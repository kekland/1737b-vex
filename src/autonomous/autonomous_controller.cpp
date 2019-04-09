#include "main.h"

using namespace okapi;
void stop() {
  // Stop the drivetrain
  driveLeft->controllerSet(0.0);
  driveRight->controllerSet(0.0);
}

double circumference = 3.1415 * 10.16;
void drive(QLength targetDistance) {
  // Reset everything
  driveLeft->tarePosition();
  driveRight->tarePosition();
  leftDriveController->reset();
  rightDriveController->reset();


  // Calculate required amount of degrees to travel
  double cm = targetDistance.convert(centimeter);
  double degrees = (cm / circumference) * 360.0;

  // Set targets
  leftDriveController->setTarget(degrees);
  rightDriveController->setTarget(degrees);

  info("Starting to drive.", "drive");
  printf("Target: %fcm\n", cm);
  while(!leftDriveController->isSettled() && !rightDriveController->isSettled()) {
    // Get current positions
    double leftReading = driveLeft->getPosition();
    double rightReading = driveRight->getPosition();

    // Get the powers
    double leftPower = leftDriveController->step(leftReading);
    double rightPower = rightDriveController->step(rightReading);
    
    // Apply powers
    driveLeft->controllerSet(leftPower);
    driveRight->controllerSet(rightPower);

    double leftCentimeters = (leftReading / 360.0) * circumference;
    double rightCentimeters = (rightReading / 360.0) * circumference;

    if(abs(leftDriveController->getError()) < 15.0 && abs(rightDriveController->getError() < 15.0)) {
      break;
    }

    // Log data
    printf("%fcm -> %fcm | %fcm -> %fcm\n", leftCentimeters, cm, rightCentimeters, cm);
    pros::delay(10);
  }
  // Stop the drives
  stop();
  info("Finished driving.", "drive");
}

void turn(QAngle targetDegrees, double turnMultiplier) {
  // Reset everything
  gyro.reset();
  turnController->reset();

  double degs = targetDegrees.convert(degree) * turnMultiplier;
  turnController->setTarget(degs);

  info("Starting to turn.", "turn");
  printf("Target: %fdeg\n", degs);

  while(!turnController->isSettled()) {
    // Get current gyro value
    double currentValue = gyro.get() / 10.0;

    // Get the power for motors
    double power = turnController->step(currentValue);

    // Set the power
    driveLeft->controllerSet(power);
    driveRight->controllerSet(-power);

    // Log data
    printf("%fdeg -> %fdeg\n", currentValue, targetDegrees);

    pros::delay(10); // Run the control loop at 10ms intervals
  }

  // Stop the drives
  stop();
  info("Finished turning.", "turn");
}