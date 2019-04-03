#ifndef BASIC_SHOOTER_ANGLE_CONTROLLER_H_
#define BASIC_SHOOTER_ANGLE_CONTROLLER_H_

#include "main.h"

class SimpleShooterAngleController : public BaseShooterAngleController
{
public:
  SimpleShooterAngleController(okapi::AsyncPosIntegratedController & controller, std::initializer_list<double> shooterPositions)
      : BaseShooterAngleController(controller, shooterPositions){};
  
  void control(ShooterAngle angle) override
  {
    double position = positions[static_cast<int>(angle)];
    motorController->setTarget(position);
  };
};

#endif