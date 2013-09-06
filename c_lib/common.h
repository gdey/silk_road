#ifndef SLKR_COMMON_H
#define SLKR_COMMON_H

#ifdef __cplusplus
# define NEW(type, count) ((type *)calloc(count, sizeof(type)))
#else
# define NEW(type, count) (calloc(count, sizeof(type)))
#endif

enum {
  NO = 0,
  YES
} MAP_BOOL;

#endif
