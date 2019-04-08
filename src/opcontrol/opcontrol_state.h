#pragma once
#ifndef OPCONTROL_STATE_H_
#define OPCONTROL_STATE_H_

#include "main.h"

class OpControlState
{
public:
  OpControlState();

  bool drivetrainEnabled;
  bool shooterEnabled;
  bool shooterAngleEnabled;
  bool intakeEnabled;

  void addTask(pros::task_fn_t function, void *parameters = (void*)__null);
  void killTask();
  void gracefulEndTask();

  pros::Task* currentTask;
};

extern std::unique_ptr<OpControlState> opcontrolState;

#endif