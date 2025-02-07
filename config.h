#ifndef CONFIG_H
#define CONFIG_H

#define NUM_PARTICLES 64//number of particles
#define PART_DEBUG 0 //set to 1 if there is only one particle and you to print it's velocity

// Physics constants
#define PHYS_OVERLAP_THRESHOLD 0.1f //how far apart each particle must be to collide.
#define PHYS_FRICTION 0.8f
#define PHYS_MOMENTUM_FAC 0.3f //how much momentum remains post collision.
#define PHYS_ACCEL_FAC 0.6f //how much gyro affects acceleration
#define PHYS_MAX_VELOCITY 5.0f
#define PHYS_MAX_ACCEL 10.0f
#define PHYS_SMOOTH_VALUE 0.8f //Value of smoothing. should be between 0[no smoothing] and .5[full smoothing])
#define PHYS_INIT_CELL_CAP 5 //How many particles can be in a cell before reallocation of memory size
#define PHYS_CELL_CAP 5 //most amount of particles per cell.

// Display settings
#define DISP_REFRESH_RATE 0.0001f // seconds
#define GRID_WIDTH 8
#define GRID_HEIGHT 8

// Colors
#define WATER_COLOR 0xFFFFFF // White

#endif
