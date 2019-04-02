#include "main.h"

using namespace okapi;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
  while (true)
  {
    drivetrain.tank(masterController.getAnalog(ControllerAnalog::leftY),
                    masterController.getAnalog(ControllerAnalog::rightY));

    if (masterController.getDigital(ControllerDigital::up))
    {
      shooterAngleController->control(ShooterAngle::upFlag);
    }
    else if (masterController.getDigital(ControllerDigital::down))
    {
      shooterAngleController->control(ShooterAngle::downFlag);
    }

    if (masterController.getDigital(ControllerDigital::R2))
    {
      shooterController->control(ShooterState::shoot);
    }
    else
    {
      shooterController->control(ShooterState::stop);
    }

    if (masterController.getDigital(ControllerDigital::L1))
    {
      intakeController->control(IntakeDirection::up);
    }
    else if (masterController.getDigital(ControllerDigital::L2))
    {
      intakeController->control(IntakeDirection::down);
    }
    else
    {
      intakeController->control(IntakeDirection::stop);
    }

    pros::delay(20);
  }
}
