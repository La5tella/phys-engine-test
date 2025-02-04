#include "sim.h"

int running = 1;

int main(){
    //init funcs
    if (init_d() || init_p() || init_t()) {
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
        update_t();
        printf("update\n");
        nanosleep(&ts,NULL);
        
        
        //nanosleep(&ts, NULL);
   }

    //close funcs
    close_d();
    close_p();
    close_t();

    return 0;
}