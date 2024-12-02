#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <command1> <args1> | <command2> <args2>\n", argv[0]);
        exit(1);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0) {  // 첫 번째 자식 프로세스
        close(pipefd[0]);  // 읽기 끝은 닫음
        dup2(pipefd[1], STDOUT_FILENO);  // 표준 출력이 파이프의 쓰기 끝으로 리디렉션
        close(pipefd[1]);

        execvp(argv[1], &argv[1]);  // command1 실행
        perror("execvp failed");
        exit(1);
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork failed");
            exit(1);
        }

        if (pid2 == 0) {  // 두 번째 자식 프로세스
            close(pipefd[1]);  // 쓰기 끝은 닫음
            dup2(pipefd[0], STDIN_FILENO);  // 표준 입력이 파이프의 읽기 끝으로 리디렉션
            close(pipefd[0]);

            execvp(argv[2], &argv[2]);  // command2 실행
            perror("execvp failed");
            exit(1);
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);  // 첫 번째 자식 프로세스 종료 대기
            wait(NULL);  // 두 번째 자식 프로세스 종료 대기
        }
    }

    return 0;
}

