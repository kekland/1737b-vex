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
  shooterAngleController->control(ShooterAngle::downFlag);
  intakeController->control(IntakeDirection::up);
  pros::delay(550);
  shooterController->shootOnce();
  intakeController->control(IntakeDirection::up);
}

void getBallUntilBallIsInIntake(void* param) {
  intakeController->getBallUntilBallIsInIntake(NULL);
}

void matchRun1(Alliance alliance) {
  double turnMultiplier = (alliance == Alliance::red)? -1.0 : 1.0;
  Flag flagToShoot = (alliance == Alliance::red)? Flag::blue : Flag::red;

  shooterAngleController->control(ShooterAngle::upFlag);

  pros::Task(getBallUntilBallIsInIntake, NULL);
  drive(3.85_ft);
  driveLeft->moveVoltage(-2500);
  driveRight->moveVoltage(-2500);
  
  //intakeController->control(IntakeDirection::stop);
  drive(-3.4_ft);
  turn(90.0_deg, turnMultiplier);
  aimAndZoomAutomated(flagToShoot);
  drive(0.2_ft);
  shooterController->shootTwice();
  intakeController->control(IntakeDirection::up);
  
  driveLeft->moveVoltage((alliance == Alliance::red)? 10000 : 12000);
  driveRight->moveVoltage((alliance == Alliance::red)? 12000 : 10000);
  pros::delay(750);
  driveLeft->moveVoltage((alliance == Alliance::red)? 8000 : 7000);
  driveRight->moveVoltage((alliance == Alliance::red)? 7000 : 8000);
  pros::delay(600);
  driveLeft->moveVoltage(6000);
  driveRight->moveVoltage(6000);
  pros::delay(500);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);

  drive(-4.35_ft);
  intake->moveVelocity(-115);
  //intakeController->control(IntakeDirection::down);
  turn(-48.0_deg, turnMultiplier);
  //aimAndZoomAutomated(flagToShoot);
  pros::Task(shootOnce, NULL);
  drive(3.55_ft);
  turn(48.5_deg, turnMultiplier);
  drive(-5.815_ft);
}

void matchRun3(Alliance alliance) {
  double turnMultiplier = (alliance == Alliance::red)? -1.0 : 1.0;
  Flag flagToShoot = (alliance == Alliance::red)? Flag::blue : Flag::red;
  
  shooterAngleController->control(ShooterAngle::upFlag);

  intakeController->control(IntakeDirection::up);
  drive(3.85_ft);
  driveLeft->moveVoltage(-2500);
  driveRight->moveVoltage(-2500);
  pros::delay(275);
  //intakeController->control(IntakeDirection::stop);
  drive(-3.4_ft);
  intakeController->control(IntakeDirection::down);
  pros::delay(250);
  intakeController->control(IntakeDirection::stop);
  turn(90.0_deg, turnMultiplier);
  aimAndZoomAutomated(flagToShoot);
  drive(-0.3_ft);
  shooterController->shootTwice();
  intakeController->control(IntakeDirection::up);

  driveLeft->moveVoltage((alliance == Alliance::red)? 10000 : 12000);
  driveRight->moveVoltage((alliance == Alliance::red)? 12000 : 10000);
  pros::delay(750);
  driveLeft->moveVoltage((alliance == Alliance::red)? 8000 : 7500);
  driveRight->moveVoltage((alliance == Alliance::red)? 7500 : 8000);
  pros::delay(600);
  driveLeft->moveVoltage(5200);
  driveRight->moveVoltage(5200);
  pros::delay(500);
  drive(-3.8_ft);
  pros::delay(500);
  intakeController->control(IntakeDirection::down);
  turn(-53.0_deg, turnMultiplier);
  //intakeController->control(IntakeDirection::down);
  pros::Task(shootOnce, NULL);
  drive(3.95_ft);
  turn(50.5_deg, turnMultiplier);
  drive(-5.915_ft);
}
void matchRun2(Alliance alliance) {
  double turnMultiplier = (alliance == Alliance::red)? -1.0 : 1.0;
  Flag flagToShoot = (alliance == Alliance::red)? Flag::blue : Flag::red;
  
  shooterAngleController->control(ShooterAngle::upFlag);

  intakeController->control(IntakeDirection::up);
  drive(3.85_ft);
  driveLeft->moveVoltage(-2500);
  driveRight->moveVoltage(-2500);
  pros::delay(275);
  //intakeController->control(IntakeDirection::stop);
  drive(-3.4_ft);
  intakeController->control(IntakeDirection::down);
  pros::delay(250);
  intakeController->control(IntakeDirection::stop);
  turn(90.0_deg, turnMultiplier);
  aimAndZoomAutomated(flagToShoot);
  drive(-0.3_ft);
  shooterController->shootTwice();
  intakeController->control(IntakeDirection::up);

  driveLeft->moveVoltage((alliance == Alliance::red)? 9800 : 12000);
  driveRight->moveVoltage((alliance == Alliance::red)? 12000 : 9800);
  pros::delay(750);
  driveLeft->moveVoltage((alliance == Alliance::red)? 8000 : 7500);
  driveRight->moveVoltage((alliance == Alliance::red)? 7500 : 8000);
  pros::delay(600);
  driveLeft->moveVoltage(5200);
  driveRight->moveVoltage(5200);
  pros::delay(500);
  drive(-3.8_ft);
  pros::delay(500);
  intakeController->control(IntakeDirection::down);
  turn(-49.0_deg, turnMultiplier);
  drive(1.25_ft);
  turn(-4.0_deg);
  intakeController->control(IntakeDirection::down);
  shooterAngleController->control(ShooterAngle::downFlag);
  shooterController->shootOnce();
  intakeController->control(IntakeDirection::up);
  driveLeft->moveVelocity(160.0);
  driveRight->moveVelocity(160.0);
  pros::delay(350);
  driveLeft->moveVelocity(0.0);
  driveRight->moveVelocity(0.0);
  drive(-0.65_ft);
  pros::delay(1000);
  aimAndZoomAutomated(flagToShoot);
  shooterAngleController->control(ShooterAngle::upFlag);
  shooterController->shootOnce();

  //shooterController->shootTwice();
  //intake->moveVelocity(-100);
  //drive(4_ft);

  /*pros::Task(shootOnce, NULL);
  drive(3.95_ft);
  turn(50.5_deg, turnMultiplier);
  drive(-5.915_ft);*/
}

