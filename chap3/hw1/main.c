#include <stdio.h>
#include <string.h>
#include "copy.h"

char lines[5][MAXLINE];
char lengths[5] = {0};

int main(){
	int i,j;

	for(i = 0; i < 5; i++){
		gets(lines[i]);
		lengths[i] = strlen(lines[i]);
	}

	for(i = 0; i < 5; i++){
		for(j = i + 1; j < 5; j++){
			if(lengths[i] < lengths[j]){
				int temp_len = lengths[i];
				lengths[i] = lengths[j];
				lengths[j] = temp_len;

				char temp[MAXLINE];
				copy(lines[i], temp);
				copy(lines[j], lines[i]);
				copy(temp, lines[j]);
			}
		}
	}

	for (i = 0; i < 5; i++)
		printf("%s \n", lines[i]);

	return 0;
}
