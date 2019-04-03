#include "main.h"

BaseIntakeController::BaseIntakeController(const okapi::Motor& intakeMotor, double maxVel) {
  motor = std::make_shared<okapi::Motor>(intakeMotor);
  maxVelocity = maxVel;
};