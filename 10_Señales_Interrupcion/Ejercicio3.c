#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(){
    int action[2]; // pos 0+ lectura y pos1 es escritura;
    int action2[2]; // pos 0+ lectura y pos1 es escritura;

    pipe(action);
    pipe(action2);

    int pid= fork();

    //Verificamos si es el hijo
    if (pid == 0)
    {
        //cerramos el lector por que queremos escribir
        close(action[0]);
        //Armamos el mensaje
        char str[]="Hola padre :)\n";
        printf("HIJO-Escribi un mensaje\n");
        //Escribimos un mensaje..
        write(action[1],str,strlen(str)+1);

        sleep(2);

         //Leo mensaje
        close(action2[1]);
        char str_recibida[32];
        read(action2[0],str_recibida,32);
        printf("HIJO-Recibi el mensaje: %s",str_recibida);


    }else
    {
        //Leo mensaje
        close(action[1]);
        char str_recibida[32];
        read(action[0],str_recibida,32);
        printf("PADRE-Recibi el mensaje: %s",str_recibida);

        sleep(1);

        //Escribo mensaje
        close(action2[0]);
        char str[]="Hola hijo 7.7 \n";
        printf("PADRE-Escribi un mensaje\n");
        write(action2[1],str,strlen(str)+1);

        sleep(2);

    }
    
    return 0;
}