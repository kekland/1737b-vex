#include "main.h"

OpControlState::OpControlState()
{
  drivetrainEnabled = true;
  shooterEnabled = true;
  shooterAngleEnabled = true;
  intakeEnabled = true;
  currentTask = NULL;
}

void OpControlState::addTask(pros::task_fn_t function, void *parameters)
{
  info("Adding task.", "addTask");
  if (currentTask != NULL)
  {
    error("currentTask is not NULL.", "addTask");
    return;
  }
  currentTask = new pros::Task(function, parameters);
  info("Added task.", "addTask");
}

void OpControlState::gracefulEndTask() {
  if (currentTask == NULL)
  {
    error("currentTask is NULL.", "gracefulEndTask");
    return;
  }
  drivetrainEnabled = true;
  shooterEnabled = true;
  shooterAngleEnabled = true;
  intakeEnabled = true;
  currentTask = NULL;
}

void OpControlState::killTask()
{
  info("Killing task.", "killTask");
  drivetrainEnabled = true;
  shooterEnabled = true;
  shooterAngleEnabled = true;
  intakeEnabled = true;

  if (currentTask == NULL)
  {
    error("currentTask is NULL.", "killTask");
    return;
  }

  int state = currentTask->get_state();
  printf("Task %s state: %d\n", currentTask->get_name(), state);
  if (state == pros::E_TASK_STATE_RUNNING)
  {
    info("Suspending task because of its state.", "killTask");
    currentTask->suspend();
  }
  state = currentTask->get_state();

  printf("Task state: %d\n", state);
  if (state == pros::E_TASK_STATE_READY ||
      state == pros::E_TASK_STATE_BLOCKED || state == pros::E_TASK_STATE_SUSPENDED)
  {
    info("Removing task because of its state.", "killTask");
    currentTask->suspend();
    currentTask->remove();
  }
  info("Setting task pointer to NULL.", "killTask");
  currentTask = NULL;
  info("Killed task.", "killTask");
}

std::unique_ptr<OpControlState> opcontrolState;