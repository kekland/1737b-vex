#include "main.h"

using namespace okapi;
/*
  Autonomous driving
*/

/* Do not change gains for those controllers - their gains are copied from above */
std::shared_ptr<okapi::IterativePosPIDController> leftDriveController;
std::shared_ptr<okapi::IterativePosPIDController> rightDriveController;
std::shared_ptr<okapi::IterativePosPIDController> straightDriveController;

std::shared_ptr<okapi::IterativePosPIDController> turnController;

/*
  Autonomous aiming
*/
std::shared_ptr<okapi::IterativePosPIDController> flagAimingController;

std::shared_ptr<okapi::IterativePosPIDController> flagZoomingController;

void configure_pid()
{
  info("Starting configuration", "config_pid");

  const double drivingKp = 0.001840;
  const double drivingKi = -0.000070;
  const double drivingKd = -0.000230;

  leftDriveController = std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.0, 0.0, 0.0, 0.0));
  rightDriveController = std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.0, 0.0, 0.0, 0.0));
  straightDriveController = std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.000, 0.0, 0.0));
  turnController =
      std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.010000, 0.002080, 0.000020));

  flagAimingController =
      std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.003, 0.008, 0.0001));
  flagZoomingController =
      std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.119, 0.01, 0.00001));

  // Set gains
  leftDriveController->setGains(drivingKp, drivingKi, drivingKd);
  rightDriveController->setGains(drivingKp, drivingKi, drivingKd);

  // Set output limits for controllers
  leftDriveController->setOutputLimits(1.0, -1.0);
  rightDriveController->setOutputLimits(1.0, -1.0);
  turnController->setOutputLimits(1.0, -1.0);
  flagAimingController->setOutputLimits(0.25, -0.25);
  flagZoomingController->setOutputLimits(0.45, -0.45);

  info("Finished configuration", "config_pid");
}