void matchRun4(Alliance alliance) {
  double turnMultiplier = (alliance == Alliance::red)? -1.0 : 1.0;
  Flag flagToShoot = (alliance == Alliance::red)? Flag::blue : Flag::red;
  
  shooterAngleController->control(ShooterAngle::upFlag);

  drive(1.8_ft);
  turn(90.0_deg, turnMultiplier);
  //intakeController->control(IntakeDirection::down);
  intake->moveVelocity(-175.0);
  drive(3.75_ft);
  drive(-2.5_ft);
  turn(90.0_deg, turnMultiplier);
  drive(1.8_ft);
  turn(-90.0_deg, turnMultiplier);
  pros::Task(getBallUntilBallIsInIntake, NULL);
  drive(1.75_ft);

  drive(-0.625_ft);
  turn(90.0_deg, turnMultiplier);
  driveLeft->moveVoltage(3000);
  driveRight->moveVoltage(3000);
  pros::delay(900);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);
  pros::delay(500);
  drive(-0.15_ft);
  turn(-10.5_deg, turnMultiplier);
  shootTwice(NULL);
  turn(10.5_deg, turnMultiplier);

  //turn(-170.0_deg, turnMultiplier);
  drive(2.525_ft);
  //drive(-4_ft);
}

void matchRun5(Alliance alliance) {
  double turnMultiplier = (alliance == Alliance::red)? -1.0 : 1.0;
  Flag flagToShoot = (alliance == Alliance::red)? Flag::blue : Flag::red;
  
  shooterAngleController->control(ShooterAngle::upFlag);

  pros::Task(getBallUntilBallIsInIntake, NULL);
  drive(3.5_ft);
  drive(-0.25_ft);
  pros::delay(250);
  turn(90.0_deg, turnMultiplier);
  driveLeft->moveVoltage(4000);
  driveRight->moveVoltage(4000);
  pros::delay(900);
  driveLeft->moveVoltage(0);
  driveRight->moveVoltage(0);
  pros::delay(500);
  drive(-0.125_ft);
  turn(-25.0_deg, turnMultiplier);
  shootTwice(NULL);
  turn(25.0_deg, turnMultiplier);
  pros::delay(200);
  turn(-90.0_deg, turnMultiplier);
  drive(-0.575_ft);
  turn(-90.0_deg, turnMultiplier);
  drive(-3.25_ft);
}


void skillsRun2() {
  Flag flagToShoot = Flag::blue;
  
  shooterAngleController->control(ShooterAngle::upFlag);

  intakeController->control(IntakeDirection::up);
  drive(3.85_ft);
  driveLeft->moveVoltage(-2500);
  driveRight->moveVoltage(-2500);
  pros::delay(275);
  //intakeController->control(IntakeDirection::stop);
  drive(-3.4_ft);
  intakeController->control(IntakeDirection::down);
  pros::delay(250);
  intakeController->control(IntakeDirection::stop);
  driveLeft->moveVoltage(-5200);
  driveRight->moveVoltage(-5200);
  pros::delay(800);
  drive(0.9_ft);
  turn(-90.0_deg, 1.0);
  aimAndZoomAutomated(flagToShoot);
  drive(-0.5_ft);
  shooterController->shootTwice();
  intakeController->control(IntakeDirection::up);

  driveLeft->moveVoltage(10000);
  driveRight->moveVoltage(12000);
  pros::delay(750);
  driveLeft->moveVoltage(8000);
  driveRight->moveVoltage(7200);
  pros::delay(600);
  driveLeft->moveVoltage(5200);
  driveRight->moveVoltage(5200);
  pros::delay(1500);
  drive(-3.8_ft);
  pros::delay(500);
  intakeController->control(IntakeDirection::down);
  turn(45.0_deg, 1.0);
  drive(0.5_ft);
  turn(9.0_deg, 1.0);
  shooterAngleController->control(ShooterAngle::downFlag);
  shooterController->shootOnce();
  turn(-9.0_deg, 1.0);
  //intakeController->control(IntakeDirection::stop);
  intakeController->control(IntakeDirection::up);
  drive(1_ft);
  driveLeft->moveVelocity(-200);
  driveRight->moveVelocity(-200);
  pros::delay(350);
  driveLeft->moveVelocity(0);
  driveRight->moveVelocity(0);
  //drive(-1.2_ft);
  pros::delay(1250);
  turn(9.0_deg, 1.0);
  shooterAngleController->control(ShooterAngle::upFlag);
  shooterController->shootOnce();
  turn(38.0_deg, 1.0);
  driveLeft->moveVoltage(-5200);
  driveRight->moveVoltage(-5200);
  pros::delay(800);
  drive(1_ft);
  turn(90.0_deg, 1.0);
  drive(2_ft);
  turn(-90.0_deg, 1.0);
  drive(12_ft);
}

void skillsRun() {
  matchRun1(Alliance::red);
  turn(-90_deg);
  drive(-2.9_ft);
}

void autonomous()
{
  info("Autonomous start", "autonomous");
  gameState->autonStarted();
  //matchRun2(Alliance::blue);
  matchRun5(Alliance::blue);
}
