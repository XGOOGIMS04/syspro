#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINES 100

int main(int argc, char *argv[]) {
	if(argc < 2){
		fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
		exit(1);
	}

	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		perror("File open error");
		exit(1);
	}

	char buffer;
	char savedText[MAX_LINES][100];
    int lineCount = 0;

	while(read(fd, &buffer, 1) > 0){
		if(buffer == '\n') {
			savedText[lineCount][strlen(savedText[lineCount])] = '\0';
			lineCount++;
		} else {
			savedText[lineCount][strlen(savedText[lineCount])] = buffer;
		}
	}

	if(lineCount > 0 && savedText[lineCount - 1][strlen(savedText[lineCount - 1]) - 1] != '\0') {
		savedText[lineCount][strlen(savedText[lineCount])] = '\0';
	}

	for(int i = lineCount - 1; i >= 0; i--){
		printf("%s\n", savedText[i]);
	}

	close(fd);
	return 0;
}
