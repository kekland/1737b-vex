#ifndef BASIC_SHOOTER_CONTROLLER_H_
#define BASIC_SHOOTER_CONTROLLER_H_

#include "main.h"

class SimpleShooterController : public BaseShooterController
{
public:
  SimpleShooterController(okapi::Motor& motor): BaseShooterController(motor) {};
  void control(ShooterState state) override
  {
    motor->moveVoltage(12000 * (int)state);
  };

  void shootOnce() override {
    motor->tarePosition();
    control(ShooterState::shoot);
    /*pros::delay(50);
    while(motor->getPosition() > 20.0) {
      printf("%d\n", motor->getPosition());
    }
    control(ShooterState::stop);
    pros::delay(10);*/
    pros::delay(600);
    control(ShooterState::stop);
    motor->tarePosition();
  }

  void shootTwice() override {
    shooterAngleController->control(ShooterAngle::upFlag);
    shootOnce();
    intakeController->control(IntakeDirection::up);
    pros::delay(200);
    shooterAngleController->control(ShooterAngle::downFlag);
    pros::delay(150);
    shootOnce();
  };
};

#endif