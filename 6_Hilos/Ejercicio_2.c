#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* showHilo(void * arg){
     printf("El TID del proceso HIJO es: %d \n", (long)pthread_self());
}

int main (){

    //creo un arrreglo de hilos
    pthread_t array[10];

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&array[i],NULL,showHilo,NULL);
        //pthread_join(array[i],NULL);
    }

    //Espero que todos los hilos terminen
    for (int i = 0; i < 10; i++)
    {
        pthread_join(array[i],NULL);
    }
    return 0;
}