#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 100

/* 파이프를 통해 자식에서 실행되는 명령어 출력을 받아 프린트 */
int main(int argc, char* argv[]) {
    int n, pid, fd[2];
    char line[MAXLINE];

    if (argc < 2) { // 실행 인자가 부족한 경우 처리
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        exit(1);
    }

    if (pipe(fd) == -1) { // 파이프 생성 오류 처리
        perror("pipe failed");
        exit(1);
    }

    if ((pid = fork()) == -1) { // fork 오류 처리
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) { // 자식 프로세스
        close(fd[0]);              // 읽기 끝 닫기
        dup2(fd[1], STDOUT_FILENO); // 파이프 쓰기 끝을 표준 출력으로 복제
        close(fd[1]);              // 복제 후 쓰기 끝 닫기
        execvp(argv[1], &argv[1]); // 명령 실행
        perror("execvp failed");   // execvp 실패 시 에러 메시지 출력
        exit(1);                   // 오류 종료
    } else { // 부모 프로세스
        close(fd[1]);              // 쓰기 끝 닫기
        printf("자식 프로세스로부터 받은 결과\n");
        while ((n = read(fd[0], line, MAXLINE)) > 0) { // 파이프에서 읽기
            write(STDOUT_FILENO, line, n); // 읽은 내용을 출력
        }
        close(fd[0]); // 읽기 끝 닫기
    }

    return 0; // 정상 종료
}

