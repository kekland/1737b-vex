#ifndef CONFIG_SENSORS_H_
#define CONFIG_SENSORS_H_

#include "main.h"

extern pros::Vision visionSensor;
extern okapi::ADIGyro gyro;

void configure_sensors();

#endif