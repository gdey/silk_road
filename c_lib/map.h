#include "common.h"
#include <inttypes.h>
#include "player.h"
#include "tile.h"
#include "sandstorm.h"

#ifndef SLKR_MAP_H
#define SLKR_MAP_H

#define MAP_PLAYER_NOT_ON_BOADER -1
#define MAP_PLAYER_NOT_ON_MAP -1
#define MAP_PLAYER_OTHER_IN_SPACE -2
#define MAP_PLAYER_FULL  -2


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

typedef uint8_t * map_ptr;

map_ptr  map_init(int width, int height);
void free_map( map_ptr map );
MAP_BOOL map_isOnLeftEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnRightEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnTopEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnBottomEdge( map_ptr map, int x, int y);
MAP_BOOL map_setTile( map_ptr map, int x, int y, tile_ptr title );
tile_ptr map_getTile( map_ptr map, int x, int y);

int map_setTitleForPlayer( map_ptr map, player_ptr, int tile_index);
int map_resolveMoveForPlayer( map_ptr map, player_ptr player);


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
