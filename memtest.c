#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void insertchar(char c, int index, char *s) {
	char *tmp = NULL;
	char *oldstr = NULL;
	
	if((tmp = malloc((strlen(s) + 1) * sizeof (char))) == NULL) {
		printf("Malloc failed on tmp\n");
		exit(EXIT_FAILURE);
	}
	
	if((oldstr = malloc((strlen(s) + 1) * sizeof (char))) == NULL) {
		printf("Malloc failed on tmp\n");
		exit(EXIT_FAILURE);
	}
	
	int size = strlen(s);
	strcpy(oldstr, s);
	
	if((s = malloc((strlen(s) + 1) * sizeof (char))) == NULL) {
		printf("Malloc failed on tmp\n");
		exit(EXIT_FAILURE);
	}
	
	tmp[index] = c;
	
	int x = 0;
	for(x = 0; x < index; x++)
	{
		tmp[x] = s[x];
	}
	
	int y = 0;
//	y = (size - x - 1);
	for(y = (size - x -1); y < size; y++)
	{
		tmp[y] =  s[y];
	}
	
	strcpy(s, tmp);
	free(tmp);
}

int main (int argc, char const *argv[])
{
	char *s = "WTFYO!";
	
	insertchar('x', 3, s);
	
	printf("\n|%s|\n", s);
	

	return 0;
}