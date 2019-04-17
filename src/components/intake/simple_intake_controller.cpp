#include "main.h"
#include "simple_intake_controller.h"

void SimpleIntakeController::control(IntakeDirection direction)
{
  motor->moveVelocity(static_cast<int>(direction) * maxVelocity);
};

bool SimpleIntakeController::isBallInIntake() {
  int value = intakeLineSensor.get_value_calibrated();
  int midThird = 10;
  
  int diff = abs(lineSensorMid - value);

  printf("line %d, %d, %d\n", lineSensorMid, value, diff > midThird);
  
  return (diff > midThird);
};