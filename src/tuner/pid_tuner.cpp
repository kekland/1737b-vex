#include "main.h"
#include "../components/vision/vision_driving.h"
#include "../autonomous/autonomous_controller.h"

using namespace okapi;

void tune()
{
  double kp = 0.005730;
  double ki = 0.016330;
  double kd = 0.000040;
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
      
    }
    else {

    }

    pros::lcd::print(0, "%f %f %f", kp, ki, kd);
    pros::lcd::print(1, "%f", gyro.get() / 10.0);
    flagAimingController->setGains(kp, ki, kd);
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
      aimForFlag(Flag::blue);
    }

    pros::delay(20);

    continue;
  }
}
