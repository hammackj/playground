#include <stdio.h>

void toBinary(int num)
{
    int r;
    if(num <= 1)
    {   
        printf("%d",num);
        
        return;
    }

    r = num % 2;
    toBinary(num >> 1);

    printf("%d",r);
}

int main(int argc, char** argv)
{
    toBinary(69);
    
    return 0; 
}