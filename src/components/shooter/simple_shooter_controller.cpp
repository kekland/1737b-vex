#include "main.h"
#include "simple_shooter_controller.h"

void SimpleShooterController::control(ShooterState state)
{
  motor->moveVoltage(12000 * (int)state);
}

void SimpleShooterController::shootOnce()
{
  motor->tarePosition();
  control(ShooterState::shoot);
  pros::delay(600);
  control(ShooterState::stop);
  motor->tarePosition();
}

void SimpleShooterController::shootTwice()
{
  // If current angle is up - shoot up then down. If current angle is down, do in reverse.
  ShooterAngle nextAngle = (shooterAngleController->currentAngle == ShooterAngle::downFlag) ? ShooterAngle::upFlag : ShooterAngle::downFlag;

  // Wait until angle is settled and shoot
  shooterAngleController->waitUntilSettled();
  shootOnce();

  // Set the angle beforehand and start intaking the ball
  shooterAngleController->control(nextAngle);
  intakeController->control(IntakeDirection::up);
  pros::delay(250);

  // Wait until angle is settled and shoot
  shooterAngleController->waitUntilSettled();
  shootOnce();
}