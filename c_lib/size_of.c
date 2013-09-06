#include <stdio.h>
#include <string.h>

#define PRINT_SIZE(TYPE) (printf(#TYPE " : %zu bits\n", sizeof(TYPE)*8))
 
int main(int argc, char **argv) {
  PRINT_SIZE(int);
  PRINT_SIZE(char);
  PRINT_SIZE(unsigned short);
}
