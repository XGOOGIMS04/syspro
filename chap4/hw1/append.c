#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE *file1, *file2;
	char buffer[256];

	if(argc != 3){
		fprintf(stderr, "Usage: %s file1.txt file2.txt\n", argv[0]);
		return 1;
	}

	file1 = fopen(argv[1], "r");
	if(file1 == NULL) {
		perror("Error opening file1");
		return 1;
	}

	file2 = fopen(argv[2], "a");
	if(file2 == NULL) {
		perror("Error opening file2");
		fclose(file1);
		return 1;
	}
	while (fgets(buffer, sizeof(buffer), file1) !=  NULL){
		fseek(file2, -1, SEEK_END);
		char lastChar;
		fread(&lastChar, sizeof(char), 1, file2);

		if(lastChar != '\n') {
			fputc(' ', file2);
		}

		fputs(buffer, file2);
	}

	fclose(file1);
	fclose(file2);

	return 0;
}

