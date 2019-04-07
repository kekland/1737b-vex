#include "main.h"
#include "vision_utils.h"


void shootTwiceAutomated(int currentFlag)
{
  printf("shootin\n");

  auto highFlag = getTopFlag();
  auto middleFlag = getMiddleFlag();

  bool shouldShootHighFlag = checkFlag(highFlag, currentFlag);
  bool shouldShootMiddleFlag = checkFlag(middleFlag, currentFlag);
  bool shouldShootAny = shouldShootHighFlag || shouldShootMiddleFlag;

  if (!shouldShootAny)
  {
    return;
  }

  if (shouldShootHighFlag || shouldShootMiddleFlag)
  {
    printf("flags\n%d\n%d\n", highFlag->signature, middleFlag->signature);

    initialSign = 778;

    while (true)
    {
      auto flag = (driveHigh) ? get_top_flag() : get_middle_flag();
      if (flag == NULL)
      {
        continue;
      }
      if (flag->signature != RED_FLAG && flag->signature != BLUE_FLAG)
      {
        continue;
      }

      double dx = 25.0 - ((double)flag->width);
      printf("%f, (%d %d)\n", dx, flag->width, flag->height);

      if (abs(dx) <= 1.0)
      {
        drivetrain.tank(-initialSign * 0.0, -initialSign * 0.0);
        pros::delay(30);
        break;
      }

      int sign = (dx > 0) ? 1 : -1;
      if (initialSign == 778)
      {
        initialSign = sign;
      }
      drivetrain.tank(sign * 0.2, sign * 0.2);
      pros::delay(25);
    }

    highFlag = get_top_flag();
    middleFlag = get_middle_flag();
    driveHigh = false;
    driveMiddle = false;
    if (highFlag != NULL)
    {
      if (highFlag->signature == current_flag)
      {
        driveHigh = true;
      }
    }
    if (middleFlag != NULL)
    {
      if (middleFlag->signature == current_flag)
      {
        driveMiddle = true;
      }
    }

    printf("%d %d\n", driveHigh, driveMiddle);

    if (driveHigh && driveMiddle)
    {
      shooterController->shootTwice();
    }
    else if (driveHigh)
    {
      shooterAngleController->control(ShooterAngle::upFlag);
      pros::delay(200);
      shooterController->shootOnce();
    }
    else if (driveMiddle)
    {
      shooterAngleController->control(ShooterAngle::downFlag);
      pros::delay(200);
      shooterController->shootOnce();
    }
    pros::delay(100);
  }
}