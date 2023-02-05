/*
Resolver la carrera de datos del ejemplo 6 de la
presentación de procesos.
 Uso de la API de bifurcación y memoria compartida.
 La variable counter se pone en la región de memoria
compartida.
 El proceso padre crea un hijo y ambos intentan incrementar la
variable compartida counter.
 Hay momentos en donde el proceso padre y el hijo actualizan
la variable sin obtener el último valor modificado.
 Se imprime 1 en ambos procesos demostrando la carrera de
datos.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define SH_SIZE 4
int mutex_shm=-1;

pthread_mutex_t* mutex = NULL;
int32_t* contador = 0;
int shm=-1;

void crearVariableCompartida(){
    shm = shm_open("/shm_0", O_CREAT | O_RDWR,0600) ;

    //verificamos si se creo
    if (shm<0)
    {
        fprintf(stderr, "Tu espacio de memoria no se creo");
    }

    //Ajustamos el tamanio
    if(ftruncate(shm, SH_SIZE * sizeof(int32_t))){
        fprintf(stderr, "Error en ftruncate");
    }
   
}

void inicializamosMutex(){
    //inicializamos el mutex en el espacio de memoria
    mutex_shm = shm_open("/mutex", O_CREAT | O_RDWR, 0600);
    if (mutex_shm<0)
    {
        fprintf(stderr, "Tu espacio de memoria del mutex no se creo");
    }
    if(ftruncate(mutex_shm,SH_SIZE * sizeof(pthread_mutex_t))<0){
        fprintf(stderr, "El truncate del mutex fallo: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    void * mapMutex = mmap(0,sizeof(pthread_mutex_t),PROT_READ | PROT_WRITE,MAP_SHARED,mutex_shm,0);
    if (mapMutex == MAP_FAILED)
    {
       fprintf(stderr, "Error en mapeo");
    }
    //Creamos un puntero que hace referencia al espacio de memoria
    mutex = (pthread_mutex_t*)mapMutex;
    pthread_mutexattr_t attr;


    if(pthread_mutexattr_init(&attr)){
        fprintf(stderr, "Error en el init del mutex: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    if(pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED)){
        fprintf(stderr, "Error en el setpshared del mutex: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (pthread_mutex_init(mutex, &attr)) {
        fprintf(stderr, "Error en el INIT2 del mutex: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (pthread_mutexattr_destroy(&attr)) {
        fprintf(stderr, "ERROR: Failed to destroy mutex attrs : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}


void aumentarContador(){
    pthread_mutex_lock(mutex);
        int32_t temp = *contador;
        temp++;
        *contador=temp;
    pthread_mutex_unlock(mutex);
}

void shutdown_control_mechanism() {
  int ret = -1;
  if ((ret = pthread_mutex_destroy(mutex))) {
    fprintf(stderr, "ERROR: Failed to destroy mutex: %s\n",
        strerror(ret));
    exit(1);
  }
  if (munmap(mutex, sizeof(pthread_mutex_t)) < 0) {
    fprintf(stderr, "ERROR: Unmapping the mutex failed: %s\n",
        strerror(errno));
    exit(1);
  }
  if (close(mutex_shm) < 0) {
    fprintf(stderr, "ERROR: Closing the mutex failed: %s\n",
        strerror(errno));
    exit(1);
  }
  if (shm_unlink("/mutex") < 0) {
    fprintf(stderr, "ERROR: Unlinking the mutex failed: %s\n",
        strerror(errno));
    exit(1);
  }
}
void shutdown_shared_resource() {
  if (shm_unlink("/shm_0") < 0) {
    fprintf(stderr, "ERROR: Unlinking failed: %s\n",
        strerror(errno));
    exit(1);
  }
}


int main(){

    
    crearVariableCompartida();
    inicializamosMutex();
    
    void * map = mmap(0,SH_SIZE,PROT_WRITE,MAP_SHARED,shm,0);
    if (map == MAP_FAILED)
    {
       fprintf(stderr, "Error en mapeo");
    }
    //Creamos un puntero que hace referencia al espacio de memoria
    contador = (int32_t*)map;

    int pid = fork();

    //Si es el hijo
    for (int i = 0; i < 5; i++)
    {
         if (pid == 0 )
        {
            aumentarContador();
            printf("Aumento el contador en : %d por el HIJO \n",*contador);
        }else
        {
            aumentarContador();
            printf("Aumento el contador en : %d por el PADRE \n",*contador);
        }
    }
    

    if (pid) {
        shutdown_shared_resource();
        shutdown_control_mechanism();
    } 

    return 0;
}