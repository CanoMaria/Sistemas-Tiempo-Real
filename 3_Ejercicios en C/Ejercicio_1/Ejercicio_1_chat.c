#include <stdio.h>

short doubleToShort(double input) {
  return (short)input;
}

double shortToDouble(short input) {
  return (double)input;
}

int main(void) {
  double inputDouble;
  short outputShort;

  printf("Ingrese un número de punto flotante: ");
  scanf("%lf", &inputDouble);

  outputShort = doubleToShort(inputDouble);
  printf("El número de punto flotante ingresado es %lf\n", inputDouble);
  printf("El número entero resultante es %d\n", outputShort);

  inputDouble = shortToDouble(outputShort);
  printf("El número entero original es %d\n", outputShort);
  printf("El número de punto flotante resultante es %lf\n", inputDouble);

  return 0;
}
