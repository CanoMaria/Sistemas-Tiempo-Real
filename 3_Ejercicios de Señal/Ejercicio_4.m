%Ejercicio 4
%{
  Utilice el ambiente de simulación para generar un
  archivo de cabecera (archivo con extensión “.h”)
  con las muestras almacenadas de una señal.
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
signal_samples= signal_3;

%Generamos un archivo y lo abrimos
file_id= fopen("signal_samples_aye.h","w");

%Escrinimos los datos
fprintf(file_id,"#define ELEMENTS %d\n\n", cant_muestras)
fprintf(file_id,"short test_signal[ELEMENTS]={")
%fprintf(file_id, "%.0f,", signal_samples);
fprintf(file_id,'%d, ' , signal_samples(1:(cant_muestras-1)));
fprintf(file_id,'%d' , signal_samples(cant_muestras));
fprintf(file_id, "};\n");
fclose(file_id);

