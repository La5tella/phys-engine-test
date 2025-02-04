#include "sim.h"

int init_t(pi_i2c_t* gyro){
    if (configureAccelGyro(gyro));
        return 0;
    return 1;
}


int close_t(pi_i2c_t* gyro){
    freei2cDevice(gyro);
    return 0;
}