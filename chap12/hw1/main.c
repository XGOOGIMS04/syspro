#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 100

int main() {
    int fd[2];
    pid_t pid;
    char send_msg[MAXLINE], recv_msg[MAXLINE];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        close(fd[0]);
        snprintf(send_msg, sizeof(send_msg), "Hello from PID %d", getpid());
        write(fd[1], send_msg, strlen(send_msg) + 1);
        printf("Send: [%d] %s\n", getpid(), send_msg);
        close(fd[1]);
    } else {
        close(fd[1]);
        read(fd[0], recv_msg, sizeof(recv_msg));
        printf("Recv: [%d] %s\n", getpid(), recv_msg);
        close(fd[0]);
    }

    return 0;
}

