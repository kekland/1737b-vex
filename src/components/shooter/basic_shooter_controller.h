#ifndef BASIC_SHOOTER_CONTROLLER_H_
#define BASIC_SHOOTER_CONTROLLER_H_

#include "main.h"

class SimpleShooterController : public BaseShooterController
{
public:
  SimpleShooterController(okapi::Motor& motor): BaseShooterController(motor) {};
  void control(ShooterState state) override
  {
    motor->moveVoltage(12000 * static_cast<int>(state));
  };
};

#endif