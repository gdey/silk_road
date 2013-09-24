#include <stdlib.h>
#include <stdio.h>

#include "map.h"

int main (int argc, const char* argv[]){
   map_ptr map = map_init_alloc(20,20);
   print_map(map);
   map_set_tile(map,0,0,5); 
   map_set_tile(map,1,0,2); 
   map_set_tile(map,1,1,43); 
   map_set_tile(map,3,6,106); 
   print_map(map);
   printf(" Is point(%d x %d) on the board: %d\n",0,0,map_isPointOnTheMap(map,0,0));
   map_node_ptr path = map_resolveMoveForPosition( map, 0,0 ,  pos_l0 );
    
   print_node(path);
   free_map_node(path);
   free_map(map);
   return 0;
}
