#include "main.h"

using namespace okapi;

/* Basic data such as gearsets, drive scales, etc */

extern AbstractMotor::gearset driveGearset;
extern ChassisScales driveScales;

/* Motors and MotorGroups */

extern Motor driveLeftFront;
extern Motor driveLeftBack;
extern Motor driveRightFront;
extern Motor driveRightBack;

extern MotorGroup driveLeft;
extern MotorGroup driveRight;

extern Motor shooter;
extern Motor intake;

/* Higher-level stuff like ChassisControllers, Controllers, etc. */

extern ChassisControllerIntegrated drivetrain;
extern Controller masterController;

extern AsyncPosIntegratedController shooterAngleController;