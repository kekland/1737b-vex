#include "main.h"

BaseIntakeController::BaseIntakeController(const okapi::Motor &intakeMotor, double maxVel)
{
  motor = std::make_shared<okapi::Motor>(intakeMotor);
  maxVelocity = maxVel;
};

void BaseIntakeController::getBallUntilBallIsInIntake(void *params)
{
  while (true)
  {
    if (isBallInIntake())
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