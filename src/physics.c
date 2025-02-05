#include "sim.h"

//variable declaration
coordinate_t* gyro_data;
float xo,yo=0;
cell_t (*_g)[GRID_WIDTH][GRID_HEIGHT];
particle_t* particles[NUM_PARTICLES];


//func prototyping
void smooth_data();
int check_for_overlap(particle_t* part);
void remove_particle_from_grid(particle_t* part, int x, int y);
void add_particle_to_grid(particle_t* part, int x, int y);

int init_p(coordinate_t* data, cell_t (*grid)[GRID_WIDTH][GRID_HEIGHT]){
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

void update_p(){
	smooth_data();
}

int add_particles(){
//adds particles to simulation
	for(int i=0; i<NUM_PARTICLES;i++){
		//initializes the particles
		particles[i] = malloc(sizeof(particle_t));
		particle_t* part = particles[i];
		int overlap = 0;
		do{
			//places randomly on grid
			part->x = (rand() % GRID_WIDTH);
			part->y = (rand() % GRID_HEIGHT);
			overlap = check_for_overlap(part);
		} while(overlap);
		//adds the particle to the display grid. Maybe change to adding it out of total particles that can fit?
		(*_g)[(int)part->x][(int)part->y].count++;
		//sets initial velocity
		part->vx=0.0f;
		part->vy=0.0f;

	}
    return 0;
}

int remove_particle(){
	for(int i=0;i<NUM_PARTICLES; i++)
		free(particles[i]);
    return 0;
}   

void smooth_data(){
	//lerps to velocity for smoother transitions.
	gyro_data->x = (PHYS_SMOOTH_VALUE * xo) + ((1-PHYS_SMOOTH_VALUE)*gyro_data->x);
	gyro_data->y = (PHYS_SMOOTH_VALUE * yo) + ((1-PHYS_SMOOTH_VALUE)*gyro_data->y);


}

int check_for_overlap(particle_t* part){
	//Checks if particle is in grid. Should check if any particles in nearby grid cells are overlapping.
	int x = (int)part->x;
	int y = (int)part->y;

	//loop through neighboring cells. Identify if the cell is occupied
	for(int dx = -1; dx <=1; dx++){
		for(int dy = -1; dy<=1; dy++){
			int neighbor_x = x+dx;
			int neighbor_y= y+dy;

			//skips over cells outside of bounds
			if(neighbor_x <0 || neighbor_y <0 || neighbor_x >= GRID_WIDTH || neighbor_y >= GRID_HEIGHT)
				continue;

			if((*_g)[neighbor_x][neighbor_y].count>0)
				return 1;
			
		}



	}
	return 0;
}

void update_particle_position(particle_t* part) {
    // Store the current position as the previous position
   	part->prev_x = (int)part->x;
    	part->prev_y = (int)part->y;

    // Update the particle's current position based on velocity
    	part->x += part->vx;
   	part->y += part->vy;

    // Calculate the new grid cell (assuming some grid size, e.g., 10x10)
    	int new_x = (int)part->x;
    	int new_y = (int)part->y;

    // Check if the particle has moved to a new cell
    	if (part->prev_x != new_x || part->prev_y != new_y) {
        // Update the grid cell to the new one
        	remove_particle_from_grid(part, part->prev_x, part->prev_y);
        	add_particle_to_grid(part, new_x, new_y);

    }
}

void remove_particle_from_grid(particle_t* part, int x, int y) {
    //finds previous position in grid, removes from stored pos.

}

void add_particle_to_grid(particle_t* part, int x, int y) {
    // Logic to add the particle to the grid at (x, y)
}
