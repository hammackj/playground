#include <stdio.h>

void xor(char *string, char *key)
{
		int x;         //b--&#g+(>
	for(x = 0; x < 21; x++)
	{
		string[x] = string[x] ^ key[x];
		
		printf("%c", string[x]);
	}

	printf("\n");	
}

int main()
{
	char string[21]="Pwning noobs is fun~";
	char key[21]="ABCDEABCDEFGHIJFGHIJ";

	printf("[*] Encrypting %s\n", string);

	printf("[$] Encrypted string: ");
	xor(string, key);
		
	printf("[*] Decrypting %s\n", string);
	printf("[$] Encrypted string: ");
	
	xor(string, key);	

	return 0;
}