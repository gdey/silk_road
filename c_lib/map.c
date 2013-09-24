#include <stdlib.h>
#include <stdio.h>
#include "map.h"

#define HEIGHT_INDEX 1
#define WIDTH_INDEX 0

map_ptr map_init_alloc( int width, int height ) {
   int size = width * height;
   map_ptr map_data = NEW(tile_map_idx_type, size + 2);
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

tile_map_idx_type map_get_tile( map_ptr map, int x, int y){
    return map[ map_index(map, x, y) ];
}

tile_map_idx_type map_set_tile( map_ptr map, int x, int y, tile_map_idx_type tile){
   int index = map_index(map, x, y);
   tile_map_type old_tile = map[ index ];
   map[index] = tile; 
   return old_tile;
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

MAP_BOOL map_isPoinOnEdge( map_ptr map, int x, int y){
   if( map_isOnLeftEdge(   map, x, y ) ||
       map_isOnRightEdge(  map, x, y ) ||
       map_isOnTopEdge(    map, x, y ) ||
       map_isOnBottomEdge( map, x, y ) ) {
       return YES;
   };
   return NO;
}

MAP_BOOL map_isPointOnTheMap( map_ptr map,int x, int y){
  return ( 
    x >= map_width(map)  || 
    y >= map_height(map)
  )? YES : NO;
}

int map_next_tile_x( enum tile_pos_type pos, int x){
  if( tile_isCenter(pos) ){
     return x;
  }
  if( tile_isLeft(pos) ){
    return x - 1;
  }
  if( tile_isRight(pos) ){
    return x + 1;
  }
  return x;
}

int map_next_tile_y( enum tile_pos_type pos, int y){
  if( tile_isCenter(pos) ){
     return y;
  }
  if( tile_isUp(pos) ){
    return y - 1;
  }
  if( tile_isDown(pos) ){
    return y + 1;
  }
  return y;
}
map_node_ptr map_resolveMoveForPosition( map_ptr map, int px, int py, enum tile_pos_type  ppos ){

  int x = px;
  int y = py;
  enum tile_pos_type pos = ppos;
  map_node_ptr node = NULL;
  map_node_ptr head = NULL;
  tile_map_idx_type tile_index = map_get_tile( map, x,y );

  while( map_isPointOnTheMap(map, x, y) == YES ){
    map_node_ptr next = calloc(1,sizeof(struct map_node));
    next->x = x;
    next->y = y;
    next->onBoard = 1;
    next->tile_index = tile_index;
    next->previous = node;
    next->next = NULL;
    next->spos = pos;
    enum tile_pos_type epos = tile_connected_pos(tile_index,pos);
    next->epos = epos;
    if(  node == NULL ){
       head = next;
    }
    if( node != NULL && x == px && y == py && pos == ppos ){
      // We are back where we started, this is a loop. Let's stop.
      node = next;
      break;
    }
    node = next;
    if( tile_index == 0 ){
       break;
    }
    pos = tile_next_tile_pos(epos); 
    x = map_next_tile_x(epos,x);
    y = map_next_tile_y(epos,y);
  }
  if( map_isPointOnTheMap(map, x, y) == NO && node != NULL ){
     node->onBoard = 0;
  }
  return node;
}



void free_map_node ( map_node_ptr node ){

   while ( node != NULL ) {
     map_node_ptr next = node->next;
     node->next = NULL;
     node->previous = NULL;
     free( node );
     node = next;
   }

}

void _print_boader_() {
   printf("|-|+");
}

/**********
 +|-|+
 -000-
 -000-
 +|-|+
*********/
void _print_index_( int index ) {
  printf("%03d-",index); 
}

void print_map( map_ptr map ){
     int x = map_width(map);
     int y = map_height(map);
     printf("\nline[%03d](%02dx%02d)+",0,x,y);
     for( int xc = 0; xc < x; xc++ ){
       _print_boader_();
     }
     for( int yc = 0; yc < y; yc++ ){
       for( int line = 0; line < 3; line ++){
          if( line == 2 ){
             printf("\nline[%03d](%02dx%02d)+",line,0,yc);
          } else {
             printf("\nline[%03d](%02dx%02d)-",line,0,yc);
          }
          for( int xc = 0; xc < x; xc++){
             if( line == 2 ){
                _print_boader_();
             } else {
                _print_index_(map_get_tile(map,xc,yc));
             }
          }
       }
     }
     printf("\n");

}

