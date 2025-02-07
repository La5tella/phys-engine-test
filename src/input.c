#include "sim.h"
#include <unistd.h>


int init_i(pi_joystick_t** js, pi_i2c_t* gyro, coordinate_t* data){
	//opens joystick
	*js = getJoystickDevice();
	//opens gyro and binds to data
	configureAccelGyro(gyro);
	while(getGyroPosition(gyro,data) && data->x==0.0) {
            usleep(100);
        }
        return 0;
}

int close_i(pi_joystick_t** js, pi_i2c_t* gyro)
{
	//js = NULL;
	if (*js)
		*js=NULL;
	freei2cDevice(gyro);
       	return 0;
}	




