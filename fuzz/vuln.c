#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	char buff[200];

	printf("%d", getpid());

	getchar();

	strcpy(buff, argv[1]);

	return 0;
}
