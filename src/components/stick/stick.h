#pragma once
#ifndef STICK_H_
#define STICK_H_

#include "main.h"

enum class StickState
{
  zero = 0,
  descore = 1,
  ball = 2,
  cap = 3,
  skills = 4,
  skillsUp = 5,
  floor = 6,
  flag = 7,
  halfUp = 8,
  zhangir = 9,
};

class BaseStickController
{
public:
  BaseStickController(okapi::Motor& shooterMotor);
  virtual void control(StickState state) = 0;
  virtual void controlSet(double velocity) = 0;
  virtual void flipCap() = 0;
protected:
  std::shared_ptr<okapi::Motor> motor;
};

#endif