/*Codifique un programa que genere un hilo y
desde la función complementaria imprima por
pantalla su PID y TID.*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* showHilo(void * arg){
     printf("El PID del proceso HIJO es: %d \n",getpid());
     printf("El TID del proceso HIJO es: %d \n", (long)pthread_self());
}

int main(){
    printf("El PID del proceso PADRE es: %d \n",getpid());

    pthread_t hilo_1;

    //Creamos un hilo
    pthread_create(&hilo_1,NULL,showHilo,NULL);
    //Esperamos a que se termine de ejecutar
    pthread_join(hilo_1,NULL);
    pthread_exit(NULL);
    return 0;
}
