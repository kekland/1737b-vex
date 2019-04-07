#include "main.h"

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

void move(double leftVelocity, double rightVelocity) {
  if(leftVelocity > 0.6) {
    leftVelocity = 0.6;
  }
  else if(leftVelocity < -0.6) {
    leftVelocity = -0.6;
  }

  if(rightVelocity > 0.6) {
    rightVelocity = 0.6;
  }
  else if(rightVelocity < -0.6) {
    rightVelocity = -0.6;
  }
  driveLeft.moveVelocity(round(leftVelocity * 200.0));
  driveRight.moveVelocity(round(rightVelocity * 200.0));
}

double circumference = 3.1415 * 10.16;
void driveForward(double cm) {
  driveLeft.tarePosition();
  driveRight.tarePosition();

  double degrees = (cm / circumference) * 360.0;
  leftDriveController.reset();
  leftDriveController.setTarget(degrees);
  rightDriveController.reset();
  rightDriveController.setTarget(degrees);
  while(!leftDriveController.isSettled() && !rightDriveController.isSettled()) {
    double leftReading = driveLeft.getPosition();
    double rightReading = driveRight.getPosition();

    double leftPower = leftDriveController.step(leftReading);
    double rightPower = rightDriveController.step(rightReading);
    
    driveLeft.controllerSet(leftPower);
    driveRight.controllerSet(rightPower);

    pros::delay(10);
  }
  pros::delay(150);
}

void turn(double degrees) {
  gyro.reset();

  turnController.reset();
  turnController.setTarget(degrees);
  while(!turnController.isSettled()) {
    double val = gyro.get() / 10.0;
    printf("%f <- %f\n", degrees, val);
    double reading = turnController.step(val);
    driveLeft.controllerSet(reading);
    driveRight.controllerSet(-reading);
    pros::delay(10); // Run the control loop at 10ms intervals
  }
  pros::delay(150);
}

void autonomous() {
  intakeController->control(IntakeDirection::up);
  driveForward(130.0);
  pros::delay(200);
  intakeController->control(IntakeDirection::stop);
  driveForward(-115.0);
  turn(-90.0);
  shootTwiceAutomated(BLUE_FLAG);
  turn(45.0);
  intakeController->control(IntakeDirection::down);
  driveForward(115.0);
  turn(-45.0);
  driveForward(-160.0);
}
