#include "common.h"
#include <inttypes.h>

#ifndef SLKR_TILE_H
#define SLKR_TILE_H

typedef uint8_t tile_index_type;

/**@Markdown
 *
 * # Tile Maping format
 *  
 *  A Tile Map is a 3 byte number
 *    Byte 1    Byte 2     Byte 3
 *  /----^---\ /---^----\ /----^----\
 *  111 110 10|1 100 011 0|10 001 000
 *   D1  D0  L 1  L0  R1   R0  U1  U0
 * 
 *  0 = 0000
 *  1 = 0001
 *  2 = 0010
 *  3 = 0011
 *  4 = 0100
 *  5 = 0101
 *  6 = 0110
 *  7 = 0111
 *  8 = 1000
 *  9 = 1001
 *  A = 1010
 *  B = 1011
 *  C = 1100
 *  D = 1101
 *  E = 1110
 *  F = 1111
 *
 */
typedef uint32_t tile_map_type;
const tile_map_type tiles[] = {
  0,  // Default unknown tile. (can be any value, just that tiles[0] is unknown.)
            //  D0   D1  L 1  L0 R1    R0  U 1 U0 
  0xDEC053, // 110|1 11|10 1|100 000|0 01|01 0011
  0xB3E053, // 101|1 00|11 1|110 000|0 01|01 0011 



}

enum tile_pos_type {
   pos_u  = 0,
   pos_u0 = 0, // 000
   pos_u1 = 1, // 001
   pos_r  = 2,
   pos_r0 = 2, // 010
   pos_r1 = 3, // 011
   pos_l  = 4,
   pos_l0 = 4, // 100
   pos_l1 = 5, // 101
   pos_d  = 6,
   pos_d0 = 6, // 110
   pos_d1 = 7, // 111
   pos_smask = 6,
   pos_mask = 7,
   pos_center = 8,
   pos_cu0 = 8,
   pos_cu1, 
   pos_cr0,
   pos_cr1,
   pos_cl0,
   pos_cl1,
   pos_cd0,
   pos_cd1,
   pos_crmask = 9
}

#endif
