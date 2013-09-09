
#include "tile.h"

int tile_isCenter( tile_pos_type pos ){
   return pos & pos_center;
}
uint8_t tile_connected_pos(tile_index_type tile_index, tile_pos_type pos){
   if( pos & pos_center ){ // If you are at the center of a tile, you are stuck there.
     return pos;
   }
   uint32_t tile = tiles[tile_index];
   tile_pos_type npos =  (tile_pos_type) ((tile >> (pos * 4) )  & pos_mask);
   if( npos == pos ){ // Center is determined by self reference.
      return npos | pos_center; // go to the center of the tile.
   }
   return npos;
}

tile_pos_type tile_next_tile_pos(tile_pos_type  pos){
   // first we and with six to isolate the bits we are interested in.
   // Then we xor with six to turn a R <-> L or U <-> D vis vie.
   // Then we get the other bits and add them back in.

   return ((pos & pos_smask) ^ pos_smask) | (pos & pos_crmask);
}

int tile_isRight( tile_pos_type pos ){
   return (pos & pos_smask) == pos_r; 
}
int tile_isLeft( tile_pos_type pos ){
   return (pos & pos_smask) == pos_l; 
}
int tile_isUp( tile_pos_type pos ){
   return (pos & pos_smask) == pos_u; 
}
int tile_isDown( tile_pos_type pos ){
   return (pos & pos_smask) == pos_d; 
}






