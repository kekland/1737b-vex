#include "main.h"
#include "simple_intake_controller.h"

void SimpleIntakeController::control(IntakeDirection direction)
{
  motor->moveVelocity(static_cast<int>(direction) * maxVelocity);
};