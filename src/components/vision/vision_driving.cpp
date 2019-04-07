#include "main.h"
#include "vision_utils.h"

const int DEFAULT_VALUE = 778;
const int turnForFlagThreshold = 5;
const int turnForFlagRestTime = 100;
void turnForFlag(int currentFlag)
{
  double prevDx = DEFAULT_VALUE;
  int timeWhenDxOk = -1;
  while (true)
  {
    auto flag = getFlagForShooting(currentFlag);

    if (flag == NULL)
    {
      continue;
    }
    if (flag->signature != currentFlag)
    {
      continue;
    }

    double dx = (double)flag->x_middle_coord;
    dx += 4.0 * (currentFlag == RED_FLAG) ? 1 : -1;

    if (prevDx == DEFAULT_VALUE)
    {
      prevDx = dx;
    }
    if (abs(dx - prevDx) > 50)
    {
      continue;
    }

    prevDx = dx;
    bool ok = abs(dx) <= turnForFlagThreshold;
    if (ok && timeWhenDxOk == -1)
    {
      timeWhenDxOk = pros::millis();
    }
    else if (ok && pros::millis() - timeWhenDxOk > turnForFlagRestTime)
    {
      drivetrain.tank(0.0, 0.0);
      break;
    }
    else if (!ok)
    {
      timeWhenDxOk = -1;
    }
    
    // TODO
    //drivetrain.tank(sign * vel, -sign * vel);
    pros::delay(25);
  }
}