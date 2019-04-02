#ifndef SHOOTER_H_
#define SHOOTER_H_

#include "main.h"

enum ShooterState
{
  shoot = 1,
  stop = 0,
};

class BaseShooterController
{
public:
  BaseShooterController(Motor&);
  virtual void control(ShooterState) = 0;

protected:
  std::shared_ptr<Motor> motor;
};

BaseShooterController::BaseShooterController(Motor& shooterMotor) {
  motor = std::make_shared<Motor>(shooterMotor);
}

#endif