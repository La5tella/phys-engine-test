#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../config.h"
#include "sense.h"


//main funcs


//physics funcs
int update_p();
int init_p(coordinate_t* data, int (*grid)[GRID_WIDTH][GRID_HEIGHT]);
int add_particles();
int remove_particle();
int close_p();


//display funcs
int update_d();
int init_d(int (*grid)[GRID_WIDTH][GRID_HEIGHT]);
int close_d();
void clear_display();

//tilt funcs
int init_t(pi_i2c_t* gyro, coordinate_t* data);
int close_t();

//types
typedef struct {
	float x,y; //position
	float vx,vy; //velocity
} particle_t;


