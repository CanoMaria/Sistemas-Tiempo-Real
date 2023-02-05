#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid;

  // Crear el primer proceso hijo
  pid = fork();
  if (pid == 0) {
    // Este es el primer proceso hijo
    printf("Soy el primer hijo, mi PID es %d\n", getpid());
    return 0;
  }

  // Crear el segundo proceso hijo
  pid = fork();
  if (pid == 0) {
    // Este es el segundo proceso hijo
    printf("Soy el segundo hijo, mi PID es %d\n", getpid());
    return 0;
  }

  // Este es el proceso padre
  printf("Soy el padre, mi PID es %d\n", getpid());
  while (1);

  return 0;
}