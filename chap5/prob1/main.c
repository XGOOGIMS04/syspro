#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR | O_CREAT, 0644)) == -1)
        printf("File Open Error\n");
    else
        printf("file %s Open Success : %d\n", argv[1], fd);

    close(fd);
    exit(0);
}

