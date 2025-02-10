# phys-engine-test

## Project Overview

**Description:** This project is a fluid simulation that runs on the Raspberry Pi 4 B with a SENSE HAT. 

**Tech stack:** All code was written in C with the VIM editor.

**Objective:** To expand my knowledge on C structs, pointers, and to begin to implement algorithms into my code. I also wanted to get a glimpse into code optimizations, and tradeoffs within code to create a final product that perfoms up to the expectations of a user. ~~I also really like fluid sims~~

**Author:** Mike LaStella

### Acknowledgements

Any code that is in ../include was not created by me, but by Andrew Roosen at the University of Delaware. This code was created for CISC200, systems programming. I utilized it as the foundational API to communicate with the Pi's SENSE hat.

## Documentation
 
### Config

**NUM_PARTICLES** Number of particles in the simulation
**PART_DEBUG** Triggers physics.c:debug_vel. Prints velocity of debug particle. Only works with one particle
**DISP_REFRESH_RATE** Refresh rate in seconds.
**GRID_WIDTH** Maximum for SENSE hat is 8.
**GRID_HEIGHT** Maximum for SENSE hat is 8.

**PHYS_OVERLAP_THRESHOLD** How far apart each particle must be to collide.
**PHYS_FRICTION** Friction factor. How hard it is for each particle to move.
**PHYS_MOMENTUM_FAC** Percentage of velocity retained per collision. Set to 1 for perfectly elastic collisions.
**PHYS_ACCEL_FAC** How much gyro affects acceleration
**PHYS_MAX_VELOCITY** Maximum speed of a particle
**PHYS_MAX_ACCEL** Maximum acceleration of a particle.
**PHYS_SMOOTH_VALUE** Value of smoothing for the gyro input data.
**PHYS_INIT_CELL_CAP** How many particles can be in a cell before reallocation of memory size
**PHYS_CELL_CAP** The most amount of particles allowed per cell. Cannot be lower than INIT_CAP

**WATER_COLOR** Decides color of cells with lower particle count


### Structures

The simulation relies on two main struct objects: The *cell* and the *particle*

**Particle:**
```
typedef struct {
	float x,y; //position
	int prev_x, prev_y; //previous grid to compare with new position.
	float vx,vy; //velocity
} particle_t;
```
*x* and *y* are floats that represent the particles in two dimensional space. 

*prev_x* and *prev_y* are ints that represent the previous grid of the particle. It is used to check if that particle moves within it's current grid

*vx* and *vy* are velocities.

**Cell:** 
```
typedef struct {
	particle_t** particles;
	int count;
	int capacity;
} cell_t;
```
*particles* is a collection of particles currently in the cell.

*count* is the amount of particles in the cell.

*capacity* is the amount of particles that can fit in the cell. It can be resized dynamically, but is used to save memory. It can be capped in config.h

### Physics functions:

**void smooth_data();** 

Used to smooth out the raw input from the gyro to reduce jittering.

**void check_for_overlap(particle_t\* part);** 

Used to check if a particle is overlapping any other particle. Checks within a 3x3 grid of surrounding cells to find nearby particles to interact with.

**void remove_particle_from_grid(particle_t\* part, int x, int y);**

Removes particle from a cell, downsizes if there is space.

**void add_particle_to_grid(particle_t\* part, int x, int y);**

Adds particle to a cell. Upsizes if there is room to.

**void resize_cell(cell_t\* cell, bool uord);**

Resizes the cell size to either fit more particles or make room for more memory.
 
**void update_velocity(particle_t\* part);**

Updates the velocity of a given particle.

**void debug_vel(particle_t\* part);**

Prints the velocity and acceleration of one particle. Should only be used if one particle is in the system.

**void reflect_particle_velocity(particle_t\* part1, particle_t\* part2);**

Exchanges velocities of particles when a collision is determined.

**int check_for_room(particle_t\* part, int x, int y);**

Checks if a specific cell is able to fit a particle. If not, checks if it can be upsized.

**void update_particle_position(particle_t\* part);**

Updates the position of a given particle and binds it to the grid width.

**int init_p(coordinate_t\* data, cell_t (\*grid)[GRID_WIDTH][GRID_HEIGHT]);**

Initializes physics system.

**int add_particles();**

Allocates memory for each particle in the system.

**int remove_particle();**

Frees memory for each particle in the system.

**int close_p();**

Calls all cleanup functions.

**void update_p();**

Function that calls per frame.

**float Q_rsqrt(float number);**

Fast square root function from Quake III.

### Display functions:

**int update_d();**

Updates display per frame.

**int init_d(cell_t (\*grid)[GRID_WIDTH][GRID_HEIGHT]);**

Initializes the grid.

**int close_d();**

Frees up any initialized data.

**void clear_display();**

Sets every LED in the display to black.

**int init_i(pi_joystick_t\*\* js, pi_i2c_t* gyro, coordinate_t* data);**

Opens up inputs on the SENSE hat.

**int close_i(pi_joystick_t\*\* js, pi_i2c_t* gyro);**

Closes inputs on the SENSE hat