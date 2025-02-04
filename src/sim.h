#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../config.h"
#include "sense.h"

//main funcs


//physics funcs
int update_p();
int init_p();
int add_particle();
int remove_particle();
int close_p();


//display funcs
int update_d();
int init_d();
int close_d();

//tilt funcs
int init_t(pi_i2c_t* gyro);
int close_t();