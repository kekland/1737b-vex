#include "main.h"
#include "simple_shooter_angle_controller.h"

void SimpleShooterAngleController::control(ShooterAngle angle)
{
  double position = positions[static_cast<int>(angle)];
  motorController->setTarget(position);
  currentAngle = angle;
}