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

void redFar() {
  
}

using void_f = void (*)();

void_f autonomousVariants[] = {&skillsRun, &redClose};

void autonomous()
{
  info("Autonomous start", "autonomous");
  gameState->autonStarted();

  (autonomousVariants[1])();
}
