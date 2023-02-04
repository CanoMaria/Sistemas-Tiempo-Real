/*Escriba una aplicación que contenga 3 tareas
periódicas que deben ejecutarse con las
siguientes temporizaciones:
 Tarea 1: 100 ms
 Tarea 2: 300 ms
 Tarea 3: 500 ms*/

#include <stdio.h>
#include <unistd.h>

void tarea_1(){
    printf("Ejecutandose tarea 1 \n");
}
void tarea_2(){
    printf("Ejecutandose tarea 2 \n");
}
void tarea_3(){
    printf("Ejecutandose tarea 3 \n");
}

int main(){

    while (1)
    {
        tarea_1();
        sleep(1);

        tarea_2();
        sleep(1);

        tarea_3();
        sleep(1);

    }
    
    return 0;
}