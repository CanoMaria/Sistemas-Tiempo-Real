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

#define SH_SIZE 4

sem_t* semaforo;
int32_t* contador = NULL;
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

void inicializamosSemaforo(){
    //inicializamos el semaforo
    semaforo = sem_open("/sem4", O_CREAT | O_EXCL, 0600, 1);
    if(semaforo==SEM_FAILED){
        fprintf(stderr, "Error en iniciar el semaforo: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}


void aumentarContador(){
    sem_wait(semaforo);
        int32_t temp = *contador;
        temp++;
        *contador=temp;
    sem_post(semaforo); 
}

int main(){

    crearVariableCompartida();
      

    //Mapeamos
    /*0: Especifica que el sistema operativo eligirá la dirección en la que se mapeará la memoria compartida.
    SH_SIZE: Especifica el tamaño en bytes de la memoria compartida que se desea mapear.
    PROT_WRITE: Especifica los permisos de la memoria compartida mapeada, en este caso se establece que solo se permitirá escribir en ella.
    MAP_SHARED: Especifica el modo de mapeo, en este caso se establece que la memoria compartida será compartida entre procesos.
    shm_fd: Es el descriptor de archivo que se usará para mapear la memoria compartida.
    0: Especifica la posición en el archivo a partir de la cual se iniciará el mapeo.*/
    void * map = mmap(0,SH_SIZE,PROT_WRITE,MAP_SHARED,shm,0);
    if (map == MAP_FAILED)
    {
       fprintf(stderr, "Error en mapeo");
    }
    
    //Creamos un puntero que hace referencia al espacio de memoria
    contador = (int32_t*)map;


    inicializamosSemaforo();

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

        if (close(shm) < 0) {
            fprintf(stderr, "Error el cerrado de shm fallo \n");
            return 1;
        }
        //cerramos la memoria compartida, la borramos
        if (shm_unlink("/shm_0") < 0) {
            fprintf(stderr, "El desligamiento de la shm fallo \n");
            exit(1);
        }
        //cerramos el semaforo
        if (sem_close(semaforo) < 0) {
            fprintf(stderr, "El cerrado del semaforo fallo \n");
            exit(1);
        }
        //Desligamos el semaforo
        if (sem_unlink("/sem4") < 0) {
            fprintf(stderr, "El desligamiento del semaforo fallo: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        if (munmap(map, SH_SIZE) < 0) {
            fprintf(stderr, "Error el desmapeo fallo: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }

    } 

    return 0;
}