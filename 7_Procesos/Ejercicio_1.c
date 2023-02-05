/*Escribir un programa que sea capaz de generar 10
procesos hijos los cuales deben imprimir su PID. Usar la
herramienta pstree y top para analizar los resultados.*/

#include <stdio.h>
#include <unistd.h>

int main(){
   
    printf("Este es el PID del proceso PADRE: %d \n", getpid() );

    for (int i = 0; i < 10; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            printf("%d - Este es el PID del proceso HIJO %d \n", getpid(),i);
            return 0;
        }       
       
    }    
    while (1);
    return 0;
}