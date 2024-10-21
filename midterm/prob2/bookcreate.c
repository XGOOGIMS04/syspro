#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[])
{
	struct student rec;
	FILE *fp;
	if(argc != 2){
		fprintf(stderr. "How to use: %s FileName\n", argv[0]);
		return 1;
	}
	fp = fopen(argv[1], "w");
	printf("%-2s %-10s %-10s %-5s %-30s %-10s\n", "gouu_number", "book_name", "wrighter", "year", "number", "Y_or_N");
	while(scanf("%d %s %s %d 
