#include "common.h"
#include <inttypes.h>

#ifndef SLKR_TILE_H
#define SLKR_TILE_H

typedef uint8_t tile_index_type;

/**@Markdown
 *
 * # Tile Maping format
 *  
 *  A Tile Map is a 4 byte number
 *    Byte 1      Byte 2      Byte 3     Byte 4
 *  /----^----\ /----^----\ /----^----\/----^----\
 *   0111 0110   0101 0100   0011 0010  0001 0000
 *     D1   D0     L1   L0     R1   R0    U1   U0
 * 
 *  U0  0 = 0000   8 = 1000
 *  U1  1 = 0001   9 = 1001
 *  R0  2 = 0010   A = 1010
 *  R1  3 = 0011   B = 1011
 *  L0  4 = 0100   C = 1100
 *  L1  5 = 0101   D = 1101
 *  D0  6 = 0110   E = 1110
 *  D1  7 = 0111   F = 1111
 *
 */
typedef uint32_t tile_map_type;
typedef uint16_t tile_map_idx_type;

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
};

#include "tiles_map.h"

#endif
