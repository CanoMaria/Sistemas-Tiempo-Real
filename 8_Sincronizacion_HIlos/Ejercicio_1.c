/*Utilice el ejemplo 1 como base para
reemplazar las funciones de mutex por
las funciones de spinlock, y probar el
funcionamiento del programa.*/

#include <stdio.h>
#include <stdlib.h>
// The POSIX standard header for using pthread library
#include <pthread.h>

// The mutex object used to synchronize the access to
// the shared state.
pthread_spinlock_t spin;

void* thread_body_1(void* arg) {
    // Obtain a pointer to the shared variable
    int* shared_var_ptr = (int*)arg;
    // Critical section
    pthread_spin_lock(&spin);
    (*shared_var_ptr)++;
    printf("%d\n", *shared_var_ptr);
    pthread_spin_unlock(&spin);
    return NULL;
}

void* thread_body_2(void* arg) {
    int* shared_var_ptr = (int*)arg;
    // Critical section
    pthread_spin_lock(&spin);
    *shared_var_ptr += 2;
    printf("%d\n", *shared_var_ptr);
    pthread_spin_unlock(&spin);
    return NULL;
}

int main(int argc, char** argv) {
    // The shared variable
    int shared_var = 0;
    
    // The thread handlers
    pthread_t thread1;
    pthread_t thread2;
    
    // Initialize the mutex and its underlying resources
    pthread_spin_init(&spin, 0);
    
    // Create new threads
    int result1 = pthread_create(&thread1, NULL, thread_body_1, &shared_var);
    int result2 = pthread_create(&thread2, NULL, thread_body_2, &shared_var);
    
    if (result1 || result2) {
        printf("The threads could not be created.\n");
        exit(1);
    }
    
    // Wait for the threads to finish
    result1 = pthread_join(thread1, NULL);
    result2 = pthread_join(thread2, NULL);
    
    if (result1 || result2) {
        printf("The threads could not be joined.\n");
        exit(2);
    }
    
    pthread_spin_destroy(&spin);
    
    return 0;
}