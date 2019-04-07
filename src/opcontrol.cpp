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


int current_flag = RED_FLAG;
void opcontrol()
{
  shooterAngle.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  drivetrain.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
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
    else if (masterController.getDigital(ControllerDigital::R1))
    {
      shootTwiceAutomated(current_flag);
    }
    else
    {
      shooterController->control(ShooterState::stop);
    }

    if (masterController.getDigital(ControllerDigital::right))
    {
      while (masterController.getDigital(ControllerDigital::right))
      {
        pros::delay(20);
      }
      current_flag = (current_flag == RED_FLAG) ? BLUE_FLAG : RED_FLAG;
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

    if(masterController.getDigital(ControllerDigital::left)) {
      autonomous();
    }
    printf("%f\n", gyro.get());

    pros::delay(25);
  }
}
