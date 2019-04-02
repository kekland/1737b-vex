#ifndef BASIC_INTAKE_CONTROLLER_H_
#define BASIC_INTAKE_CONTROLLER_H_

#include "main.h"

class SimpleIntakeController : public BaseIntakeController
{
public:
  SimpleIntakeController(Motor& motor, double maxVel): BaseIntakeController(motor, maxVel) {};
  void control(IntakeDirection direction)
  {
    motor->moveVelocity(direction * maxVelocity);
  };
};

#endif