#include "sim.h"

//variable declaration
coordinate_t* gyro_data;
float xo,yo=0;
int (*_g)[GRID_WIDTH][GRID_HEIGHT];
particle_t* particles[NUM_PARTICLES];


//func prototyping
void smooth_data();
int check_for_overlap(particle_t* part);

int init_p(coordinate_t* data, int (*grid)[GRID_WIDTH][GRID_HEIGHT]){
    	_g=grid;
	gyro_data=data;
	add_particles();
	if(data)
		return 0;
	else
		return 1;
}

int close_p(){

    return 0;
}  

int update_p(){
    smooth_data();
	return 0;
}
int add_particles(){

	for(int i=0; i<NUM_PARTICLES;i++){
		particles[i] = malloc(sizeof(particle_t));
		particle_t* part = particles[i];
		int overlap = 0;
		do{
		part->x = (rand() % GRID_WIDTH);
		part->y = (rand() % GRID_HEIGHT);
		overlap = check_for_overlap(part);
		} while(overlap);
		(*_g)[(int)part->x][(int)part->y] = 1;
		part->vx=0.0f;
		part->vy=0.0f;

	}
    return 0;
}

int remove_particle(){
    return 0;
}   

void smooth_data(){

	gyro_data->x = (PHYS_SMOOTH_VALUE * xo) + ((1-PHYS_SMOOTH_VALUE)*gyro_data->x);
	gyro_data->y = (PHYS_SMOOTH_VALUE * yo) + ((1-PHYS_SMOOTH_VALUE)*gyro_data->y);


}

int check_for_overlap(particle_t* part){

	if(*_g[(int)part->x][(int)part->y])
		return 1;
	else
		return 0;


}

