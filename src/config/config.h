#ifndef CONFIG_H_
#define CONFIG_H_

#include "main.h"

using namespace okapi;

/* Higher-level stuff like ChassisControllers, Controllers, etc. */

extern okapi::ChassisControllerIntegrated drivetrain;
extern okapi::Controller masterController;

extern BaseIntakeController* intakeController;
extern BaseShooterController* shooterController;
extern BaseShooterAngleController* shooterAngleController;

#endif