#pragma once
#ifndef CONFIG_SENSORS_H_
#define CONFIG_SENSORS_H_

#include "main.h"

extern pros::Vision visionSensor;
extern okapi::ADIGyro gyro;
extern okapi::ADIUltrasonic ultrasonic;

void configure_sensors();

#endif