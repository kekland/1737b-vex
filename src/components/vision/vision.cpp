#include "main.h"
#include "vision_utils.h"
#include "vision_driving.h"
#include "../../autonomous/autonomous_controller.h"
#include "./calc/vision_math.h"

using namespace okapi;
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

void shootTwiceAutomated(Flag currentFlag)
{
  info("Starting to shoot.", "shootTwiceAutomated");

  FlagObject object = pollForFlag(currentFlag);
  if (object.flagPointer == NULL)
  {
    warn("No flags found.", "shootTwiceAutomated");
    return;
  }

  QLength distance = calculateDistanceToFlag(object.flagPointer, object.isTopFlag);
  QLength verticalDistance = calculateVerticalDistanceToFlag(object.flagPointer);
  QLength horizontalError = calculateHorizontalErrorFromFlag(object.flagPointer);

  QLength flatDistance = calculateFlatDistanceToFlag(verticalDistance, distance);

  QAngle angle = calculateHorizontalAngle(horizontalError, flatDistance);

  printf("[shootTwiceAutomated] error: (%fm, %fm), distance: %fm, flat: %fm, angle: %fdeg",
         horizontalError.convert(meter), verticalDistance.convert(meter),
         distance.convert(meter), flatDistance.convert(meter), angle.convert(degree));

  info("Starting to turn", "shootTwiceAutomated");
  turn(angle, 1.0);

  /*bool shootTopFlag = shouldShootTopFlag(currentFlag);
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
  zoomForFlag(currentFlag);
  aimForFlag(currentFlag);
  info("Finished aiming and zooming", "shootTwiceAutomated");

  shootTopFlag = shouldShootTopFlag(currentFlag);
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

void shootTwiceAutomatedTask(void *param)
{
  opcontrolState->drivetrainEnabled = false;
  opcontrolState->shooterAngleEnabled = false;
  opcontrolState->shooterEnabled = false;

  shootTwiceAutomated(gameState->getOpposingFlag());

  masterController->rumble(". ");
  opcontrolState->gracefulEndTask();
}