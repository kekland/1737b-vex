#ifndef CONFIG_CONTROLLERS_H_
#define CONFIG_CONTROLLERS_H_

#include "main.h"

extern okapi::ChassisControllerIntegrated drivetrain;

extern BaseIntakeController* intakeController;
extern BaseShooterController* shooterController;
extern BaseShooterAngleController* shooterAngleController;

void configure_controllers();

#endif