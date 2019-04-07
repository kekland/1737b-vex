#include "main.h"

using namespace okapi;
/* Basic data such as gearsets, drive scales, etc */

okapi::AbstractMotor::gearset driveGearset = okapi::AbstractMotor::gearset::green;
okapi::ChassisScales driveScales = okapi::ChassisScales({4.0_in, 40.0_cm});

/* Motors and MotorGroups */

okapi::Motor driveLeftFront = okapi::Motor(10, false, driveGearset);
okapi::Motor driveLeftBack = okapi::Motor(12, false, driveGearset);
okapi::Motor driveRightFront = okapi::Motor(17, true, driveGearset);
okapi::Motor driveRightBack = okapi::Motor(15, true, driveGearset);

okapi::MotorGroup driveLeft = okapi::MotorGroup({driveLeftBack, driveLeftFront});
okapi::MotorGroup driveRight = okapi::MotorGroup({driveRightBack, driveRightFront});

okapi::Motor intake = okapi::Motor(11, true, AbstractMotor::gearset::green);
okapi::Motor shooter = okapi::Motor(13, true, AbstractMotor::gearset::green);
okapi::Motor shooterAngle = okapi::Motor(19, false, AbstractMotor::gearset::green);

void configure_motors() {
  info("Starting configuration", "config_motors");

  driveLeft.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  driveRight.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  
  info("Finished configuration", "config_motors");
}