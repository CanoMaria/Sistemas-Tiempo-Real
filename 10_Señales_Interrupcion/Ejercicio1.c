/*Investigue y haga uso de la señal SIGALRM para
implementar un mecanismo de temporización
(similar a un tick de sistema). Imprima en pantalla
cada 1 segundo una cadena de caracteres para
demostrar el correcto funcionamiento de la
temporización.*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void mensaje_alarma(int signo){
    printf("Se ha ejecutado la alarma\n");
}

int main(){
    printf("PID del proceso %d \n",getpid());
    while (1)
    {
        signal(SIGALRM,mensaje_alarma);
        alarm(1);
        //espera a que se produzca una senial
        pause();
    }
    
    
    return 0;
}
