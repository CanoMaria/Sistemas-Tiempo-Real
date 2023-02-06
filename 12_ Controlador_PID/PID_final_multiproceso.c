#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define Kp 0.03349    // Constante proporcional
#define Ki 0.009988   // Constante integral
#define Kd -0.09693   // Constante derivativa
#define n 0.01813

double voltajeActual=50;
double integral=0.0;
double deritativo=0.0;

double dt=0.1; //intervalo de tiempo
double t= 1.0; 
double errorPrevio=0;

double error=0.0;

void obtenerIntegral()
{
    integral=integral + error * dt;
}

void obtenerDeritativo()
{
    double tiempo=t/dt; //tiempo de muestreo
    deritativo= tiempo * (error - errorPrevio);
    errorPrevio = error;
}

int main(){
    //Creo 2 procesos que accederan al controlador pid
    pid_t pid1, pid2;
    double voltaje_deseado=40;

    double tiempo=t/dt; //tiempo de muestreo
    error= voltajeActual - voltaje_deseado;

    pid1 = fork();
    if(pid1 == 0)
    {
        obtenerIntegral();
        exit(0);
    }
    else
    {
        wait(NULL);
    }

    pid2 = fork();
    if(pid2 == 0)
    {
        obtenerDeritativo();
        exit(0);
    }
    else
    {
        wait(NULL);
    }

    // Cálculo de la señal de control
    double senalControl = Kp * error + Ki / tiempo * integral + Kd * deritativo;

    double velocidad = senalControl;
    printf("Señal de velocidad: %f\n", velocidad);

    return 0;
}