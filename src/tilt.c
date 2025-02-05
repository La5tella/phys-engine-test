#include "sim.h"
#include <unistd.h>

int init_t(pi_i2c_t* gyro, coordinate_t* data){
    	
	configureAccelGyro(gyro);
	while(getGyroPosition(gyro,data) && data->x==0.0) {
            usleep(100);
        }
	
        return 0;
 }


int close_t(pi_i2c_t* gyro){
    freei2cDevice(gyro);
    return 0;
}
