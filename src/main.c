#include "sim.h"
#include <signal.h>

#define KEY_ENTER  28

int running = 1;

void init_cell(cell_t* cell);
void handler(unsigned int code);
void interrupt_handler(int sig){
    running = 0;
}

int main(){
    //init funcs
    signal(SIGINT, interrupt_handler);
    srand(time(NULL)); 
    //Global objects
    coordinate_t data = {0,0,0};
    pi_i2c_t* gyro = geti2cDevice();
    cell_t grid[GRID_WIDTH][GRID_HEIGHT];
    pi_joystick_t* js;
    
    for(int i=0;i<GRID_WIDTH;i++){
	for(int j=0; j<GRID_HEIGHT;j++){
		init_cell(&grid[i][j]);
	}
    }


    if (init_d(&grid) || init_p(&data, &grid) || init_i(&js,gyro,&data)|| !gyro){ 
        printf("init error\n");
        return 1;
    }
    struct timespec ts ={0, (DISP_REFRESH_RATE * 1000000000)};
    
    printf("init success. running...\n");

    while (running){
        //run loop
        //start timer
        //update funcs
        update_d();
        update_p();
        getGyroPosition(gyro, &data);
	pollJoystick(js,handler,1);	

        nanosleep(&ts,NULL);
        
        
       
   }

    //close funcs
    close_d();
    close_p();
    close_i(&js, gyro);

    return 0;
}

void init_cell(cell_t* cell) {
	//initializes and allocates memory for each cell in the grid
   	cell->count = 0;
    	cell->capacity = PHYS_INIT_CELL_CAP;
	cell->particles = calloc(cell->capacity , sizeof(particle_t*));
    	if (!cell->particles) {
    	    	fprintf(stderr, "Memory allocation failed for cell particles\n");
    	    	exit(EXIT_FAILURE);
    	}

}

void handler(unsigned int code) {

   if(code == KEY_ENTER) {
	running = 0;
    }}
