#include "sim.h"

//variable declaration
coordinate_t* gyro_data;
float xo,yo=0;
cell_t (*_g)[GRID_WIDTH][GRID_HEIGHT];
particle_t* particles[NUM_PARTICLES];


//func prototyping
void smooth_data();
particle_t** check_for_overlap(particle_t* part);
void remove_particle_from_grid(particle_t* part, int x, int y);
void add_particle_to_grid(particle_t* part, int x, int y);
void resize_cell(cell_t* cell, bool uord); 
void update_velocity(particle_t* part);
void debug_vel(particle_t* part);

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
	for(int i=0; i<NUM_PARTICLES;i++){
		particle_t* part=particles[i];
		update_velocity(part);
		update_particle_position(part);
		//debug_vel(part);
	}
		
}

void debug_vel(particle_t* part){
		//recommended for use with a single particle to adjust parameters.
	printf("\rVx: %+04.2f Ax: %+04.2f Vy: %+04.2f Ay: %+04.2f", part->vx, (PHYS_MAX_ACCEL * ((gyro_data->x)/180)) * PHYS_ACCEL_FAC, part->vy, (PHYS_MAX_ACCEL * ((gyro_data->y)/180)) * PHYS_ACCEL_FAC);
	fflush(stdout);
}

void update_velocity(particle_t* part){
	// Update velocity with directional acceleration from gyro data
	part->vx += (PHYS_MAX_ACCEL * ((gyro_data->x)/180)) * PHYS_ACCEL_FAC;
	part->vy += (PHYS_MAX_ACCEL * ((gyro_data->y)/180)) * PHYS_ACCEL_FAC;

	// Apply friction to gradually slow down the velocity
	part->vx *= (1 - PHYS_FRICTION * DISP_REFRESH_RATE);
	part->vy *= (1 - PHYS_FRICTION * DISP_REFRESH_RATE);

	if(part->vx>PHYS_MAX_VELOCITY)
		part->vx=PHYS_MAX_VELOCITY;

	if(part->vy>PHYS_MAX_VELOCITY)
		part->vy=PHYS_MAX_VELOCITY;


}

