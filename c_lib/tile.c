
#include "tile.h"
#include "tiles_map.h"

int tile_isCenter( enum tile_pos_type pos ){
   return pos & pos_center;
}

enum tile_pos_type tile_connected_pos(map_tileIdxType tile_index, enum tile_pos_type pos){
   if( pos & pos_center ){ // If you are at the center of a tile, you are stuck there.
     return pos;
   }
   map_tileType tile = map_tiles[tile_index][0];
   enum tile_pos_type npos =  (enum tile_pos_type) ((tile >> (pos * 4) )  & pos_mask);
   if( npos == pos ){ // Center is determined by self reference.
      return npos | pos_center; // go to the center of the tile.
   }
   return npos;
}

enum tile_pos_type tile_next_tile_pos(enum tile_pos_type  pos){
   // first we and with six to isolate the bits we are interested in.
   // Then we xor with six to turn a R <-> L or U <-> D vis vie.
   // Then we get the other bits and add them back in.

   return ((pos & pos_smask) ^ pos_smask) | (pos & pos_crmask);
}

int tile_isRight( enum tile_pos_type pos ){
   return (pos & pos_smask) == pos_r; 
}
int tile_isLeft( enum tile_pos_type pos ){
   return (pos & pos_smask) == pos_l; 
}
int tile_isUp( enum tile_pos_type pos ){
   return (pos & pos_smask) == pos_u; 
}
int tile_isDown( enum tile_pos_type pos ){
   return (pos & pos_smask) == pos_d; 
}

map_tileIdxType tile_for( map_tileIdxType tile, enum map_tileIndexs idx ){
   if( tile >= num_tiles || tile < 0 ){
     return 0; /* This is the special tile for unknown. */
   }
   return map_tiles[tile][idx];
}
map_tileIdxType tile_reference( map_tileIdxType tile){
   return (map_tileIdxType) tile_for( tile, tile_idx_ref );
}

map_tileIdxType tile_rotate90( map_tileIdxType tile){
   return (map_tileIdxType) tile_for( tile, tile_idx_90 );
}
map_tileIdxType tile_rotate180( map_tileIdxType tile){
   return (map_tileIdxType) tile_for( tile, tile_idx_180 );
}
map_tileIdxType tile_rotate270( map_tileIdxType tile){
   return (map_tileIdxType) tile_for( tile, tile_idx_270 );
}
map_tileType tile_tile( map_tileIdxType tile ){
   return tile_for( tile, tile_ref );
}



