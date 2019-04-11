#include "main.h"

using namespace okapi;
void stop()
{
  // Stop the drivetrain
  driveLeft->controllerSet(0.0);
  driveRight->controllerSet(0.0);
}

double circumference = 3.1415 * 10.16;
void drive(QLength targetDistance)
{
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

  int timeStart = pros::millis();
  
  int timeWhenOk = -1;
  while (!leftDriveController->isSettled() && !rightDriveController->isSettled())
  {
    // Get current gyro value
    if (pros::millis() - timeStart > 3000)
    {
      pros::lcd::print(3, "stopped");
      break;
    }
    // Get current positions
    double leftReading = driveLeft->getPosition();
    double rightReading = driveRight->getPosition();

    double diffReading = leftReading - rightReading;

    // Get the powers
    double leftPower = leftDriveController->step(leftReading);
    double rightPower = rightDriveController->step(rightReading);
    double straightPower = straightDriveController->step(diffReading);

    // Apply powers
    driveLeft->controllerSet(leftPower + straightPower);
    driveRight->controllerSet(rightPower - straightPower);

    double leftCentimeters = (leftReading / 360.0) * circumference;
    double rightCentimeters = (rightReading / 360.0) * circumference;

    double leftError = degrees - leftReading;
    double rightError = degrees - rightReading;

    bool ok = abs(leftError) < 10.0 && abs(rightError) < 10.0;

    if(ok && timeWhenOk == -1) {
      timeWhenOk = pros::millis();
    }
    else if(!ok) {
      timeWhenOk = -1;
    }
    else if(ok && pros::millis() - timeWhenOk > 100) {
      break;
    }

    // Log data
    printf("%fcm -> %fcm | %fcm -> %fcm\n", leftCentimeters, cm, rightCentimeters, cm);
    pros::delay(1);
  }
  // Stop the drives
  stop();
  info("Finished driving.", "drive");
}

void turn(QAngle targetDegrees, double turnMultiplier)
{
  // Reset everything
  //gyro.reset();
  double startValue = gyro.get() / 10.0;
  turnController->reset();

  double degs = targetDegrees.convert(degree) * turnMultiplier;
  turnController->setTarget(degs);

  info("Starting to turn.", "turn");
  printf("Target: %fdeg\n", degs);

  int timeStart = pros::millis();
  pros::lcd::print(3, "running");

  int timeWhenOk = -1;
  while (true)
  {
    // Get current gyro value
    double currentValue = (gyro.get() / 10.0) - startValue;

    double error = degs - currentValue;

    bool ok = abs(error) < 4.0;
    if(ok && timeWhenOk == -1) {
      timeWhenOk = pros::millis();
    }
    else if(!ok) {
      timeWhenOk = -1;
    }
    else if(ok && pros::millis() - timeWhenOk > 100) {
      break;
    }

    // Get the power for motors
    double power = turnController->step(currentValue);

    // Set the power
    driveLeft->controllerSet(power);
    driveRight->controllerSet(-power);

    // Log data
    printf("%fdeg -> %fdeg\n", currentValue, targetDegrees);

    pros::delay(1); // Run the control loop at 10ms intervals
  }

  // Stop the drives
  stop();
  info("Finished turning.", "turn");
}