#ifndef CONFIG_H_
#define CONFIG_H_

#include "main.h"

using namespace okapi;

/* Higher-level stuff like ChassisControllers, Controllers, etc. */

extern ChassisControllerIntegrated drivetrain;
extern Controller masterController;

extern std::shared_ptr<BaseIntakeController> intakeController;
extern std::shared_ptr<BaseShooterController> shooterController;
extern std::shared_ptr<BaseShooterAngleController> shooterAngleController;

#endif