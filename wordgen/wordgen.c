#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pwned(char *inputstring, int length);
void build(char inputstring, char *arraystring, int length);
void recbuild(char *inputstring, char *arraystring, int length);

void pwned(char *inputstring, int length)
{
	int i;
	
	for(i = 0; i < strlen(inputstring); i++)
	{
		build(inputstring[i], inputstring, length);
	}
}

void build(char inputstring, char *arraystring, int length)
{
	int i;
	for (i = 0; i < strlen(arraystring); i++)
	{
		char *newString;
		char hack[2];
		newString = calloc(strlen(hack) + 1 + strlen(arraystring), sizeof(char));
		newString[0] = inputstring;
		
		hack[0] = arraystring[i];
		hack[1] = '\0';
		
		strcat(newString, hack);
		
		if(strlen(newString) <= length)
		{
			printf("%s\n", newString);
			recbuild(newString, arraystring, length);
		}

	}
}

void recbuild(char *inputstring, char *arraystring, int length)
{
	int i;
	for (i = 0; i < strlen(arraystring); i++)
	{
		char *newString;
		char hack[2];
		newString = calloc(strlen(hack) + strlen(inputstring) + strlen(arraystring), sizeof(char));
		strcat(newString, inputstring);
		
		//printf("%c",arraystring[i]);
		
		hack[0] = arraystring[i];
		hack[1] = '\0';
		
		strcat(newString, hack);
		
		if(strlen(newString) <= length)
		{
			printf("%s\n", newString);
			recbuild(newString, arraystring, length);
		}

	}
}

int main (int argc, char const *argv[])
{
	char *ascii = "abcd ";
	
	printf("Generating Wordlist...\n");
	pwned(ascii, 5);

	
	return 0;
}