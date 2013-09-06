#include "map.h"
#include <stdlib.h>


map_ptr init_map( int width, int height ) {
   int size = width * height;
   char *map_data = NEW(char, size);
   if( map_data == NULL ){
      /* We could not alloc enough memory */
      return NULL;
   }
   map_ptr map = NEW(map_type, 1);
   map->width = width;
   map->height = height;
   map->num_players  = 0;
   map->num_sandunes = 0;
   for( int i; i = 0; i < 16; i++ ){
     map->players[i] = NULL;
   }
   for( int i; i = 0; i < 16; i++ ){
     map->storms[i] = NULL;
   }
   map->data = map_data;
   return map;
}

void free_map( map_ptr map){
   free(map->data);
   map->data = NULL;
   free(map);
   map = NULL;
}

MAP_BOOL map_isOnLeftEdge( map_ptr map, int x, int y ) {
  return x == 0 ? YES : NO;
}

MAP_BOOL map_isOnRightEdge( map_ptr map, int x, int y) {
  return (map->width - 1) == x ? YES : NO;
}

MAP_BOOL map_isOnTopEdge( map_ptr map, int x, int y) {
  return y == 0 ? YES : NO;
}

MAP_BOOL map_isOnBottomEdge( map_ptr map, int x, int y) {
  return (map->height - 1) == y ? YES :  NO;
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
    player->x >= map->x || player->y >= map->y 
  )? YES : NO;
}

signed int add_player( map_ptr map, player_ptr player) {
   int player_index;
   if( map_isPlayerOnTheMap( map, player ) == NO ){
     return MAP_PLAYER_NOT_ON_MAP;
   }

   if( map->num_player >= 16 ) {
     return MAP_PLAYER_FULL;
   }

   player_index = map->num_players;
   map->num_players++;
   map->player[player_index] = player;
   return player_index;

}
