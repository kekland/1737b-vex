#include "main.h"
#include "simple_stick_controller.h"

void SimpleStickController::control(StickState state)
{
  double target = 0.0;
  if(state == StickState::zero) {
    target = 0.0;
  }
  else if(state == StickState::descore) {
    target = 471.0;
  }
  else if(state == StickState::ball) {
    target = 748.0;
  }
  else if(state == StickState::cap) {
    target = 723.0;
  }
  else if(state == StickState::skills) {
    target = 684.0;
  }
  else if(state == StickState::skillsUp) {
    target = 627.0;
  }
  else if(state == StickState::floor) {
    target = 773.0;
  }
  else if(state == StickState::flag) {
    target = 583.0;
  }
  controller->setTarget(target);
  controller->flipDisable(false);
  controller->waitUntilSettled();
}

void SimpleStickController::controlSet(double velocity) {
  controller->flipDisable(true);
  motor->controllerSet(velocity);
}

void SimpleStickController::flipCap() {
  control(StickState::floor);
  controller->waitUntilSettled();
  driveLeft->moveVoltage(2750);
  driveRight->moveVoltage(2750);
  controlSet(-0.45);
  pros::delay(235);
  controlSet(0.0);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);
}