#ifndef CONFIG_H
#define CONFIG_H

#define NUM_PARTICLES 15 //number of particles

// Physics constants
#define PHYS_GRAVITY 9.8f //m/s^2
#define PHYS_FRICTION 0.5f
#define PHYS_MOMENTUM_FACTOR 0.5f
#define PHYS_MAX_VELOCITY 15.0f
#define PHYS_MAX_ACCELERATION 15.0f
#define PHYS_SMOOTH_VALUE 0.8f //Value of smoothing. should be between 0[no smoothing] and 1[full smoothing])

// Display settings
#define DISP_REFRESH_RATE 0.1f // seconds
#define GRID_WIDTH 8
#define GRID_HEIGHT 8

// Colors
#define WATER_COLOR 0xFFFFFF // White

#endif
