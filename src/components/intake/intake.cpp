#include "main.h"

double maxIntakeVelocity = 200.0;

void controlIntake(IntakeDirection direction) {
  intake.move_velocity((int)direction * maxIntakeVelocity);
}