#include "main.h"

BaseShooterAngleController::BaseShooterAngleController(okapi::AsyncPosIntegratedController& controller, std::initializer_list<double> anglePositions)
{
  motorController = &controller;
  int i = 0;
  for (std::initializer_list<double>::iterator it = anglePositions.begin(); it != anglePositions.end(); it++)
  {
    positions[i] = *it;
    i++;
  }
};

void BaseShooterAngleController::waitUntilSettled() {
  motorController->waitUntilSettled();
}