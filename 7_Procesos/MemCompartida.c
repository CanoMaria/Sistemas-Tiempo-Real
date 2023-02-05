#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// Para ejecutarlo debio usarse gcc -o EjMemCompartida EjMemCompartida.c -lrt -lpthread

#define SH_SIZE 16

int main(int argc, char** argv) {

	// Crea una región de memoria compartida
	int shm_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
	
	// Verifica si se creó correctamente
	if (shm_fd < 0) {
		fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
		return 1;
	}
	
	// Imprime el descriptor de archivo asociado a la región de memoria compartida
	fprintf(stdout, "Shared memory is created with fd: %d\n", shm_fd);
	
	// Trunca la región de memoria compartida a un tamaño de SH_SIZE caracteres
	if (ftruncate(shm_fd, SH_SIZE * sizeof(char)) < 0) {
		fprintf(stderr, "ERROR: Truncation failed: %s\n",
		strerror(errno));
		return 1;
	}
	
	// Imprime que la región de memoria se ha truncado correctamente
	fprintf(stdout, "The memory region is truncated.\n");
	
	// Mapea la región de memoria compartida en el espacio de direcciones del proceso
	void* map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	// Verifica si se realizó correctamente el mapeo
	if (map == MAP_FAILED) {
		fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
		return 1;
	}
	
	// Escribir algunos datos en la región de memoria compartida
	char* ptr = (char*)map;
	ptr[0] = 'A';
	ptr[1] = 'B';
	ptr[2] = 'C';
	ptr[3] = '\n';
	ptr[4] = '\0';
	
	// Imprime que los datos han sido escritos en la región de memoria compartida
	fprintf(stdout, "Data is written to the shared memory.\n");
	
	// Desmapea la región de memoria compartida
	if (munmap(ptr, SH_SIZE) < 0) {
		fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
		return 1;
	}
	
	// Cierra el descriptor de archivo de la
	if (close(shm_fd) < 0) {
		fprintf(stderr, "ERROR: Closing shared memory failed: %s\n", strerror(errno));
		return 1;
	}
	
	return 0;
}