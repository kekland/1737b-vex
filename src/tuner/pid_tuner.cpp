#include "main.h"
#include "../components/vision/vision_driving.h"
#include "../autonomous/autonomous_controller.h"

using namespace okapi;

void tune()
{
  double kp = 0.119000;
  double ki = 0.010000;
  double kd = 0.000010;
  while (true)
  {
    drivetrain->tank(masterController->getAnalog(ControllerAnalog::leftY),
                     masterController->getAnalog(ControllerAnalog::rightY));

    double modifier = 1.0;

    if(masterController->getDigital(ControllerDigital::Y)) {
      modifier = 10.0;
    }

    if (masterController->getDigital(ControllerDigital::L1))
    {
      kp += 0.00001 * modifier;
    }
    else if (masterController->getDigital(ControllerDigital::L2))
    {
      kp -= 0.00001 * modifier;
    }

    if (masterController->getDigital(ControllerDigital::R1))
    {
      ki += 0.00001 * modifier;
    }
    else if (masterController->getDigital(ControllerDigital::R2))
    {
      ki -= 0.00001 * modifier;
    }

    if (masterController->getDigital(ControllerDigital::up))
    {
      kd += 0.00001 * modifier;
    }
    else if (masterController->getDigital(ControllerDigital::down))
    {
      kd -= 0.00001 * modifier;
    }

    if (masterController->getDigital(ControllerDigital::X))
    {
      shooterController->shootOnce();
    }

    pros::lcd::print(0, "%f %f %f", kp, ki, kd);
    pros::lcd::print(1, "%f", gyro.get() / 10.0);
    flagZoomingController->setGains(kp, ki, kd);
    //rightDriveController->setGains(kp, ki, kd);

    /*if (masterController->getDigital(ControllerDigital::B))
    {
      turn(90.0_deg, 1.0);
    }
    if (masterController->getDigital(ControllerDigital::A))
    {
      drive(5_ft);
    }
    if (masterController->getDigital(ControllerDigital::Y))
    {
      drive(2_ft);
    }*/

    if (masterController->getDigital(ControllerDigital::B))
    {
      zoomForFlag(Flag::blue);
    }

    pros::delay(20);

    continue;
  }
}
