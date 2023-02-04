%Ejercicio 3
%{
  Revise la documentación de la función fft() del
  ambiente de simulación para luego obtener los
  espectros de frecuencia de las señales de los
  puntos 1, y 2. Grafique cada espectro de
  frecuencia.
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

signal_3 = signal_1 + signal_2
%Obtenemos la transformada de furier
f1 = fft(signal_1);
f2 = fft(signal_2);
f3 = fft(signal_3);

%Dividimos la parte compleja de las tranformadas para obtener solo las partes positivas
N = length(signal_3);
f1 = f1(1:N/2+1);
f2 = f2(1:N/2+1);
f3 = f3(1:N/2+1);
f = frec_muestreo*(0:N/2)/N;

figure;
plot(f, abs(f1), 'blue');
hold on;
plot(f, abs(f2), 'red');
%plot(f, abs(f3), 'green');
figure;
plot(f,20*log10(f3)) % grafica con salida en dBs.

legend('Espectro Señal 1', 'Espectro Señal 2', 'Espectro Señal 3');
xlabel('Frecuencia (Hz)');
ylabel('Amplitud');
title('Espectros de Frecuencia');




