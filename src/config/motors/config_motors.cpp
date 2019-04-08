#include "main.h"

using namespace okapi;
/* Basic data such as gearsets, drive scales, etc */

okapi::AbstractMotor::gearset driveGearset;
okapi::ChassisScales* driveScales;

/* Motors and MotorGroups */

okapi::Motor* driveLeftFront;
okapi::Motor* driveLeftBack;
okapi::Motor* driveRightFront;
okapi::Motor* driveRightBack;

okapi::MotorGroup* driveLeft;
okapi::MotorGroup* driveRight;

okapi::Motor* intake;
okapi::Motor* shooter;
okapi::Motor* shooterAngle;

void configure_motors() {
  info("Starting configuration", "config_motors");

  driveGearset = okapi::AbstractMotor::gearset::green;
  driveScales = new okapi::ChassisScales({4.0_in, 40.0_cm});

  driveLeftFront = new okapi::Motor(10, false, driveGearset);
  driveLeftBack = new okapi::Motor(12, false, driveGearset);
  driveRightFront = new okapi::Motor(17, true, driveGearset);
  driveRightBack = new okapi::Motor(15, true, driveGearset);
  driveLeft = new okapi::MotorGroup({*driveLeftBack, *driveLeftFront});
  driveRight = new okapi::MotorGroup({*driveRightBack, *driveRightFront});

  driveLeft->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  driveRight->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  
  intake = new okapi::Motor(11, true, AbstractMotor::gearset::green);
  shooter = new okapi::Motor(13, true, AbstractMotor::gearset::green);
  shooterAngle = new okapi::Motor(19, false, AbstractMotor::gearset::green);
  
  info("Finished configuration", "config_motors");
}