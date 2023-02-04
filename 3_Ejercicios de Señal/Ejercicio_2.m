%Ejercicio 2
%{
  Realice la suma de dos señales como las del punto
  1 con igual amplitud pero de diferentes frecuencias.
  Grafique la señal resultante.
%}

amplitud=100
frec_1=100
frec_2=250
frec_muestreo=8000
cant_muestras=2500

for x=1 : cant_muestras
  t=(x-1)/frec_muestreo
  signal_1(x) = amplitud * sin(2 * pi * t *frec_1 );
  signal_2(x) = amplitud * sin(2 * pi * t *frec_2 );
end

signal_3 = signal_1 + signal_2;
plot(signal_3, 'green');
legend('Señal 3');


xlabel('Muestras')
ylabel('Amplitud')
title('Señal Sinusoidal')
