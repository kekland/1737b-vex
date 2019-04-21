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
void redClose()
{
  shooterAngleController->control(ShooterAngle::upFlag);
  pros::Task(getBallUntilBallIsInIntake, NULL);
  driveWithRight(-0.6_ft);
  drive(0.95_ft);
  stickController->control(StickState::ball);
  intakeController->control(IntakeDirection::up);
  drive(-1.15_ft);
  turn(-120.0_deg);
  drive(0.65_ft);
  shooterController->shootTwice();
  stickController->control(StickState::skillsUp);
  intakeController->control(IntakeDirection::down);
  turn(45.0_deg, 1.0);
  intakeController->control(IntakeDirection::stop);
  drive(1.15_ft);
  stickController->control(StickState::cap);

  intakeController->control(IntakeDirection::up);
  drive(-0.5_ft);
  stickController->control(StickState::skillsUp);
  drive(-1.2_ft);
  turn(47.0_deg, 1.0);
  stickController->control(StickState::floor);
  drive(3.5_ft);
  turn(-40.0_deg, 1.0);
  driveLeft->moveVelocity(-100);
  driveRight->moveVelocity(-100);
  pros::delay(150);
  driveLeft->moveVelocity(0);
  driveRight->moveVelocity(0);
  pros::Task(releaseBallUntilBallIsInIntake, NULL);
  shooterController->shootTwice();
}

void redFar()
{
  shooterAngleController->control(ShooterAngle::upFlag);
  int turnMultiplier = -1.0;
  stickController->control(StickState::halfUp);
  pros::Task(getBallUntilBallIsInIntake, NULL);
  //stickController->control(StickState::skillsUp);
  //pros::delay(800);
  drive(3.6_ft);
  driveLeft->moveVelocity(-160);
  driveRight->moveVelocity(-50);
  pros::delay(1000);
  driveLeft->moveVelocity(0);
  driveRight->moveVelocity(0);
  pros::delay(200);
  driveLeft->moveVoltage(6000);
  driveRight->moveVoltage(6000);
  pros::delay(800);
  driveLeft->moveVoltage(-3000);
  driveRight->moveVoltage(-3000);
  pros::delay(200);
  driveLeft->moveVelocity(0);
  driveRight->moveVelocity(0);
  
  driveWithRight(-2.87_in);
  shooterAngleController->motorController->setTarget(13.0);
  shooterController->shootOnce();
  intakeController->control(IntakeDirection::up);
  shooterAngleController->motorController->setTarget(51.5);
  pros::delay(500);
  shooterController->shootOnce();
  driveLeft->moveVelocity(-6000);
  driveRight->moveVelocity(-6000);
  pros::delay(400);
  driveLeft->moveVelocity(0);
  driveRight->moveVelocity(-6000);
  pros::delay(500);

  drive(0.75_ft);
  stickController->control(StickState::cap);

  intakeController->control(IntakeDirection::up);
  drive(-0.5_ft);
  stickController->control(StickState::skillsUp);
  drive(-1.2_ft);
  stickController->control(StickState::floor);
  drive(2.75_ft);
  turn(-90_deg);
  stickController->control(StickState::skillsUp);
  drive(2.0_ft);


}

void redFar2() {
  turn(-45_deg);
  drive(0.7_ft);
  pros::Task(getBallUntilBallIsInIntake, NULL);
  stickController->control(StickState::ball);
  turn(-22_deg);
  shooterAngleController->motorController->setTarget(13.0);
  shooterController->shootOnce();
  intakeController->control(IntakeDirection::up);
  shooterAngleController->motorController->setTarget(51.5);
  pros::delay(500);
  shooterController->shootOnce();
  stickController->control(StickState::flag);

  turn(135_deg);
  pros::delay(200);
  driveLeft->moveVelocity(120);
  driveRight->moveVelocity(120);
  pros::delay(1100);
  driveLeft->moveVelocity(0);
  driveRight->moveVelocity(120);
  pros::delay(535);
  driveLeft->moveVelocity(100);
  driveRight->moveVelocity(100);
  pros::delay(140);
  driveLeft->moveVelocity(0);
  driveRight->moveVelocity(0);

  stickController->control(StickState::zhangir);
  intakeController->control(IntakeDirection::up);
  drive(-0.5_ft);
  stickController->control(StickState::skillsUp);
  turn(-90_deg);
  driveLeft->moveVelocity(200);
  driveRight->moveVelocity(130);
  pros::delay(600);
  driveLeft->moveVelocity(65);
  driveRight->moveVelocity(100);
  pros::delay(1000);
  driveLeft->moveVelocity(0);
  driveRight->moveVelocity(0);
  pros::delay(200);
  intakeController->control(IntakeDirection::down);
  driveWithRight(-11_in);
  shootTwice(NULL);
  //turn(50_deg);

}
void redFar3() {
  shooterAngleController->control(ShooterAngle::upFlag);
  int turnMultiplier = -1.0;
  pros::Task(getBallUntilBallIsInIntake, NULL);
  stickController->control(StickState::halfUp);
  //pros::delay(800);
  drive(3.6_ft);

  drive(-0.28_ft);
  pros::delay(100);

  turn(90.0_deg, turnMultiplier);

  driveLeft->moveVoltage(2500);
  driveRight->moveVoltage(2500);
  pros::delay(1500);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);

  pros::delay(100);
  driveWithRight(-5.7_in);
  // pros::delay(100);
  pros::delay(5000);
  shooterAngleController->motorController->setTarget(18.0);
  shooterController->shootOnce();
  intakeController->control(IntakeDirection::up);
  shooterAngleController->motorController->setTarget(48.5);
  pros::delay(900);
  //  driveIndependent(0_in, -1_in);
  shooterController->shootOnce();
  driveLeft->moveVoltage(1000);
  driveRight->moveVoltage(4000);
  pros::delay(1500);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);
  drive(-0.5_ft);
  turn(90_deg);
  drive(-1.0_ft);
  turn(-90_deg);
  drive(2.9_ft);

}


using void_f = void (*)();

void_f autonomousVariants[] = {&skillsRun, &redClose, &redFar, &redFar2, &redFar3};

void autonomous()
{
  info("Autonomous start", "autonomous");
  gameState->autonStarted();

  (autonomousVariants[4])();
}
