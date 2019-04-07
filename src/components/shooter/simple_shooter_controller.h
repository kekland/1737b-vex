#ifndef SIMPLE_SHOOTER_CONTROLLER_H_
#define SIMPLE_SHOOTER_CONTROLLER_H_

#include "main.h"

class SimpleShooterController : public BaseShooterController
{
public:
  SimpleShooterController(okapi::Motor& motor): BaseShooterController(motor) {};
  void control(ShooterState state) override;

  void shootOnce() override;

  void shootTwice() override;
};

#endif