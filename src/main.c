#include "sim.h"

int running = 1;

void interrupt_handler(int sig){
    running = 0;
}
int main(){
    //init funcs
    signal(SIGINT, interrupt_handler);
    coordinate_t data = {0,0,0};
    pi_i2c_t* gyro = geti2cDevice();
    if (init_d() || init_p() || init_t(&gyro) || !gyro){ {
        printf("init error\n");
        return 1;
    }
    struct timespec ts ={0, (refresh_rate * 1000000000)};
    double dt = refresh_rate;

    printf("init success. running...\n");
    while (running){
        //run loop
        //start timer
        //update funcs
        update_d();
        update_p();
        getGyroPosition(&gyro, &data);
        printf("Gyro: %f %f %f\n", data.x, data.y, data.z);
        nanosleep(&ts,NULL);
        
        
        //nanosleep(&ts, NULL);
   }

    //close funcs
    close_d();
    close_p();
    close_t();

    return 0;
}