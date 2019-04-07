#ifndef CONFIG_MOTORS_H_
#define CONFIG_MOTORS_H_

#include "main.h"

extern okapi::AbstractMotor::gearset driveGearset;
extern okapi::ChassisScales driveScales;

extern okapi::Motor driveLeftFront;
extern okapi::Motor driveLeftBack;
extern okapi::Motor driveRightFront;
extern okapi::Motor driveRightBack;

extern okapi::MotorGroup driveLeft;
extern okapi::MotorGroup driveRight;

extern okapi::Motor intake;
extern okapi::Motor shooter;
extern okapi::Motor shooterAngle;

void configure_motors();
#endif