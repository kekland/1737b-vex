#pragma once
#ifndef PID_TUNER_H_
#define PID_TUNER_H_

#define TUNING_PID true

void tune();

class DrivetrainForwardController : public ControllerOutput<double>
{
public:
  void controllerSet(double value) override;
};
class DrivetrainTurnController : public ControllerOutput<double>
{
public:
  void controllerSet(double value) override;
};
#endif