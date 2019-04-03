#include "main.h"

BaseShooterController::BaseShooterController(okapi::Motor& shooterMotor) {
  motor = std::make_shared<okapi::Motor>(shooterMotor);
};