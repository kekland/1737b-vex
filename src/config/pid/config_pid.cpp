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

  const double drivingKp = 0.0025;
  const double drivingKi = 0.001;
  const double drivingKd = 0.00013;

  leftDriveController = std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.0, 0.0, 0.0, 0.0));
  rightDriveController = std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.0, 0.0, 0.0, 0.0));

  turnController =
      std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.0128, 0.001, 0.00018, 0.0));

  flagAimingController =
      std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.003, 0.025, 0.0001));
  flagZoomingController =
      std::make_shared<okapi::IterativePosPIDController>(IterativeControllerFactory::posPID(0.119, 0.01, 0.0001));

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