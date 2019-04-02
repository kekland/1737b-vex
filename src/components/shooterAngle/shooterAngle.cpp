#include "main.h"

double shootPositions[2] = {45, 60};

void controlShooterAngle(ShooterAngle angle) {
  double desiredAngle = shootPositions[(int)angle];
  shooterAngleController.setTarget(desiredAngle);
}