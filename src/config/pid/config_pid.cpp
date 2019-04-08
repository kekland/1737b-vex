#include "main.h"

using namespace okapi;
/*
  Autonomous driving
*/

/* Do not change gains for those controllers - their gains are copied from above */
std::shared_ptr<okapi::IterativePosPIDController> leftDriveController;
std::shared_ptr<okapi::IterativePosPIDController> rightDriveController;

std::shared_ptr<okapi::IterativePosPIDController> turnController;

/*
  Autonomous aiming
*/
std::shared_ptr<okapi::IterativePosPIDController> flagAimingController;

std::shared_ptr<okapi::IterativePosPIDController> flagZoomingController;

void configure_pid()
{
  info("Starting configuration", "config_pid");

  const double drivingKp = 0.048;
  const double drivingKi = 0.0;
  const double drivingKd = 0.00013;

  leftDriveController = std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.0, 0.0, 0.0, 0.0));
  rightDriveController = std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.0, 0.0, 0.0, 0.0));

  turnController =
      std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.0124, 0.0, 0.00018, 0.0));

  flagAimingController =
      std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.01, 0.0, 0.0));

  flagZoomingController =
      std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.01, 0.0, 0.0));

  // Set gains
  leftDriveController->setGains(drivingKp, drivingKi, drivingKd);
  rightDriveController->setGains(drivingKp, drivingKi, drivingKd);

  // Set output limits for controllers
  leftDriveController->setOutputLimits(0.5, -0.5);
  rightDriveController->setOutputLimits(0.5, -0.5);
  turnController->setOutputLimits(0.5, -0.5);
  flagAimingController->setOutputLimits(0.5, -0.5);
  flagZoomingController->setOutputLimits(0.5, -0.5);

  info("Finished configuration", "config_pid");
}