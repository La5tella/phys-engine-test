#include "sim.h"
#include <signal.h>

int running = 1;

void interrupt_handler(int sig){
    running = 0;
}
int main(){
    //init funcs
    signal(SIGINT, interrupt_handler);
    
    //Global objects
    coordinate_t data = {0,0,0};
    pi_i2c_t* gyro = geti2cDevice();
    int grid[GRID_WIDTH][GRID_HEIGHT] = {0};


    if (init_d(&grid) || init_p(&data, &grid) || init_t(gyro,&data)|| !gyro){ 
        printf("init error\n");
        return 1;
    }
	printf("%d\n",grid[0][1]);
    struct timespec ts ={0, (DISP_REFRESH_RATE * 1000000000)};
    double dt = DISP_REFRESH_RATE; 
    printf("init success. running...\n");

    while (running){
        //run loop
        //start timer
        //update funcs
        update_d();
        update_p();
        getGyroPosition(gyro, &data);
	
	printf("Gyro: %f %f %f\n", data.x, data.y, data.z);

        nanosleep(&ts,NULL);
        
        
       
   }

    //close funcs
    close_d();
    close_p();
    close_t();

    return 0;
}
