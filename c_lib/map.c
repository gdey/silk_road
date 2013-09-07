#include "map.h"
#include <stdlib.h>

#define HEIGHT_INDEX 1
#define WIDHT_INDEX 0

map_ptr init_alloc_map( int width, int height ) {
   int size = width * height;
   char *map_data = NEW(char, size + 2);
   if( map_data == NULL ){
      /* We could not alloc enough memory */
      return NULL;
   }
   map_data[HEIGHT_INDEX] = height;
   map_data[WIDTH_INDEX] = width;
   return map_data;
}

void free_map( map_ptr map){
   free(map);
   map = NULL;
}

int map_width( map_ptr map ) {
    return (int)map[WIDTH_INDEX];
}
int map_height( map_ptr map ) {
    return (int)map[HEIGHT_INDEX];
}

int map_index(map_ptr map, int x, int y) {
    int width = (int)map[WIDTH_INDEX];
    return (x + ( y * width ) ) + 2;
}

char map_get_tile( map_ptr map, int x, int y){
    return map[ map_index(map, x, y) ];
}

MAP_BOOL map_isOnLeftEdge( map_ptr map, int x, int y ) {
  return x == 0 ? YES : NO;
}

MAP_BOOL map_isOnRightEdge( map_ptr map, int x, int y) {
  return (map[WIDTH_INDEX] - 1) == x ? YES : NO;
}

MAP_BOOL map_isOnTopEdge( map_ptr map, int x, int y) {
  return y == 0 ? YES : NO;
}

MAP_BOOL map_isOnBottomEdge( map_ptr map, int x, int y) {
  return (map[HEIGHT_INDEX] - 1) == y ? YES :  NO;
}

MAP_BOOL map_isPlayerOnEdge( map_ptr map, player_ptr player ){
   if( map_isOnLeftEdge(   map, player->x, player->y ) ||
       map_isOnRightEdge(  map, player->x, player->y ) ||
       map_isOnTopEdge(    map, player->x, player->y ) ||
       map_isOnBottomEdge( map, player->x, player->y ) ) {
       return YES;
   };
   return NO;
}

MAP_BOOL map_isPlayerOnTheMap( map_ptr map, player_ptr player){
  return ( 
    player->x >= map_width(map)  || 
    player->y >= map_height(map)
  )? YES : NO;
}

map_traversed_path *map_resolveMoveForPlayer( map_ptr map, player_ptr player ) {

  int x = player->x;
  int y = player->y;
  char tile_index = map_get_tile( map, player->x, player->y );
  if( tile_index == 0 ) {
    /* We are done here */
  }

   
}

