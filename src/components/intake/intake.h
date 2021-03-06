#pragma once
#ifndef INTAKE_H_
#define INTAKE_H_

enum class IntakeDirection
{
  up = 1,
  stop = 0,
  down = -1,
};

class BaseIntakeController
{
public:
  BaseIntakeController(const okapi::Motor& intakeMotor, double maxVel);
  void setMaxVelocity(double);
  double getMaxVelocity();
  void getBallUntilBallIsInIntake(void* params);
  void releaseBallUntilBallIsInIntake(void* params);
  virtual void control(IntakeDirection direction) = 0;
  virtual bool isBallInIntake() = 0;

protected:
  double maxVelocity = 200.0;
  std::shared_ptr<okapi::Motor> motor;
};

#endif