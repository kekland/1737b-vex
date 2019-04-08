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

void controlShooterAngle()
{
  if (masterController->getDigital(ControllerDigital::up))
  {
    shooterAngleController->control(ShooterAngle::upFlag);
  }
  else if (masterController->getDigital(ControllerDigital::down))
  {
    shooterAngleController->control(ShooterAngle::downFlag);
  }
}

void controlShooter()
{
  if (masterController->getDigital(ControllerDigital::R2))
  {
    shooterController->control(ShooterState::shoot);
  }
  else if (masterController->getDigital(ControllerDigital::R1))
  {
    Flag flag = gameState->getOpposingFlag();
    opcontrolState->addTask(shootTwiceTask, &flag);
  }
  else
  {
    shooterController->control(ShooterState::stop);
  }
}

void controlIntake()
{
  if (masterController->getDigital(ControllerDigital::L1))
  {
    intakeController->control(IntakeDirection::up);
  }
  else if (masterController->getDigital(ControllerDigital::L2))
  {
    intakeController->control(IntakeDirection::down);
  }
  else
  {
    intakeController->control(IntakeDirection::stop);
  }
}

void opcontrol()
{
  /*if (TUNING_PID)
  {
    warn("Detected that we are tuning PID now. Don't forget to turn this off.", "opcontrol");
    info("Waiting for R2 button press", "opcontrol");
    while (true)
    {
      if (masterController->getDigital(ControllerDigital::R2))
      {
        tune();
        return;
      }
    }
    return;
  }*/

  info("Opcontrol start", "opcontrol");
  bool rumbled = false;
  gameState->driverStarted();

  while (true)
  {
    // Analog sticks
    if (opcontrolState->drivetrainEnabled)
    {
      drivetrain->tank(masterController->getAnalog(ControllerAnalog::leftY),
                       masterController->getAnalog(ControllerAnalog::rightY));
    }
    if (opcontrolState->shooterAngleEnabled)
    {
      controlShooterAngle();
    }
    if (opcontrolState->shooterEnabled)
    {
      controlShooter();
    }
    if (opcontrolState->intakeEnabled)
    {
      controlIntake();
    }
    
    if (masterController->getDigital(ControllerDigital::left))
    {
      opcontrolState->killTask();
    }

    // Temporary
    if (masterController->getDigital(ControllerDigital::right))
    {
      while (masterController->getDigital(ControllerDigital::right))
      {
        pros::delay(20);
      }

      Alliance alliance = gameState->getAlliance();
      gameState->setAlliance(alliance == Alliance::red ? Alliance::blue : Alliance::red);
    }
    pros::delay(25);
  }
  /*while (true)
  {
    info("Opcontrol tick", "opcontrol");
    // Analog sticks
    if (opcontrolState->drivetrainEnabled)
    {
      drivetrain->tank(masterController->getAnalog(ControllerAnalog::leftY),
                       masterController->getAnalog(ControllerAnalog::rightY));
    }
    if (opcontrolState->shooterAngleEnabled)
    {
      controlShooterAngle();
    }
    if (opcontrolState->shooterEnabled)
    {
      controlShooter();
    }
    if (opcontrolState->intakeEnabled)
    {
      controlIntake();
    }

    if (masterController->getDigital(ControllerDigital::left))
    {
      opcontrolState->killTask();
    }

    // Temporary
    if (masterController->getDigital(ControllerDigital::right))
    {
      while (masterController->getDigital(ControllerDigital::right))
      {
        pros::delay(20);
      }

      Alliance alliance = gameState->getAlliance();
      gameState->setAlliance(alliance == Alliance::red ? Alliance::blue : Alliance::red);
    }

    if (masterController->getDigital(ControllerDigital::left))
    {
      autonomous();
    }
    pros::delay(25);
  }*/
}
