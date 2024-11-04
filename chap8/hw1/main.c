#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print_all_env_vars() {
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

int main(int argc, char *argv[]) {
    int opt;
    int e_flag = 0, u_flag = 0, g_flag = 0, i_flag = 0, p_flag = 0;
    char *env_var_name = NULL;

    while ((opt = getopt(argc, argv, "e::ugip")) != -1) {
        switch (opt) {
            case 'e':
                e_flag = 1;
                env_var_name = optarg;
                break;
            case 'u':
                u_flag = 1;
                break;
            case 'g':
                g_flag = 1;
                break;
            case 'i':
                i_flag = 1;
                break;
            case 'p':
                p_flag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-e [env_var_name]] [-u] [-g] [-i] [-p]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (e_flag) {
        if (env_var_name) {
            char *env_val = getenv(env_var_name);
            if (env_val) {
                printf("%s=%s\n", env_var_name, env_val);
            } else {
                printf("환경 변수 %s가 설정되어 있지 않습니다.\n", env_var_name);
            }
        } else {
            printf("모든 환경 변수:\n");
            print_all_env_vars();
        }
    }

    if (u_flag) {
        printf("My Realistic User ID: %d\n", getuid());
        printf("My Valid User ID: %d\n", geteuid());
    }

    if (g_flag) {
        printf("My Realistic Group ID: %d\n", getgid());
        printf("My Valid Group ID: %d\n", getegid());
    }

    if (i_flag) {
        printf("my process number :[%d]\n", getpid());
    }

    if (p_flag) {
        printf("my parent's process number :[%d]\n", getppid());
    }

    return 0;
}

