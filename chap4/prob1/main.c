#include <stdio.h>
int main(int agrc, char *argv[])
{
	FILE *fp;
	int c;
	if(argv < 2)
		fp = stdin;
	else fp = fopen(argv[1], "r");

	c = getc(fp);
	while(c != EOF) {
		putc(c, stdout);
		c = getc(fp);
	}
	fclose(fp);
	return 0;
}
