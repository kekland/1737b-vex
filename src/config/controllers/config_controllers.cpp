#include "main.h"
#include "../../components/intake/simple_intake_controller.h"
#include "../../components/shooter/simple_shooter_controller.h"
#include "../../components/shooterAngle/simple_shooter_angle_controller.h"
#include "../motors/config_motors.h"

okapi::ChassisControllerIntegrated drivetrain = okapi::ChassisControllerFactory::create(driveLeft, driveRight, driveGearset, driveScales);

auto _intakeController = SimpleIntakeController(intake, 200.0);
BaseIntakeController *intakeController = &_intakeController;

okapi::AsyncPosIntegratedController _saController = okapi::AsyncControllerFactory::posIntegrated(shooterAngle, 100);
auto _shooterAngleController = SimpleShooterAngleController(_saController, {25.0, 60.0});
BaseShooterAngleController *shooterAngleController = &_shooterAngleController;

auto _shooterController = SimpleShooterController(shooter);
BaseShooterController *shooterController = &_shooterController;

void configure_controllers() {
  info("Starting configuration", "config_controllers");
  drivetrain.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  info("Finished configuration", "config_controllers");
}