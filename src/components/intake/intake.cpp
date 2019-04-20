#include "main.h"

BaseIntakeController::BaseIntakeController(const okapi::Motor &intakeMotor, double maxVel)
{
  motor = std::make_shared<okapi::Motor>(intakeMotor);
  maxVelocity = maxVel;
};

void BaseIntakeController::getBallUntilBallIsInIntake(void *params)
{
  int startTime = pros::millis();
  while (true)
  {
    if (isBallInIntake() || pros::millis() - startTime > 6000)
    {
      break;
    }

    control(IntakeDirection::up);

    pros::delay(1);
  }

  control(IntakeDirection::down);
  
  pros::delay(100);

  control(IntakeDirection::stop);
}

void BaseIntakeController::releaseBallUntilBallIsInIntake(void *params)
{
  int startTime = pros::millis();
  while (true)
  {
    if (isBallInIntake() || pros::millis() - startTime > 6000)
    {
      break;
    }

    control(IntakeDirection::down);

    pros::delay(1);
  }

  control(IntakeDirection::up);
  
  pros::delay(100);

  control(IntakeDirection::stop);
}