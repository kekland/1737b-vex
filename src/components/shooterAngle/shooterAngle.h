#ifndef SHOOTERANGLE_H_
#define SHOOTERANGLE_H_

#include "main.h"

enum ShooterAngle
{
  upFlag = 1,
  downFlag = 0,
};

class BaseShooterAngleController
{
public:
  BaseShooterAngleController(AsyncPositionController<double, double>&, std::initializer_list<double>);
  virtual void control(ShooterAngle) = 0;

protected:
  std::shared_ptr<AsyncPositionController<double, double>> motorController;
  double positions[2];
};

BaseShooterAngleController::BaseShooterAngleController(AsyncPositionController<double, double>& controller, std::initializer_list<double> anglePositions)
{
  motorController = std::make_shared<AsyncPositionController<double, double>>(controller);
  for (std::initializer_list<double>::iterator it = anglePositions.begin(), int i = 0; it != anglePositions.end(); it++, i++)
  {
    positions[i] = *it;
  }
}

#endif