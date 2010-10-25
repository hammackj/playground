#include <stdio.h>
#include <regex.h>
#include <string.h>

int main (int argc, char const *argv[])
{
	int error;
	regex_t pdata;
	regmatch_t pmatch[3];
	char dest[1024];
	char *buffer;
	size_t length;
	
	char *line = "SPE A[0m8[1;58H[7mPage 1 of 3[0m[2;38HSTATION[4;1H Extension: [4;12H0013 [5;6HType:";

	if (error = regcomp(&pdata, "(Extension:)", REG_EXTENDED))
	{
		printf("Error 1\n");
		length = regerror(error, &pdata, buffer, NULL);
		buffer = malloc(sizeof(char) * (int)length);
		regerror(error, &pdata, buffer, length);
		fprintf(stderr, "%s\n", buffer); /* Print the error */
      	free(buffer);
		
		return 1;
	} 
	
	if (error = regexec(&pdata, line, 0, pmatch, 0))
	{
		printf("Error 2 %d\n", error);
		
		length = regerror(error, &pdata, buffer, NULL);
		buffer = malloc(sizeof(char) * length);
		regerror(error, &pdata, buffer, length);
		fprintf(stderr, "%s\n", buffer); /* Print the error */
      	free(buffer);
	
		return 2;
	} 

		strncpy(dest, line + pmatch[0].rm_so, line + pmatch[0].rm_eo);
		
		printf("dest = %s\n", dest);
		

	  regfree(&pdata);

	
	return 0;
}
