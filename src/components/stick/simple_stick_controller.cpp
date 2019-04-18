#include "main.h"
#include "simple_stick_controller.h"

void SimpleStickController::control(StickState state)
{
  double target = 0.0;
  if(state == StickState::zero) {
    target = 0.0;
  }
  else if(state == StickState::descore) {
    target = 613.0;
  }
  else if(state == StickState::ball) {
    target = 1116.0;
  }
  else if(state == StickState::cap) {
    target = 1038.0;
  }
  else if(state == StickState::skills) {
    target = 992.0;
  }
  else if(state == StickState::skillsUp) {
    target = 800.0;
  }
  else if(state == StickState::floor) {
    target = 1150.0;
  }
  else if(state == StickState::flag) {
    target = 710.0;
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
  driveLeft->moveVoltage(3150);
  driveRight->moveVoltage(3150);
  controlSet(-0.85);
  pros::delay(285);
  controlSet(0.0);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);
}