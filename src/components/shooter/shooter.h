#ifndef SHOOTER_H_
#define SHOOTER_H_

#include "main.h"

enum class ShooterState
{
  shoot = 1,
  stop = 0
};

class BaseShooterController
{
public:
  BaseShooterController(okapi::Motor& shooterMotor);
  virtual void control(ShooterState state) = 0;

protected:
  std::shared_ptr<okapi::Motor> motor;
};

#endif