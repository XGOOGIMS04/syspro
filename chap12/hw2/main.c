#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 100

int main() {
    int fd1[2], fd2[2];
    pid_t pid1, pid2;
    char input_str[MAXLINE], modified_str[MAXLINE];

    printf("parent process start\n");

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid1 = fork();

    if (pid1 == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);

        printf("input string: ");
        fgets(input_str, sizeof(input_str), stdin);
        input_str[strcspn(input_str, "\n")] = '\0';

        write(fd1[1], input_str, strlen(input_str) + 1);
        close(fd1[1]);

        exit(0);
    } else {
        pid2 = fork();

        if (pid2 == -1) {
            perror("fork failed");
            exit(1);
        }

        if (pid2 == 0) {
            close(fd1[1]);
            close(fd2[0]);

            read(fd1[0], input_str, sizeof(input_str));
            close(fd1[0]);

            for (int i = 0; input_str[i]; i++) {
                modified_str[i] = toupper(input_str[i]);
            }

            write(fd2[1], modified_str, strlen(modified_str) + 1);
            close(fd2[1]);

            exit(0);
        } else {
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);

            read(fd2[0], modified_str, sizeof(modified_str));
            printf("%s\n", modified_str);

            close(fd2[0]);

            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}

