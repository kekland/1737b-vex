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
    target = 1140.0;
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
  controlSet(-1.0);
  pros::delay(200);
  controlSet(0.0);
}