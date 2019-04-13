#include "main.h"
#include "vision_utils.h"
#include "vision_driving.h"

bool shouldShootTopFlag(Flag currentFlag)
{
  auto topFlag = getTopFlag();
  return checkFlag(topFlag, currentFlag);
}

bool shouldShootMiddleFlag(Flag currentFlag)
{
  auto middleFlag = getMiddleFlag();
  return checkFlag(middleFlag, currentFlag);
}

//Actual distance: 1m
//Actual mid area: 1100
//Actual high area: 
// Now mid area: 726

void measureAreaOfObjects()
{
  info("Measuring area.", "measureAreaOfObjects");
  double area = 0.0;
  int iters = 0;
  while (true)
  {
    pros::delay(25);
    auto topFlag = getTopFlag();
    auto flag = getMiddleFlag();
    if (flag == NULL || topFlag == NULL)
    {
      info("Flag is NULL", "maoo");
      continue;
    }

    double area = topFlag->width * topFlag->height;

    printf("top %d\t(%d %d) %d\n", topFlag->signature, topFlag->width, topFlag->height, topFlag->width * topFlag->height);
    printf("mid %d\t(%d %d) %d\n", flag->signature, flag->width, flag->height, flag->width * flag->height);
  }
}

void shootTwiceAutomated(Flag currentFlag)
{
  info("Starting to shoot.", "shootTwiceAutomated");

  bool shootTopFlag = shouldShootTopFlag(currentFlag);
  bool shootMiddleFlag = shouldShootMiddleFlag(currentFlag);
  bool shootAny = shootTopFlag || shootMiddleFlag;

  if (!shootAny)
  {
    warn("No flags found.", "shootTwiceAutomated");
    return;
  }

  if (shootTopFlag)
  {
    shooterAngleController->control(ShooterAngle::upFlag);
    info("Detected top flag.", "shootTwiceAutomated");
  }
  if (shootMiddleFlag)
  {
    shooterAngleController->control(ShooterAngle::downFlag);
    info("Detected middle flag.", "shootTwiceAutomated");
  }

  aimForFlag(currentFlag);

  pros::vision_object_s_t *flagToShoot = NULL;
  while (flagToShoot == NULL)
  {
    flagToShoot = getFlagForShooting(currentFlag);
  }

  if (flagToShoot->width > 18)
  {
    zoomForFlag(currentFlag);
    aimForFlag(currentFlag);
    info("Finished aiming and zooming", "shootTwiceAutomated");

    /*shootTopFlag = shouldShootTopFlag(currentFlag);
    shootMiddleFlag = shouldShootMiddleFlag(currentFlag);

    if (shootTopFlag && shootMiddleFlag)
    {
      info("Shooting both flags.", "shootTwiceAutomated");
      shooterController->shootTwice();
    }
    else if (shootTopFlag)
    {
      info("Shooting top flag.", "shootTwiceAutomated");
      shooterAngleController->control(ShooterAngle::upFlag);
      shooterAngleController->waitUntilSettled();
      shooterController->shootOnce();
    }
    else if (shootMiddleFlag)
    {
      info("Shooting middle flag.", "shootTwiceAutomated");
      shooterAngleController->control(ShooterAngle::downFlag);
      shooterAngleController->waitUntilSettled();
      shooterController->shootOnce();
    }
    else
    {
      warn("No flags were detected.", "shootTwiceAutomated");
    }*/
  }
}

void shootTwiceAutomatedTask(void *param)
{
  opcontrolState->drivetrainEnabled = false;
  opcontrolState->shooterAngleEnabled = false;
  opcontrolState->shooterEnabled = false;

  shootTwiceAutomated(gameState->getOpposingFlag());

  masterController->rumble(". ");
  opcontrolState->gracefulEndTask();
}