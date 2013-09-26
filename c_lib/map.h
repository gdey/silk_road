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

typedef map_tileIdxType * map_ptr;

map_ptr  map_allocInit(int width, int height);
void map_free( map_ptr map );
// int map_index( map_ptr map, int x, int y);

int map_width( map_ptr map );
int map_height( map_ptr map );


map_tileIdxType map_getTile( map_ptr map, int x, int y);
map_tileIdxType map_setTile( map_ptr map, int x, int y, map_tileIdxType tile );

int map_nextTileY( enum tile_pos_type pos, int y);
int map_nextTileX( enum tile_pos_type pos, int x);

MAP_BOOL map_isOnLeftEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnRightEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnTopEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnBottomEdge( map_ptr map, int x, int y);
MAP_BOOL map_isPointOnTheMap( map_ptr map,int x, int y);

map_node_ptr map_resolveMoveForPosition( map_ptr map, int px, int py, enum tile_pos_type ppos );

void map_node_free( map_node_ptr node );
void map_node_print( map_node_ptr node );

void map_print( map_ptr map );



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
