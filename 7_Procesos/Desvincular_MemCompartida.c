#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// Para ejecutarlo debio usarse gcc -o EjMemCompartida EjMemCompartida.c -lrt -lpthread

#define SH_SIZE 16

int main(int argc, char** argv) {

	// Abrir objeto de memoria compartida "/shm0" con permisos de solo lectura
	int shm_fd = shm_open("/shm0", O_RDONLY, 0600);

	// Verificar si la apertura del objeto de memoria compartida fue exitosa
	if (shm_fd < 0) {
		// Imprimir mensaje de error en stderr si la apertura falló
		fprintf(stderr, "ERROR: Failed to open shared memory: %s\n", strerror(errno));
		return 1;
	}

	// Imprimir en la salida estándar el identificador de archivo asociado al objeto de memoria compartida
	fprintf(stdout, "Shared memory is opened with fd: %d\n", shm_fd);

	// Mapear el objeto de memoria compartida en el espacio de direcciones del proceso
	void* map = mmap(0, SH_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

	// Verificar si el mapeo fue exitoso
	if (map == MAP_FAILED) {
		// Imprimir mensaje de error en stderr si el mapeo falló
		fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
		return 1;
	}

	// Hacer casting del puntero a char*
	char* ptr = (char*)map;

	// Imprimir el contenido de la memoria compartida en la salida estándar
	fprintf(stdout, "The contents of shared memory object: %s\n", ptr);

	// Eliminar el mapeo del objeto de memoria compartida
	if (munmap(ptr, SH_SIZE) < 0) {
		// Imprimir mensaje de error en stderr si la eliminación del mapeo falló
		fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
		return 1;
	}

	// Cerrar el identificador de archivo asociado al objeto de memoria compartida
	if (close(shm_fd) < 0) {
		// Imprimir mensaje de error en stderr si el cierre falló
		fprintf(stderr, "ERROR: Closing shared memory fd filed: %s\n", strerror(errno));
		return 1;
	}

	// Eliminar el objeto de memoria compartida
	if (shm_unlink("/shm0") < 0) {
		// Imprimir mensaje de error en stderr si la eliminación falló
		fprintf(stderr, "ERROR: Unlinking shared memory failed: %s\n", strerror(errno));
		return 1;
	}

	// Devolver código de salida 0 para indicar que la operación se realizó correctamente
	return 0;

}