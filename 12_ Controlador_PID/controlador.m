 %--------Para el PID----------
  %abrimos una figura para ser rellenada
 figure
 s=tf('s');
 g=18/(s^2+40.1*s+20.2);
 step(g);
 title("Ejecucion continua PID");
 g
 %Ahora convertiremos esa funcion de continuo a discreto
 figure
 h=c2d(g,0.1);
 step(h);
 title("Respuesta al escalon");
 h