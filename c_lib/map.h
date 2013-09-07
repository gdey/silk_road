#include "common.h"
#include "player.h"
#include "tile.h"
#include "sandstorm.h"

#ifndef SLKR_MAP_H
#define SLKR_MAP_H

#define MAP_PLAYER_NOT_ON_BOADER -1
#define MAP_PLAYER_NOT_ON_MAP -1
#define MAP_PLAYER_OTHER_IN_SPACE -2
#define MAP_PLAYER_FULL  -2


struct map_struct {
   int width;
   int height;
   int num_players;
   int num_sandunes;
   player_ptr players[16];
   sandstorm_ptr storms[16];
   char* data;
} map_type;


struct {
   char spos :4;
   char epos :4;
   char tile_index;
   int x;
   int y;
} map_path;
struct {
   int count;
   map_path paths[];

} map_traversed_path ;

typedef char * map_ptr;

map_ptr  map_init(int width, int height);
void free_map( map_ptr map );
MAP_BOOL map_isOnLeftEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnRightEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnTopEdge( map_ptr map, int x, int y);
MAP_BOOL map_isOnBottomEdge( map_ptr map, int x, int y);
MAP_BOOL map_setTile( map_ptr map, int x, int y, tile_ptr title );
tile_ptr map_getTile( map_ptr map, int x, int y);

int map_addPlayer( map_ptr map, player_ptr player);
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
