/*1. Codificar en una función reentrante el
algoritmo de un filtro de promedio según
la ecuación (verla en el ppt)
*/
#include <stdio.h>

double promedio(double *notas, int n){
    double resultado = 0;
        for (int i = 0; i < n; i++)
        {
            resultado += notas[i];
        }
    return resultado/n;
}

int main(){
    double notas[] = {8.5,9,10,6,4,5};
    double promedioObtenido=0;
    int n=5;
    promedioObtenido=promedio(notas,n);
    printf("El promedio obtenido es = %lf",promedioObtenido);
    return 0;
}