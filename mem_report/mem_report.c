#include <stdio.h>

int main (int argc, char const *argv[])
{
  int x;
  
  x = 1234;
  
  
  printf("var = %d, Address_Of_Var = %d\n", x, &x);
  
  return 0;
}