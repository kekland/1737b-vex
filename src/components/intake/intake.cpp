#include "main.h"
#include "../../global.h"
#include "intake.h"

double maxIntakeVelocity = 200.0;

void control(IntakeDirection direction) {
  intake.move_velocity((int)direction * maxIntakeVelocity);
}