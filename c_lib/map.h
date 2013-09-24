#include "common.h"
#include <inttypes.h>
#include "tile.h"

#ifndef SLKR_MAP_H
#define SLKR_MAP_H

#define MAP_PLAYER_NOT_ON_BOADER -1
#define MAP_PLAYER_NOT_ON_MAP -1
#define MAP_PLAYER_OTHER_IN_SPACE -2
#define MAP_PLAYER_FULL  -2
#define YES 1
#define NO 0
#define MAP_BOOL char


struct map_node {
   uint8_t spos :4;
   uint8_t epos :4;
   uint8_t tile_index;
   int x;
   int y;
   int onBoard;
   struct map_node *next;
   struct map_node *previous;
};

typedef struct map_node * map_node_ptr;

typedef tile_map_idx_type * map_ptr;

map_ptr  map_init_alloc(int width, int height);

void free_map( map_ptr map );

int map_width( map_ptr map );
int map_height( map_ptr map );

int map_index( map_ptr map, int x, int y);

tile_map_idx_type map_get_tile( map_ptr map, int x, int y);
tile_map_idx_type map_set_tile( map_ptr map, int x, int y, tile_map_idx_type tile );


MAP_BOOL map_isOnLeftEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnRightEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnTopEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnBottomEdge( map_ptr map, int x, int y);

void print_map( map_ptr map );



/*
map_type *init_map(int width, int height) {
    int size = width * height;
    char *map_data = calloc(size,sizeof(char));
    if( ptr == NULL ){
      * Memory coud not be allocated *
    }
}
*/

#endif
