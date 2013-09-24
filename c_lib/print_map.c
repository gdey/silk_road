#include <stdlib.h>
#include <stdio.h>

#include "map.h"

int main (int argc, const char* argv[]){
   map_ptr map = map_init_alloc(20,20);
   print_map(map);
   map_set_tile(map,1,0,1); 
   map_set_tile(map,3,6,106); 
   print_map(map);
   free_map(map);
   return 0;
}
