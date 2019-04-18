#pragma once
#ifndef SIMPLE_STICK_CONTROLLER_H_
#define SIMPLE_STICK_CONTROLLER_H_

#include "main.h"

class SimpleStickController : public BaseStickController
{
public:
  SimpleStickController(okapi::Motor& motor): BaseStickController(motor) {
    controller = std::make_shared<AsyncPosIntegratedController>(AsyncControllerFactory::posIntegrated(motor, 200));
  }
  void control(StickState state) override;
  void controlSet(double velocity) override;
  void flipCap() override;

protected:
  std::shared_ptr<AsyncPosIntegratedController> controller;
};

#endif