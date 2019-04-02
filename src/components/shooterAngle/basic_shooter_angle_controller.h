#ifndef BASIC_SHOOTER_ANGLE_CONTROLLER_H_
#define BASIC_SHOOTER_ANGLE_CONTROLLER_H_

#include "main.h"

class SimpleShooterAngleController : public BaseShooterAngleController
{
public:
  SimpleShooterAngleController(AsyncPositionController<double, double>& controller, std::initializer_list<double> shooterPositions)
      : BaseShooterAngleController(controller, shooterPositions){};
  
  void control(ShooterAngle angle)
  {
    double position = positions[(int)angle];
    motorController->setTarget(position);
  };
};

#endif