#include "main.h"

using namespace okapi;
/*
  Autonomous driving
*/

const double drivingKp = 0.048;
const double drivingKi = 0.0;
const double drivingKd = 0.00013;

/* Do not change gains for those controllers - their gains are copied from above */
okapi::IterativePosPIDController leftDriveController = IterativeControllerFactory::posPID(0.0, 0.0, 0.0, 0.0);
okapi::IterativePosPIDController rightDriveController = IterativeControllerFactory::posPID(0.0, 0.0, 0.0, 0.0);

okapi::IterativePosPIDController turnController = IterativeControllerFactory::posPID(0.0124, 0.0, 0.00018, 0.0);


/*
  Autonomous aiming
*/
okapi::IterativePosPIDController flagAimingController = IterativeControllerFactory::posPID(0.01, 0.0, 0.0);
okapi::IterativePosPIDController flagZoomingController = IterativeControllerFactory::posPID(0.01, 0.0, 0.0);

void configure_pid() {
  info("Starting configuration", "config_pid");

  // Set gains
  leftDriveController.setGains(drivingKp, drivingKi, drivingKd);
  rightDriveController.setGains(drivingKp, drivingKi, drivingKd);

  // Set output limits for controllers
  leftDriveController.setOutputLimits(0.5, -0.5);
  rightDriveController.setOutputLimits(0.5, -0.5);
  turnController.setOutputLimits(0.5, -0.5);
  flagAimingController.setOutputLimits(0.5, -0.5);
  flagZoomingController.setOutputLimits(0.5, -0.5);

  info("Finished configuration", "config_pid");
}