%Verifico que el paquete ande
%Pruebo el impulso
pkg load control
clf;
 s = tf('s');
 g = 1/(2*s^2+3*s+4);
 impulse(g);
 title ("Impulse response of a PT2 transfer function");
 
 %Pruebo el escalon
 clf;
 s = tf('s');
 g = 1/(2*s^2+3*s+4);
 step(g);
 title ("Step response of a PT2 transfer function");
 %Pueba de tiempo discreto
  clf;
 s = tf('s');
 g = 1/(2*s^2+3*s+4);
 h = c2d(g,0.1);
 step(h);
 title ("Step response of a discretized PT2 transfer function");
 
 %Pueba de rampa
 clf;
 s = tf('s');
 g = 1/(2*s^2+3*s+4);
 ramp(g);
 title ("Ramp response of a PT2 transfer function");
 
 
 %Prueba del profe 
 %-----------Para el impulso---------------
 %abrimos una figura para ser rellenada
 figure
 s=tf('s');
 g=1/(s^2+4*s+3);
 impulse(g);
 title("respuesta a impulso");
 g
 %Ahora convertiremos esa funcion de continuo a discreto
 figure
 h=c2d(g,0.1);
 impulse(h);
 title("Respuesta al impulso");
 h
 
 %--------Para el escalon----------
  %abrimos una figura para ser rellenada
 figure
 s=tf('s');
 g=1/(s^2+4*s+3);
 step(g);
 title("respuesta al escalon");
 g
 %Ahora convertiremos esa funcion de continuo a discreto
 figure
 h=c2d(g,0.1);
 step(h);
 title("Respuesta al escalon");
 h
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 