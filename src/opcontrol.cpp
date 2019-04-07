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
  gameState.driverStarted();
  while (true)
  {
    // Analog sticks
    drivetrain.tank(masterController.getAnalog(ControllerAnalog::leftY),
                    masterController.getAnalog(ControllerAnalog::rightY));

    // Shooter angle
    if (masterController.getDigital(ControllerDigital::up))
    {
      shooterAngleController->control(ShooterAngle::upFlag);
    }
    else if (masterController.getDigital(ControllerDigital::down))
    {
      shooterAngleController->control(ShooterAngle::downFlag);
    }

    // Shooting
    if (masterController.getDigital(ControllerDigital::R2))
    {
      shooterController->control(ShooterState::shoot);
    }
    else if (masterController.getDigital(ControllerDigital::R1))
    {
      shootTwiceAutomated(gameState.getOpposingFlag());
    }
    else
    {
      shooterController->control(ShooterState::stop);
    }

    // Intake
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

    // Temporary
    if (masterController.getDigital(ControllerDigital::right))
    {
      while (masterController.getDigital(ControllerDigital::right))
      {
        pros::delay(20);
      }
      
      Alliance alliance = gameState.getAlliance();
      gameState.setAlliance(alliance == Alliance::red ? Alliance::blue : Alliance::red);
    }

    if (masterController.getDigital(ControllerDigital::left))
    {
      autonomous();
    }
    
    pros::delay(25);
  }
}
