#include "main.h"
#include "vision_utils.h"
#include "vision_driving.h"

bool shouldShootTopFlag(int currentFlag) {
  auto topFlag = getTopFlag();
  return checkFlag(topFlag, currentFlag);
}

bool shouldShootMiddleFlag(int currentFlag) {
  auto middleFlag = getTopFlag();
  return checkFlag(middleFlag, currentFlag);
}

void shootTwiceAutomated(int currentFlag)
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
    info("Detected top flag.", "shootTwiceAutomated");
  }
  if (shootMiddleFlag)
  {
    info("Detected middle flag.", "shootTwiceAutomated");
  }

  aimForFlag(currentFlag);
  zoomForFlag(currentFlag);
  
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
  else {
    warn("No flags were detected.", "shootTwiceAutomated");
  }
}