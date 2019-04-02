#ifndef BASIC_SHOOTER_CONTROLLER_H_
#define BASIC_SHOOTER_CONTROLLER_H_

#include "main.h"

class SimpleShooterController : public BaseShooterController
{
public:
  SimpleShooterController(Motor& motor): BaseShooterController(motor) {};
  void control(ShooterState state)
  {
    motor->moveVoltage(12000 * state);
  };
};

#endif