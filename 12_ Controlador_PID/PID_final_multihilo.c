#include <pthread.h>
#include <stdio.h>
#include <math.h>

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
pthread_mutex_t mutex;


void* obtenerIntegral(void * args){
    pthread_mutex_lock(&mutex);
    double error= *(double*) args;
    integral=integral + error * dt;
    pthread_mutex_unlock(&mutex);
}
void* obtenerDeritativo(void * args){
    pthread_mutex_lock(&mutex);
    double error= *(double*) args;
    double tiempo=t/dt; //tiempo de muestreo
    deritativo= tiempo * (error - errorPrevio);
    errorPrevio = error;  
    pthread_mutex_unlock(&mutex);
}


int main(){
    //Creo 2 hilos que accederan al controlador pid
    pthread_t hilo_1,hilo_2;  
    double voltaje_deseado=40;

    pthread_mutex_init(&mutex,NULL);

    double tiempo=t/dt; //tiempo de muestreo
    double error= voltajeActual - voltaje_deseado;

    pthread_create(&hilo_1,NULL,obtenerIntegral,&error);
    pthread_create(&hilo_2,NULL,obtenerDeritativo,&error); 
    
    pthread_join(hilo_1,NULL);
    pthread_join(hilo_2,NULL);

    // Cálculo de la señal de control
    double senalControl = Kp * error + Ki / tiempo * integral + Kd * deritativo;

    double velocidad = senalControl;
    printf("Señal de velocidad: %f\n", velocidad);

    return 0;
}