#include <stdio.h>
#include <math.h>

// Parámetros del controlador PID
double Kp = 1;
double Ki = 0.9;
double Kd = 0.9;
double L = 0.05;
double R = 2;
double J = 1;
double B = 0.1;

// Variables iniciales
double error_prev = 0;
double integral = 0;
double dt = 0.1;

// Función de control PID
double control_pid(double reference, double feedback, double error_prev, double integral)
{
  double error = reference - feedback;
  integral = integral + error * dt;
  double derivative = (error - error_prev) / dt;
  double u = Kp * error + Ki * integral + Kd * derivative;
  error_prev = error;
  return u;
}

// Función de la señal de transferencia
double transfer_function(double input)
{
  double s = 0.1;
  double num = 18 * L;
  double den = pow(s, 2) * J * R + s * (B * L + B * R + J * R) + L * R;
  double G = num / den;
  return input * G;
}

int main()
{
  int i;
  double t[1001];
  double reference[1001];
  double feedback[1001];
  double control_signal[1001];

  // Inicialización de tiempos y señales
  for (i = 0; i <= 1000; i++)
  {
    t[i] = i * dt;
    reference[i] = sin(t[i]);
    feedback[i] = 0;
    control_signal[i] = 0;
  }

  // Cálculo de las señales de referencia y retroalimentación
  for (i = 0; i <= 1000; i++)
  {
    feedback[i] = transfer_function(control_signal[i]);
    control_signal[i] = control_pid(reference[i], feedback[i], error_prev, integral);
  }

  // Imprimir los resultados
  for (i = 0; i <= 1000; i++)
  {
    printf("%.2lf, %.2lf, %.2lf\n", reference[i], feedback[i], control_signal[i]);
  }

  return 0;
}
