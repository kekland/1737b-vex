#include "main.h"
#include "vision_utils.h"

void aimForFlag(Flag currentFlag)
{
  info("Starting to aim for flag", "aimForFlag");

  flagAimingController->reset();
  flagAimingController->setTarget(0.0);

  int iters = 0;
  int startTime = pros::millis();
  while (true)
  {
    if(pros::millis() - startTime > 1000) {
      break;
    }
    pros::delay(25);
    auto flag = getFlagForShooting(currentFlag);

    if (flag.flagPointer == NULL)
    {
      warn("Flag was NULL.", "aimForFlag");
      drivetrain->tank(0.0, 0.0);
      continue;
    }

    double position = (double)flag.flagPointer->x_middle_coord;

    double power = flagAimingController->step(position);

    double error = flagAimingController->getError();
    if (flagAimingController->isSettled())
    {
      break;
    }

    drivetrain->tank(-power, power);
    iters++;

    printf("(%f) %f -> %f with power %f\n", position, position, 0.0, power);
  }

  drivetrain->tank(0.0, 0.0);
  pros::delay(50);
  info("Finished aiming for flag.", "aimForFlag");
}

const double zoomForFlagTargetClose = 26.0;
const double zoomForFlagTargetFar = 8.0;
void zoomForFlag(Flag currentFlag)
{
  info("Starting to zoom for flag", "zoomForFlag");
  okapi::AverageFilter<3> filter;

  flagZoomingController->reset();
  flagZoomingController->setTarget(zoomForFlagTargetClose);
  int iters = 0;
  while (true)
  {
    pros::delay(25);
    // Get the flag
    auto flag = getFlagForShooting(currentFlag);

    if (flag.flagPointer == NULL)
    {
      warn("Flag was NULL.", "zoomForFlag");
      continue;
    }

    double width = (double)flag.flagPointer->width;
    double height = (double)flag.flagPointer->height;

    double filteredWidth = width;
    double error = flagZoomingController->getError();

    if (abs(error) <= 2 && iters > 4)
    {
      break;
    }

    if (iters < 3)
      filteredWidth = width;
    double power = flagZoomingController->step(filteredWidth);

    drivetrain->tank(power, power);
    iters++;

    printf("(%f) %f -> %f with power %f\n", width, filteredWidth, zoomForFlagTargetClose, power);
  }

  drivetrain->tank(0.0, 0.0);
  pros::delay(50);
  info("Finished zooming for flag", "zoomForFlag");
}

// DEPRECATED: NOW ADDING FILTERS
/*
const int DEFAULT_VALUE = 778;
void aimForFlag(Flag currentFlag)
{
  int flagIndex = (int)currentFlag;
  info("Starting to aim for flag", "aimForFlag");

  double prevPosition = DEFAULT_VALUE;
  int timeWhenDxOk = -1;

  flagAimingController.reset();
  flagAimingController.setTarget(0.0);
  while (!flagAimingController.isSettled())
  {
    // Get the flag
    auto flag = getFlagForShooting(currentFlag);

    // Check that this is the correct flag
    if (flag == NULL)
    {
      warn("Flag was NULL.", "aimForFlag");
      continue;
    }
    if (flag->signature != flagIndex)
    {
      warn("Flag's signature is incorrect.", "aimForFlag");
      continue;
    }

    // Get the value
    double position = (double)flag->x_middle_coord;

    // If the error is deviating too much from the previous error - skip
    if (prevPosition == DEFAULT_VALUE)
    {
      prevPosition = position;
    }
    if (abs(position - prevPosition) > 50)
    {
      continue;
    }

    // Step with the PID controller
    double power = flagAimingController.step(position);
    prevPosition = position;

    drivetrain.tank(power, -power);
    pros::delay(25);
  }

  info("Finished aiming for flag.", "aimForFlag");
}

const double zoomForFlagTarget = 25.0;
void zoomForFlag(Flag currentFlag)
{
  int flagIndex = (int)currentFlag;
  info("Starting to zoom for flag", "zoomForFlag");

  flagZoomingController.reset();
  flagZoomingController.setTarget(zoomForFlagTarget);
  while (!flagZoomingController.isSettled())
  {
    // Get the flag
    auto flag = getFlagForShooting(currentFlag);

    if (flag == NULL)
    {
      warn("Flag was NULL.", "zoomForFlag");
      continue;
    }
    if (flag->signature != flagIndex)
    {
      warn("Flag's signature is incorrect.", "zoomForFlag");
      continue;
    }

    double width = (double)flag->width;
    double power = flagZoomingController.step(width);

    drivetrain.forward(power);

    pros::delay(25);
  }
  
  info("Finished zooming for flag", "zoomForFlag");
}
*/