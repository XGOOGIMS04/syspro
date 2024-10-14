#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINES 100

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
		exit(1);
	}

	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		perror("File open error");
		exit(1);
	}

	printf("File read success\n");

	char buffer;
	char savedText[MAX_LINES][100];
	int lineCount = 0;

	while(read(fd, &buffer, 1) > 0) {
		if(buffer == '\n') {
			savedText[lineCount][strlen(savedText[lineCount])] = '\0';
			lineCount++;
		} else {
			savedText[lineCount][strlen(savedText[lineCount])] = buffer;
		}
	}

	if(lineCount > 0 && savedText[lineCount - 1][strlen(savedText[lineCount - 1]) - 1] != '\0'){
		savedText[lineCount][strlen(savedText[lineCount])] = '\0';
	}
	
	printf("Total Line : %d\n", lineCount);
 	printf("You can choose 1 ~ %d Line\n", lineCount);

	char input[100];
	printf("Ple 'Enter' the line to select : ");
	scanf("%s", input);

	if(strcmp(input, "*") == 0) {
		for (int i = 0; i < lineCount; i++) {
			printf("%s\n", savedText[i]);
		}
	} else {
		char *token = strtok(input, ",");
		while (token != NULL) {
			if(strchr(token, '-') != NULL) {
				int start, end;
				sscanf(token, "%d-%d", &start, &end);
				for(int i = start - 1; i < end && i < lineCount; i++){
					printf("%s\n", savedText[i]);
				}
			} else{
				int lineNum = atoi(token);
				if(lineNum > 0 && lineNum <= lineCount) {
					printf("%s\n", savedText[lineNum - 1]);
				} else {
					printf("Line %d does not exit.\n", lineNum);
				}
			}
			token = strtok(NULL, ",");
		}
	}


	close(fd);
	return 0;
}
