#pragma once
#ifndef SIMPLE_SHOOTER_ANGLE_CONTROLLER_H_
#define SIMPLE_SHOOTER_ANGLE_CONTROLLER_H_

#include "main.h"

class SimpleShooterAngleController : public BaseShooterAngleController
{
public:
  SimpleShooterAngleController(okapi::AsyncPosIntegratedController & controller, std::initializer_list<double> shooterPositions)
      : BaseShooterAngleController(controller, shooterPositions){};
  void control(ShooterAngle angle) override;
};

#endif