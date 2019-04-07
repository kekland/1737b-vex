#include "main.h"

using namespace okapi;
/*
  Autonomous driving
*/

const double drivingKp = 0.048;
const double drivingKi = 0.0;
const double drivingKd = 0.00013;

/* Do not change ganis for those controllers - their gains are copied from above */
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

  leftDriveController.setGains(drivingKp, drivingKi, drivingKd);
  rightDriveController.setGains(drivingKp, drivingKi, drivingKd);

  info("Finished configuration", "config_pid");
}