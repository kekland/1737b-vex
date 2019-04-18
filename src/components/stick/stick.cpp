#include "main.h"

BaseStickController::BaseStickController(okapi::Motor& stickMotor) {
  motor = std::make_shared<okapi::Motor>(stickMotor);
};