#include "main.h"

OpControlState::OpControlState() {
  drivetrainEnabled = true;
  shooterEnabled = true;
  shooterAngleEnabled = true;
  intakeEnabled = true;
  currentTask = NULL;
}

void OpControlState::addTask(pros::task_fn_t function, void *parameters) {
  if(currentTask == NULL) {
    return;
  }
  auto task = pros::Task(function, parameters);
  currentTask = &task;
}

void OpControlState::killTask() {
  drivetrainEnabled = true;
  shooterEnabled = true;
  shooterAngleEnabled = true;
  intakeEnabled = true;

  if(currentTask == NULL) {
    return;
  }

  currentTask->remove();
  currentTask = NULL;
}

OpControlState opcontrolState = OpControlState();