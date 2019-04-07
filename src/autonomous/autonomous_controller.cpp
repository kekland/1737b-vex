#include "main.h"

void stop() {
  // Stop the drivetrain
  driveLeft.controllerSet(0.0);
  driveRight.controllerSet(0.0);
}

double circumference = 3.1415 * 10.16;
void drive(double cm) {
  // Reset everything
  driveLeft.tarePosition();
  driveRight.tarePosition();
  leftDriveController.reset();
  rightDriveController.reset();

  // Calculate required amount of degrees to travel
  double degrees = (cm / circumference) * 360.0;

  // Set targets
  leftDriveController.setTarget(degrees);
  rightDriveController.setTarget(degrees);

  info("Starting to drive.", "drive");
  printf("Target: %fcm\n", cm);
  while(!leftDriveController.isSettled() && !rightDriveController.isSettled()) {
    // Get current positions
    double leftReading = driveLeft.getPosition();
    double rightReading = driveRight.getPosition();

    // Get the powers
    double leftPower = leftDriveController.step(leftReading);
    double rightPower = rightDriveController.step(rightReading);
    
    // Apply powers
    driveLeft.controllerSet(leftPower);
    driveRight.controllerSet(rightPower);

    // Log data
    printf("%fd -> %fd | %fd -> %fd\n", leftReading, degrees, rightReading, degrees);
    pros::delay(10);
  }
  // Stop the drives
  stop();
  info("Finished driving.", "drive");

  pros::delay(150);
}

void turn(double targetDegrees) {
  // Reset everything
  gyro.reset();
  turnController.reset();

  turnController.setTarget(targetDegrees);

  info("Starting to turn.", "turn");
  printf("Target: %fdeg\n", targetDegrees);
  while(!turnController.isSettled()) {
    // Get current gyro value
    double currentValue = gyro.get() / 10.0;

    // Get the power for motors
    double power = turnController.step(currentValue);

    // Set the power
    driveLeft.controllerSet(power);
    driveRight.controllerSet(-power);

    // Log data
    printf("%fdeg -> %fdeg\n", currentValue, targetDegrees);

    pros::delay(10); // Run the control loop at 10ms intervals
  }

  // Stop the drives
  stop();
  info("Finished turning.", "turn");
  pros::delay(150);
}