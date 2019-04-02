#include "main.h";

using namespace okapi;

/* Basic data such as gearsets, drive scales, etc */

AbstractMotor::gearset driveGearset = AbstractMotor::gearset::green;
ChassisScales driveScales = ChassisScales({4.0_in, 32.0_cm});

/* Motors and MotorGroups */

Motor driveLeftFront = Motor(1, false, driveGearset);
Motor driveLeftBack = Motor(2, false, driveGearset);
Motor driveRightFront = Motor(9, true, driveGearset);
Motor driveRightBack = Motor(10, true, driveGearset);

MotorGroup driveLeft = MotorGroup({driveLeftBack, driveLeftFront});
MotorGroup driveRight = MotorGroup({driveLeftBack, driveLeftFront});

/* Higher-level stuff like ChassisControllers, Controllers, etc. */

auto drivetrain = ChassisControllerFactory::create(driveLeft, driveRight, driveGearset, driveScales);