#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../config.h"
#include "sense.h"
#include <stdbool.h>
#include <pthread.h>

//types
typedef struct {
	float x,y; //position
	int prev_x, prev_y; //previous grid to compare with new position.
	float vx,vy; //velocity
} particle_t;

typedef struct {
	particle_t** particles;
	int count;
	int capacity;
} cell_t;
//main funcs


//physics funcs
void update_particle_position(particle_t* part);
int init_p(coordinate_t* data, cell_t (*grid)[GRID_WIDTH][GRID_HEIGHT]);
int add_particles();
int remove_particle();
int close_p();
void update_p();


//display funcs
int update_d();
int init_d(cell_t (*grid)[GRID_WIDTH][GRID_HEIGHT]);
int close_d();
void clear_display();

//tilt funcs
int init_t(pi_i2c_t* gyro, coordinate_t* data);
int close_t();


