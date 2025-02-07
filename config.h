#ifndef CONFIG_H
#define CONFIG_H

#define NUM_PARTICLES 1 //number of particles

// Physics constants
#define PHYS_OVERLAP_THRESHOLD 0.25f //how far apart each particle must be to collide.
#define PHYS_FRICTION 0.8f
#define PHYS_MOMENTUM_FACTOR 0.8f
#define PHYS_ACCEL_FAC 0.8f //how much gyro affects acceleration
#define PHYS_MAX_VELOCITY 15.0f
#define PHYS_MAX_ACCEL 15.0f
#define PHYS_SMOOTH_VALUE 0.8f //Value of smoothing. should be between 0[no smoothing] and 1[full smoothing])
#define PHYS_INIT_CELL_CAP 5 //How many particles can be in a cell before reallocation of memory size

// Display settings
#define DISP_REFRESH_RATE 0.0001f // seconds
#define GRID_WIDTH 8
#define GRID_HEIGHT 8

// Colors
#define WATER_COLOR 0xFFFFFF // White

#endif
