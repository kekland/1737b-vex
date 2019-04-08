#pragma once
#ifndef PID_TUNER_H_
#define PID_TUNER_H_

#define TUNING_PID false
#include "main.h"
using namespace okapi;

void tune();

class DrivetrainForwardController : public ControllerOutput<double>
{
public:
  virtual void controllerSet(double ivalue) override;
};
class DrivetrainTurnController : public ControllerOutput<double>
{
public:
  virtual void controllerSet(double ivalue) override;
};
#endif