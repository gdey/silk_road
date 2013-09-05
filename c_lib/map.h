#include <stdlib.h>
#include "silkroad/common.h"
#include "silkroad/player.h"
#include "silkroad/tile.h"
#include "silkraod/sanddune.h"

#ifndef SLKR_MAP_H
#define SLKR_MAP_H

enum {
  NO = 0,
  YES
} MAP_BOOL;

struct map_struct {
   int width;
   int height;
   int num_plauers;
   int num_sandunes;
   player_ptr players[16];
   sanddune_ptr dunes[16];
   char* data;
} map_type;

typedef map_type * map_ptr;

map_ptr  map_init(int width, int height);
MAP_BOOL map_isOnLeftEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnRightEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnTopEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnBottomEdge( map_ptr map, int x, int y);
MAP_BOOL map_setTile( map_ptr map, int x, int y, tile_ptr title );
tile_ptr map_getTile( map_ptr map, int x, int y);

int map_addPlayer( map_ptr map, 


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
