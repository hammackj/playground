//Jacob Hammack
//Shellcode executor template from: http://www.thexploit.com/sploitdev/testing-your-shellcode-on-a-non-executable-stack-or-heap/

#include <stdio.h>

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
 
int (*sc)();
 
char shellcode[] = "<YOUR SHELLCODE>";
 
int main(int argc, char **argv) 
{
 
    void *ptr = mmap(0, <SIZE OF YOUR SHELLCODE>, PROT_EXEC | PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
 
    if (ptr == MAP_FAILED) 
    {
        perror("mmap");
        exit(-1);
    }
 
    memcpy(ptr, shellcode, sizeof(shellcode));
    sc = ptr;
 
    sc();
 
    return 0;
}