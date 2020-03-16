#ifndef DEFINES_H
#define DEFINES_H

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <uzebox.h>

typedef enum {
  SOUTH, WEST, NORTH, EAST
} direction;

#define EDGE_WEST 26
#define EDGE_EAST 0
#define EDGE_NORTH 2
#define EDGE_SOUTH 28

#endif
