#include "main.h"
#include "../autonomous_controller.h"

void skillsRun()
{
  shooterAngleController->control(ShooterAngle::upFlag);
  int turnMultiplier = -1.0;
  pros::Task(getBallUntilBallIsInIntake, NULL);
  stickController->control(StickState::skills);
  //pros::delay(800);
  drive(3.6_ft);
  stickController->control(StickState::skillsUp);

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

  shooterAngleController->motorController->setTarget(18.0);
  shooterController->shootOnce();
  intakeController->control(IntakeDirection::up);
  shooterAngleController->motorController->setTarget(48.5);
  pros::delay(900);
  //  driveIndependent(0_in, -1_in);
  shooterController->shootOnce();

  pros::delay(200);
  turn(-10.0_deg, turnMultiplier);
  drive(-3.13_ft);
  turn(-54.0_deg, turnMultiplier);

  intakeController->control(IntakeDirection::stop);
  drive(0.8655_ft);
  //turn(5.0_deg, turnMultiplier);
  stickController->control(StickState::cap);
  //pros::delay(500);
  intakeController->control(IntakeDirection::up);
  //drive(0.25_ft);
  drive(-0.5_ft);
  stickController->control(StickState::skillsUp);
  drive(-1_ft);

  stickController->control(StickState::floor);
  drive(1.1_ft);
  stickController->flipCap();
  //drive(-0.1_ft);
  pros::delay(200);
  turn(-90.0_deg);
  driveLeft->moveVoltage(-2000);
  driveRight->moveVoltage(-2000);
  pros::delay(800);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);
  intakeController->releaseBallUntilBallIsInIntake(NULL);


  drive(2.50_ft);
  driveLeft->moveVoltage(2000);
  driveRight->moveVoltage(2000);
  pros::delay(1000);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);
  driveWithRight(-4_in);
  driveLeft->moveVoltage(-2000);
  driveRight->moveVoltage(-2000);
  pros::delay(500);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);  
  shooterAngleController->motorController->setTarget(10.0);
  shooterController->shootOnce();
  intakeController->control(IntakeDirection::up);
  shooterAngleController->motorController->setTarget(53.5);
  pros::delay(500);
  //  driveIndependent(0_in, -1_in);
  shooterController->shootOnce();
  pros::delay(500);
  drive(-0.1_ft);
  turn(85.0_deg);
  intakeController->control(IntakeDirection::down);

  driveLeft->moveVoltage(-7000);
  driveRight->moveVoltage(-7000);
  pros::delay(1200);
  driveLeft->moveVoltage(-2000);
  driveRight->moveVoltage(-2000);
  pros::delay(1200);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);
  drive(0.5_ft);
  pros::delay(500);
  turn(-90.0_deg);
  driveLeft->moveVoltage(-6000);
  driveRight->moveVoltage(-6000);
  pros::delay(900);
  driveLeft->moveVoltage(-2000);
  driveRight->moveVoltage(-2000);
  pros::delay(2000);

  drive(6.4_ft);
  stickController->control(StickState::skillsUp);
  turn(45_deg);
  intakeController->control(IntakeDirection::stop);
  drive(1.48_ft);
  stickController->control(StickState::cap);
  //pros::delay(1000);
  intakeController->control(IntakeDirection::up);
  drive(-0.5_ft);
  stickController->control(StickState::skillsUp);
  drive(-1_ft);

  stickController->control(StickState::floor);
  drive(1.05_ft);
  stickController->flipCap();
  drive(-1.42_ft);
  turn(-43_deg);
  drive(0.1_ft);
  intakeController->releaseBallUntilBallIsInIntake(NULL);
  //aimForFlag(Flag::blue);
  shootTwice(NULL);
  turn(-5_deg);
  stickController->control(StickState::flag);
  intake->controllerSet(-0.4);

  drive(3.0_ft);
  pros::delay(200);
  drive(-3.75_ft);
  turn(90_deg);
  driveLeft->moveVoltage(-2000);
  driveRight->moveVoltage(-2000);
  pros::delay(1800);
  drive(4.5_ft);
  drive(-1.8_ft);

  turn(90_deg);
  drive(2.9_ft);
  pros::delay(500);
  turn(-90_deg);
  driveLeft->moveVoltage(4000);
  driveRight->moveVoltage(4000);
  pros::delay(700);
  drive(-0.5_ft);
  drive(2.9_ft);

  /*
  driveLeft->moveVoltage(-2000);
  driveRight->moveVoltage(-2000);
  pros::delay(3000);
  driveLeft->moveVoltage(12000);
  driveRight->moveVoltage(12000);
  pros::delay(2200);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);

  pros::delay(5000);
  driveLeft->moveVoltage(-12000);
  driveRight->moveVoltage(-12000);
  pros::delay(2400);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0); */
}