#include "main.h"
#include "../../components/intake/simple_intake_controller.h"
#include "../../components/shooter/simple_shooter_controller.h"
#include "../../components/shooterAngle/simple_shooter_angle_controller.h"
#include "../motors/config_motors.h"

std::shared_ptr<okapi::ChassisControllerIntegrated> drivetrain;

BaseIntakeController *intakeController;

std::shared_ptr<okapi::AsyncPosIntegratedController> _shooterAngleController;
BaseShooterAngleController *shooterAngleController;
SimpleShooterController *shooterController;

void configure_controllers()
{
  info("Starting configuration", "config_controllers");

  drivetrain = okapi::ChassisControllerFactory::createPtr(*driveLeft, *driveRight, driveGearset, okapi::ChassisScales({4_in, 40_cm}));

  intakeController = new SimpleIntakeController(*intake, 200.0);

  shooterAngle->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

  _shooterAngleController = std::make_shared<okapi::AsyncPosIntegratedController>(
      okapi::AsyncControllerFactory::posIntegrated(*shooterAngle, 100));
  shooterAngleController = new SimpleShooterAngleController(*_shooterAngleController, {15.0, 60.0});

  shooterController = new SimpleShooterController(*shooter);

  drivetrain->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

  info("Finished configuration", "config_controllers");
}