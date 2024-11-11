#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    int pid1, status;

    pid1 = fork();
    
    if (pid1 < 0) { 
        fprintf(stderr, "Failed to create child process.\n");
        return 1;
    } 
    else if (pid1 == 0) { 

        if (execvp(argv[1], &argv[1]) == -1) { 
            fprintf(stderr, "Error: Failed to execute command with execvp()\n");
            exit(1);
        }
    } 
    else { 
        wait(&status);

        if (WIFEXITED(status)) {
            printf("[%d] Child process %d end\n", getpid(), pid1);
			printf("\t end code %d\n", status >> 8);
        }
    }

    return 0;
}

