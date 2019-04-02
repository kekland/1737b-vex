#ifndef INTAKE_H_
#define INTAKE_H_
#include "main.h"
enum IntakeDirection
{
  up = 1,
  stop = 0,
  down = -1,
};

class BaseIntakeController
{
public:
  BaseIntakeController(Motor&, double);
  void setMaxVelocity(double);
  double getMaxVelocity();
  virtual void control(IntakeDirection) = 0;

protected:
  double maxVelocity = 200.0;
  std::shared_ptr<Motor> motor;
};

BaseIntakeController::BaseIntakeController(Motor& intakeMotor, double maxVel) {
  motor = std::make_shared<Motor>(intakeMotor);
  maxVelocity = maxVel;
}

#endif