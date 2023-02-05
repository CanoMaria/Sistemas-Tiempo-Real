/*Codifique un programa cuyo proceso sea capaz de
enviar la señal SIGINT al proceso del ejemplo 1. Se
deberá pasar como argumento al programa el PID
del proceso del ejemplo 1.*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void mensaje_alarma(int signo){
    printf("Se ha ejecutado la alarma\n");
}

int main(){
    pid_t pid;
    printf("Ingresa el PID del proceso: ");
    scanf("%d",&pid);

    if (kill(pid,SIGINT)==0)
    {
        printf("Senial enviada al proceso: %d\n",pid);
    }else
    {
        printf("El proceso no se elimino correctamente");
    }
    
    
    
    
    
    return 0;
}