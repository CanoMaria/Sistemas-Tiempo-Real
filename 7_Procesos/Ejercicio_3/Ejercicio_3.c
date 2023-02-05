#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid;

    printf("Hola desde el proceso PADRE: %d\n",getpid());
    
    pid=fork();
    if (pid == 0)
    {
        char* args[]= {"./mensaje1",0};
        execvp("./mensaje1",args);
        return 0;
    }

    pid=fork();
    if (pid == 0)
    {
        char* args[]= {"./mensaje2",0};
        execvp("./mensaje2",args);
        return 0;
    }

    return 0;
}