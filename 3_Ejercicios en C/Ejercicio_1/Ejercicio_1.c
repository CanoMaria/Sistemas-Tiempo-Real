#include <stdio.h>

int doubleAShort(double);
double shortADouble(int);

int main(int argc, char const *argv[])
{
    double numeroIngresado;
    double numeroConvertidoDouble;
    int numeroConvertidoShort;

    printf("Ingresa el numero double: ");
    scanf("%lf", &numeroIngresado);

    numeroConvertidoShort= doubleAShort(numeroIngresado);
    printf("El numero obtenido de Double a Short es: %d \n",numeroConvertidoShort);

    numeroConvertidoDouble= shortADouble(numeroConvertidoShort);
    printf("El numero obtenido de Short a Double es: %lf\n",numeroConvertidoDouble);

    

    return 0;
}

int doubleAShort(double numero){
    int resultado= (short) numero;
    return resultado;
}

double shortADouble(int numero){
    double resultado= (double) numero;
    return resultado;
}
