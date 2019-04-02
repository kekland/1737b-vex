#include "main.h";

using namespace okapi;

/* Basic data such as gearsets, drive scales, etc */

AbstractMotor::gearset driveGearset = AbstractMotor::gearset::green;
okapi::ChassisScales driveScales = okapi::ChassisScales({4.0_in, 32.0_cm});

/* Motors and MotorGroups */

okapi::Motor driveLeftFront = Motor(1, false, driveGearset);
okapi::Motor driveLeftBack = Motor(2, false, driveGearset);
okapi::Motor driveRightFront = Motor(9, true, driveGearset);
okapi::Motor driveRightBack = Motor(10, true, driveGearset);

okapi::MotorGroup driveLeft = MotorGroup({driveLeftBack, driveLeftFront});
okapi::MotorGroup driveRight = MotorGroup({driveLeftBack, driveLeftFront});

/* Higher-level stuff like ChassisControllers, Controllers, etc. */

auto drivetrain = okapi::ChassisControllerFactory::create(driveLeft, driveRight, driveGearset, driveScales);