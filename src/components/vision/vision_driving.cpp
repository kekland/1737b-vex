#include "main.h"
#include "vision_utils.h"

const int filterCount = 5;
void aimForFlag(Flag currentFlag) {
  info("Starting to aim for flag", "aimForFlag");
  okapi::AverageFilter<filterCount> filter;
  
  flagAimingController.reset();
  flagAimingController.setTarget(0.0);
  while(!flagAimingController.isSettled()) {
    auto flag = getFlagForShooting(currentFlag);
    
    if (flag == NULL)
    {
      warn("Flag was NULL.", "aimForFlag");
      continue;
    }
    if (flag->signature != (int)currentFlag)
    {
      warn("Flag's signature is incorrect.", "aimForFlag");
      continue;
    }

    double position = (double)flag->x_middle_coord;
    double filteredPosition = filter.filter(position);

    double power = flagAimingController.step(filteredPosition);
    drivetrain.tank(power, -power);

    printf("(%f) %f -> %f\n", position, filteredPosition, 0.0);
    pros::delay(25);
  }

  drivetrain.tank(0.0, 0.0);
  pros::delay(50);
  info("Finished aiming for flag.", "aimForFlag");
}

const double zoomForFlagTarget = 25.0;
void zoomForFlag(Flag currentFlag) {
  info("Starting to zoom for flag", "zoomForFlag");
  okapi::AverageFilter<filterCount> filter;

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
    if (flag->signature != (int)currentFlag)
    {
      warn("Flag's signature is incorrect.", "zoomForFlag");
      continue;
    }

    double width = (double)flag->width;
    double filteredWidth = filter.filter(width);
    double power = flagZoomingController.step(filteredWidth);

    drivetrain.forward(power);

    printf("(%f) %f -> %f\n", width, filteredWidth, zoomForFlagTarget);
    pros::delay(25);
  }
  
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