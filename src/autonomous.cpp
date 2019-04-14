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

void shootOnce(void *param)
{
  pros::delay(300);
  shooterController->shootOnce();
}

void shootTwice(void *param)
{
  shooterAngleController->control(ShooterAngle::upFlag);
  shooterController->shootOnce();
  intakeController->control(IntakeDirection::down);
  pros::delay(100);
  intakeController->control(IntakeDirection::up);
  pros::delay(450);
  shooterController->shootOnce();
  intakeController->control(IntakeDirection::up);
}

void matchRun(Alliance alliance) {
  double turnMultiplier = (alliance == Alliance::red)? -1.0 : 1.0;
  Flag flagToShoot = (alliance == Alliance::red)? Flag::blue : Flag::red;

  shooterAngleController->control(ShooterAngle::upFlag);

  intakeController->control(IntakeDirection::up);
  drive(3.85_ft);
  driveLeft->moveVoltage(-2000);
  driveRight->moveVoltage(-2000);
  pros::delay(225);
  intakeController->control(IntakeDirection::stop);
  drive(-3.65_ft);
  intakeController->control(IntakeDirection::down);
  pros::delay(150);
  intakeController->control(IntakeDirection::stop);
  turn(90.0_deg, turnMultiplier);
  aimAndZoomAutomated(flagToShoot);

  shooterController->shootTwice();
  
  intakeController->control(IntakeDirection::up);
  //turn(6.0_deg, turnMultiplier);
  driveLeft->moveVoltage((alliance == Alliance::blue)? 12000 : 10250);
  driveRight->moveVoltage((alliance == Alliance::blue)? 11500 : 12000);
  pros::delay(1000);
  driveLeft->moveVoltage((alliance == Alliance::blue)? 7000 : 9000);
  driveRight->moveVoltage((alliance == Alliance::blue)? 9000 : 7000);
  pros::delay(950);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);

  drive(-4.65_ft);
  intake->moveVelocity(-100);
  //intakeController->control(IntakeDirection::down);
  turn(-42.0_deg, turnMultiplier);
  pros::Task(shootOnce, NULL);
  drive(3.85_ft);
  turn(48.5_deg, turnMultiplier);
  drive(-6.115_ft);
}

void skillsRun() {
  matchRun(Alliance::red);
  turn(-90_deg);
  drive(-2.9_ft);
}

void autonomous()
{
  info("Autonomous start", "autonomous");
  gameState->autonStarted();
  matchRun(Alliance::red);
  //skillsRun();
}
