/*Modificar el programa del ejemplo 3 para que en lugar
de utilizar un ejecutable dentro de PATH utilice un
ejecutable en el directorio actual. Codificar también el
programa del ejecutable que se cargará que incluya algo
simple como imprimir un mensaje en pantalla.*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv) {
	char *args[] = {"./mensaje", 0};

	execvp("./mensaje", args);

	printf("execvp() failed. Error: %s\n", strerror(errno));

	return 0;
}