int add_particles(){
//adds particles to simulation
	for(int i=0; i<NUM_PARTICLES;i++){
		//initializes the particles
		particles[i] = calloc(1, sizeof(particle_t));
		particle_t* part = particles[i];
		
		//adds the particle to the display grid. Maybe change to adding it out of total particles that can fit?
		part->x = (rand() % GRID_WIDTH);
		part->y = (rand() % GRID_HEIGHT);

		int count = (*_g)[(int)part->x][(int)part->y].count;
		(*_g)[(int)part->x][(int)part->y].particles[count] = part;
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
	gyro_data->x = -1*((PHYS_SMOOTH_VALUE * xo) + ((1-PHYS_SMOOTH_VALUE)*gyro_data->x));
	gyro_data->y = -1*((PHYS_SMOOTH_VALUE * yo) + ((1-PHYS_SMOOTH_VALUE)*gyro_data->y));


}

particle_t** check_for_overlap(particle_t* part){
	//FREE MUST BE CALLED AFTER THIS FUNCTION!!
	//Checks if particle is in grid. Should check if any particles in nearby grid cells are overlapping.
	int x = (int)part->x;
	int y = (int)part->y;
	int count = 0;
	int part_count=0;
	cell_t* cells[9] = {NULL};
		
	//loop through neighboring cells. Identify if the cell is occupied
	for(int dx = -1; dx <=1; dx++){
		for(int dy = -1; dy<=1; dy++){
			int neighbor_x = x+dx;
			int neighbor_y= y+dy;

			//skips over cells outside of bounds
			if(neighbor_x <0 || neighbor_y <0 || neighbor_x >= GRID_WIDTH || neighbor_y >= GRID_HEIGHT)
				continue;

			if((*_g)[neighbor_x][neighbor_y].count>0)
				cells[count]=&((*_g)[neighbor_x][neighbor_y]);
				part_count += (*_g)[neighbor_x][neighbor_y].count;
				count++;
				continue;
		}
	}
	if(count==0)
		return NULL;
	//returns an array with pointers to the cells with overlapped particles
	//probably should return an array of particles that are in the overlap threshold.
	particle_t** overlap_part= calloc(part_count, sizeof(particle_t*));
	int tally=0;
	for(int i=0;cells[i]!=NULL;i++){
		for(int j=0;j<(cells[i])->count;j++){
			overlap_part[tally]=(cells[i])->particles[j];
			tally++;
		}
		}
	return overlap_part;
}


void update_particle_position(particle_t* part) {
	
    // Store the current position as the previous position
   	part->prev_x = (int)part->x;
    	part->prev_y = (int)part->y;
	
    // Update the particle's current position based on velocity
    	if(part->x + part->vx > 0 && part->x + part->vx < GRID_WIDTH)
		part->x += part->vx;
		
	else if(part->x + part->vx >= GRID_WIDTH){
	      //set pos and reflect velocity	
		part->x = GRID_WIDTH-1;
		part->vx *= (-1* PHYS_MOMENTUM_FACTOR);
		
	}
	else if(part->x + part->vx <= 0){
		part->x =0;
		part->vx *=(-1* PHYS_MOMENTUM_FACTOR);

	}
	
	if(part->y + part->vy > 0 && part->y + part->vy < GRID_HEIGHT)
		part->y += part->vy;
		
		
	else if(part->y + part->vy >= GRID_HEIGHT){
	      //set pos and reflect velocity	
		part->y = GRID_HEIGHT-1;
		part->vy *= (-1* PHYS_MOMENTUM_FACTOR);
	}
	else if(part->y + part->vy <= 0){
		part->y =0;
		part->vy *=(-1* PHYS_MOMENTUM_FACTOR);
	}
    
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
    	cell_t* cell = &((*_g)[x][y]);
	for(int i=0;i<cell->count;i++){
		if (cell->particles[i] == part) {
            	// Found the particle; shift subsequent elements left
            		for (int j = i; j < cell->count - 1; j++) {
               			cell->particles[j] = cell->particles[j+1];
           			}
            	// Clear the now-unused last element and update count
            			cell->particles[cell->count - 1] = NULL;
            			cell->count--;
            			
            			break;  // Exit the loop once the particle is removed
       			 }
		if(cell->count<cell->capacity&&cell->capacity<PHYS_INIT_CELL_CAP)
			resize_cell(cell, false);	
	}
	//add a checker if the grid can downsize

}

void add_particle_to_grid(particle_t* part, int x, int y) {
    // Logic to add the particle to the grid at (x, y)
    	cell_t cell = (*_g)[x][y];
	
	for(int i=0;i<cell.capacity;i++){
		if(cell.particles[i]==NULL){
			cell.particles[i]=part;
			cell.count++;
			
			(*_g)[x][y] = cell;
			return;
		}
		if(cell.count==cell.capacity){
			resize_cell(&cell, true);
		}
			
	}
}

void resize_cell(cell_t* cell, bool uord){
	//adds one extra slot to the cell
	//I THINK THIS QUEUES UP A DOUBLE FREE
	if(uord){
		particle_t** temp = realloc(cell->particles, (cell->capacity+1) * sizeof(cell_t));
		if(temp == NULL)
			return;
		cell->capacity+=1;
		cell->particles = temp;
		if (cell->particles == NULL) {	
    				fprintf(stderr, "Memory allocation failed for grid cell\n");
    				exit(EXIT_FAILURE);  // Optionally terminate the program if memory allocation is critical
					}
	}else{
		particle_t** temp = realloc(cell->particles, (cell->capacity-1) * sizeof(cell_t));
		if(temp == NULL)
			return;
		cell->capacity-=1;
		cell->particles = temp;
		if (cell->particles == NULL) {
    			    	fprintf(stderr, "Memory allocation failed for grid cell\n");
    				exit(EXIT_FAILURE);  // Optionally terminate the program if memory allocation is critical
					}

	}

}


