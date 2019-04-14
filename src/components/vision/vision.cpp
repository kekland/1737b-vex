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

const QLength perfectDistanceFromFlag = 120.0_cm;
void aimAndZoomAutomated(Flag currentFlag)
{
  info("Starting to shoot.", "aimAndZoomAutomated");

  FlagObject object = pollForFlag(currentFlag);
  if (object.flagPointer == NULL)
  {
    warn("No flags found.", "aimAndZoomAutomated");
    return;
  }

  QLength distance = calculateDistanceToFlag(object.flagPointer, object.isTopFlag);
  QLength verticalDistance = calculateVerticalDistanceToFlag(object.flagPointer);
  QLength horizontalError = calculateHorizontalErrorFromFlag(object.flagPointer);

  QLength flatDistance = calculateFlatDistanceToFlag(verticalDistance, distance);

  QAngle angle = calculateHorizontalAngle(horizontalError, flatDistance);

  printf("[aimAndZoomAutomated] error: (%fm, %fm), distance: %fm, flat: %fm, angle: %fdeg",
         horizontalError.convert(meter), verticalDistance.convert(meter),
         distance.convert(meter), flatDistance.convert(meter), angle.convert(degree));

  info("Starting to turn", "aimAndZoomAutomated");
  turn(angle, 1.0);

  info("Starting to drive", "aimAndZoomAutomated");
  drive(flatDistance - perfectDistanceFromFlag);
}

void shootTwiceAutomated(Flag currentFlag)
{
  bool shootTopFlag = shouldShootTopFlag(currentFlag);
  bool shootMiddleFlag = shouldShootMiddleFlag(currentFlag);

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
  }
}

void aimAndZoomAutomatedTask(void *param)
{
  opcontrolState->drivetrainEnabled = false;

  shootTwiceAutomated(gameState->getOpposingFlag());

  opcontrolState->gracefulEndTask();
}

void shootTwiceAutomatedTask(void *param)
{
  opcontrolState->shooterAngleEnabled = false;
  opcontrolState->shooterEnabled = false;

  shootTwiceAutomated(gameState->getOpposingFlag());

  opcontrolState->gracefulEndTask();
}