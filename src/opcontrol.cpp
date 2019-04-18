#include "main.h"
#include "./autonomous/autonomous_controller.h"
using namespace okapi;

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
  }
  else if (masterController->getDigital(ControllerDigital::R1))
  {
    opcontrolState->addTask(aimAndZoom2AutomatedTask);
  }
  else if (masterController->getDigital(ControllerDigital::R2))
  {
    shooterController->shootTwice();
    //opcontrolState->addTask(shootTwiceAutomatedTask);
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

void control()
{
  bool rumbled = false;
  gameState->driverStarted();
  while (true)
  {
    // Analog sticks
    if (opcontrolState->drivetrainEnabled)
    {
      drivetrain->tank(masterController->getAnalog(ControllerAnalog::leftY),
                       masterController->getAnalog(ControllerAnalog::rightY), 0.09);
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
    if (partnerController->getDigital(ControllerDigital::Y))
    {
      stickController->control(StickState::zero);
    }
    else if(partnerController->getDigital(ControllerDigital::up)) {
      stickController->control(StickState::descore);
    }
    else if(partnerController->getDigital(ControllerDigital::down)) {
      stickController->control(StickState::cap);
    }
    else if(partnerController->getDigital(ControllerDigital::A)) {
      stickController->control(StickState::ball);
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

void opcontrol()
{
  info("Opcontrol start.", "opcontrol");
  //tune();
  control();
}
