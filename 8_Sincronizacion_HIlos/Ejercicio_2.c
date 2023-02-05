/*
Reemplace la estructura de ejecutivo
cíclico con 3 tareas descripto en “05-
ejercicios.pdf” por un sistema multihilo
con 3 hilos, manteniendo una
funcionalidad similar.

Escriba una aplicación que contenga 3 tareas
periódicas que deben ejecutarse con las
siguientes temporizaciones:
 Tarea 1: 100 ms
 Tarea 2: 300 ms
 Tarea 3: 500 ms*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


sem_t sem_1, sem_2, sem_3;

void* task_1(void *args){
    while (1)
    {
        //Bloque el semaforo 1
        sem_wait(&sem_1);
        printf("1\n");
        //Libero el semaforo 2
        sem_post(&sem_2);
        sleep(1);
    }
    return 0;
}
void* task_2(void *args){
    while (1)
    {
        //Bloque el semaforo 2
        sem_wait(&sem_2);
        printf("2\n");
        //Libero el semaforo 1
        sem_post(&sem_3);
        sleep(2);
    }
  
    return 0;
}
void* task_3(void *args){
    while (1)
    {
       //Bloque el semaforo 2
        sem_wait(&sem_3);
        printf("3\n\n");
        //Libero el semaforo 1
        sem_post(&sem_1);
        sleep(3);
    }
    
    return 0;
}

int main(){
    pthread_t hilo_1,hilo_2,hilo_3;
    //Solo el semaforo 1 esta activado;
    sem_init(&sem_1,0,1);
    sem_init(&sem_2,0,0);
    sem_init(&sem_3,0,0);

    pthread_create(&hilo_1,NULL,task_1,NULL);
    pthread_create(&hilo_2,NULL,task_2,NULL);
    pthread_create(&hilo_3,NULL,task_3,NULL);

    pthread_join(hilo_1,NULL);
    pthread_join(hilo_2,NULL);
    pthread_join(hilo_3,NULL);  
    
    return 0;
}