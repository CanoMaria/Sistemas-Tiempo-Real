%Ejercicio 1
%{
  Genere una señal sinusoidal digital especificando
  en forma de parámetros su amplitud y frecuencia, la
  frecuencia de muestreo y la cantidad de muestras
  del registro. Grafique la señal.
%}
amplitud = 100;
frecuencia = 100;
frec_muestreo = 8000;
cant_muestras = 2500;

% Suponemos un instante de tiempo x
for x = 1 : cant_muestras
t = (x - 1) / frec_muestreo;
onda = amplitud * sin(2 * pi * frecuencia * t);
signal(x) = onda;
end

plot(signal,'color','blue')
plot(signal, 'o-b');
xlabel('Muestras')
ylabel('Amplitud')
title('Señal Sinusoidal')
