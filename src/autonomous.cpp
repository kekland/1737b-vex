#include "main.h"
#include "./autonomous/autonomous_controller.h"
#include "./autonomous/autonomous_variants.h"
#include "./components/vision/vision_driving.h"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

//using void_f = void (*)();

//void_f autonomousVariants[] = {&autonomousFront1};

void shootTwice(void* param) {
  shooterController->shootOnce();
}
void autonomous()
{
  info("Autonomous start", "autonomous");
  //gameState->autonStarted();
  shooterAngleController->control(ShooterAngle::upFlag);

  intakeController->control(IntakeDirection::up);
  drive(4_ft);
  pros::delay(350);
  intakeController->control(IntakeDirection::stop);
  drive(-3.6_ft);
  turn(90.0_deg, 1.0);
  //drive(10.0_cm);
  aimForFlag(Flag::red);
  turn(3.0_deg, 1.0);

  shooterController->shootTwice();
  intakeController->control(IntakeDirection::up);
  drive(4.0_ft);

  driveLeft->moveVoltage(90.0);
  driveRight->moveVoltage(90.0);
  pros::delay(600);
  driveLeft->moveVoltage(0.0);
  driveRight->moveVoltage(0.0);

  drive(-4.3_ft);
  intakeController->control(IntakeDirection::down);
  pros::delay(250);
  intakeController->control(IntakeDirection::stop);
  turn(-48.0_deg, 1.0);

  intakeController->control(IntakeDirection::down);
  pros::Task(shootTwice, NULL);
  drive(3.6_ft);

  turn(48.0_deg, 1.0);
  intakeController->control(IntakeDirection::stop);
  drive(-5.85_ft);

  /*int selectedAutonomous = gameState->getAutonomous();

  if(selectedAutonomous == -1) {
    return;
  }

  gameState->autonStarted();
  (*autonomousVariants[selectedAutonomous])();*/
}
