#pragma once
#ifndef SHOOTERANGLE_H_
#define SHOOTERANGLE_H_

#include "main.h"

enum class ShooterAngle
{
  upFlag = 0,
  downFlag = 1
};

class BaseShooterAngleController
{
public:
  BaseShooterAngleController(okapi::AsyncPosIntegratedController& controller, std::initializer_list<double> anglePositions);
  virtual void control(ShooterAngle angle) = 0;
  void waitUntilSettled();
  ShooterAngle currentAngle;
  okapi::AsyncPosIntegratedController* motorController;

protected:
  double positions[2];
};

#endif