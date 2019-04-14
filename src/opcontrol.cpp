#include "main.h"
#include "./autonomous/autonomous_controller.h"
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

void testTask(void *args)
{
  while (true)
  {
    info("I am running!", "testTask");
    pros::delay(100);
  }
}

void controlShooterAngle()
{
  if (masterController->getDigital(ControllerDigital::up))
  {
    shooterAngleController->control(ShooterAngle::downFlag);
  }
  else if (masterController->getDigital(ControllerDigital::down))
  {
    shooterAngleController->control(ShooterAngle::upFlag);
  }
}

void controlShooter()
{
  if (masterController->getDigital(ControllerDigital::A))
  {
    shooterController->shootOnce();
    //shooterController->control(ShooterState::shoot);
  }
  else if (masterController->getDigital(ControllerDigital::R1))
  {
    //opcontrolState->addTask(testTask, NULL);
    measureAreaOfObjects();
    //Flag flag = gameState->getOpposingFlag();
    //opcontrolState->addTask(shootTwiceAutomatedTask, &flag);
  }
  else if (masterController->getDigital(ControllerDigital::R2))
  {
    opcontrolState->addTask(shootTwiceTask, NULL);
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
  info("Opcontrol start.", "opcontrol");
  bool rumbled = false;
  gameState->driverStarted();
  
  
  //TODO: Don't forget to remove this
  //measureAreaOfObjects();
  
  //tune();
  while (true)
  {
    // Analog sticks
    //printf("%f\n", shooter->getPosition());
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

    if (masterController->getDigital(ControllerDigital::B))
    {
      autonomous();
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

    if (gameState->getTimeFromGameStartSeconds() > 105.0 && !rumbled)
    {
      masterController->rumble("-.- ");
      rumbled = true;
    }

    pros::delay(25);
  }
}
