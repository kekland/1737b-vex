#pragma once
#ifndef CONFIG_PID_H_
#define CONFIG_PID_H_

#include "main.h"

extern std::shared_ptr<okapi::IterativePosPIDController> leftDriveController;
extern std::shared_ptr<okapi::IterativePosPIDController> rightDriveController;
extern std::shared_ptr<okapi::IterativePosPIDController> turnController;

extern std::shared_ptr<okapi::IterativePosPIDController> flagAimingController;
extern std::shared_ptr<okapi::IterativePosPIDController> flagZoomingController;

void configure_pid();

#endif