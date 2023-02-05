% Parámetros del controlador PID
Kp = 1;
Ki = 0.9;
Kd = 0.9;
L = 0.05;
R = 2;
J = 1;
B = 0.1;

% Variables iniciales
error_prev = 0;
integral = 0;

% Función de control PID
function [u] = control_pid(reference, feedback, error_prev, integral)
  error = reference - feedback;
  integral = integral + error * dt;
  derivative = (error - error_prev) / dt;
  u = Kp * error + Ki * integral + Kd * derivative;
  error_prev = error;
end

% Función de la señal de transferencia
function [output] = transfer_function(input)
  s = tf('s');
  G = (18 * L) / (s^2 * J * R + s * (B * L + B * R + J * R) + L * R);
  output = lsim(G, input, t);
end

% Código principal
dt = 0.1;
t = 0:dt:100;
reference = sin(t);
feedback = zeros(size(t));

for i = 1:length(t)
  feedback(i) = transfer_function(control_signal(i));
  control_signal(i) = control_pid(reference(i), feedback(i), error_prev, integral);
end

plot(t, reference, 'b', t, feedback, 'r', t, control_signal, 'g');
legend('Reference', 'Feedback', 'Control signal');
