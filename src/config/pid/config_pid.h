#ifndef CONFIG_PID_H_
#define CONFIG_PID_H_

#include "main.h"

extern okapi::IterativePosPIDController leftDriveController;
extern okapi::IterativePosPIDController rightDriveController;
extern okapi::IterativePosPIDController turnController;

extern okapi::IterativePosPIDController flagAimingController;
extern okapi::IterativePosPIDController flagZoomingController;

void configure_pid();

#endif