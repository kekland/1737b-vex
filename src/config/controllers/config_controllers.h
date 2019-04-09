#pragma once
#ifndef CONFIG_CONTROLLERS_H_
#define CONFIG_CONTROLLERS_H_

#include "main.h"
#include "../../components/shooter/simple_shooter_controller.h"

extern std::shared_ptr<okapi::ChassisControllerIntegrated> drivetrain;

extern BaseIntakeController* intakeController;
extern SimpleShooterController* shooterController;
extern BaseShooterAngleController* shooterAngleController;

void configure_controllers();

#endif