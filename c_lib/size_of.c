#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#define PRINT_SIZE(TYPE) (printf(#TYPE " : %zu bits\n", sizeof(TYPE)*8))
 
int main(int argc, char **argv) {
  PRINT_SIZE(int);
  PRINT_SIZE(char);
  PRINT_SIZE(unsigned short);
  PRINT_SIZE(long);
  PRINT_SIZE(long long);
  PRINT_SIZE( int32_t );
  PRINT_SIZE( uint32_t );
}
