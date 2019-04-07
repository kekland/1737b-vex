#pragma once
#ifndef SIMPLE_INTAKE_CONTROLLER_H_
#define SIMPLE_INTAKE_CONTROLLER_H_

#include "main.h"

class SimpleIntakeController : public BaseIntakeController
{
public:
  SimpleIntakeController(okapi::Motor& motor, double maxVel): BaseIntakeController(motor, maxVel) {};
  void control(IntakeDirection direction) override;
};

#endif