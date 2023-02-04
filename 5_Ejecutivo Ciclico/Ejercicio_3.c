#include <stdio.h>
/*Codificar en una función reentrante el
algoritmo de un filtro IIR de primer orden
según la ecuación

yn = yn−1 + b0(xn − yn−1)*/

double iir_filter(double y, double bo,double x[],int tam){
    for (int n = 0; n < tam; n++)
    {
       y= y + bo * ( x[n] - y );
    }
    return y;    
}

int main(){
    srand(time(NULL));  // Inicializa la semilla de números aleatorios
    int tam=5;
    double x[tam];
    double y=0;
    double bo=0.5;

    for (int i = 0; i < tam; i++)
    {
        x[i]=rand();
    }
    printf("El valor retornado es: %lf",iir_filter(y,bo,x,tam));
    
    return 0;
}