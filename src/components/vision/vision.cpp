#include "main.h"
#include "vision_utils.h"

pros::vision_object_s_t *get_top_flag()
{
  std::vector<pros::vision_object_s_t> flags;

  for (int size = 0; size < 3; size++)
  {
    auto flag = visionSensor.get_by_size(size);
    if (flag.width >= 6 && flag.height >= 6 && (flag.signature == BLUE_FLAG || flag.signature == RED_FLAG))
    {
      flags.push_back(flag);
    }
  }

  int total = flags.size();

  if (total < 2)
  {
    return NULL;
  }

  int highestIndex = 0;
  int highestY = -1000;
  int secondHighestIndex = 0;

  for (int i = 0; i < total; i++)
  {
    if (highestY == -1000)
    {
      highestY = flags[i].y_middle_coord;
      highestIndex = i;
      continue;
    }

    auto flag = flags[i];
    double flagArea = flag.width * flag.height;
    double highestIndexArea = flags[highestIndex].width * flags[highestIndex].height;
    if (flag.y_middle_coord > highestY || (abs(flag.y_middle_coord - highestY) < 20 && flagArea >= highestIndexArea))
    {
      highestY = flag.y_middle_coord;
      highestIndex = i;
    }
  }

  highestY = -1000;

  for (int i = 0; i < total; i++)
  {
    auto flag = flags[i];
    if (i == highestIndex)
    {
      continue;
    }
    if (highestY == -1000)
    {
      highestY = flags[i].y_middle_coord;
      secondHighestIndex = i;
      continue;
    }

    double flagArea = flag.width * flag.height;
    double highestIndexArea = flags[secondHighestIndex].width * flags[secondHighestIndex].height;
    if (flag.y_middle_coord > highestY || (abs(flag.y_middle_coord - highestY) < 20 && flagArea >= highestIndexArea))
    {
      highestY = flag.y_middle_coord;
      secondHighestIndex = i;
    }
  }

  return &flags[highestIndex];
}

pros::vision_object_s_t *get_middle_flag()
{
  std::vector<pros::vision_object_s_t> flags;

  for (int size = 0; size < 3; size++)
  {
    auto flag = visionSensor.get_by_size(size);
    if (flag.width >= 6 && flag.height >= 6 && (flag.signature == BLUE_FLAG || flag.signature == RED_FLAG))
    {
      flags.push_back(flag);
    }
  }

  int total = flags.size();

  if (total < 2)
  {
    return NULL;
  }

  int highestIndex = 0;
  int highestY = -1000;
  int secondHighestIndex = 0;

  for (int i = 0; i < total; i++)
  {
    if (highestY == -1000)
    {
      highestY = flags[i].y_middle_coord;
      highestIndex = i;
      continue;
    }

    auto flag = flags[i];
    double flagArea = flag.width * flag.height;
    double highestIndexArea = flags[highestIndex].width * flags[highestIndex].height;
    if (flag.y_middle_coord > highestY || (abs(flag.y_middle_coord - highestY) < 20 && flagArea >= highestIndexArea))
    {
      highestY = flag.y_middle_coord;
      highestIndex = i;
    }
  }

  highestY = -1000;

  for (int i = 0; i < total; i++)
  {
    auto flag = flags[i];
    if (i == highestIndex)
    {
      continue;
    }
    if (highestY == -1000)
    {
      highestY = flags[i].y_middle_coord;
      secondHighestIndex = i;
      continue;
    }

    double flagArea = flag.width * flag.height;
    double highestIndexArea = flags[secondHighestIndex].width * flags[secondHighestIndex].height;
    if (flag.y_middle_coord > highestY || (abs(flag.y_middle_coord - highestY) < 20 && flagArea >= highestIndexArea))
    {
      highestY = flag.y_middle_coord;
      secondHighestIndex = i;
    }
  }

  return &flags[secondHighestIndex];
}

void shootTwiceAutomated(int current_flag)
{
  printf("shootin\n");

  auto highFlag = get_top_flag();
  auto middleFlag = get_middle_flag();
  bool driveHigh = false;
  bool driveMiddle = false;
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

  if (driveHigh || driveMiddle)
  {
    printf("flags\n%d\n%d\n", highFlag->signature, middleFlag->signature);

    int initialSign = 778;
    int timeWhenDxOk = -1;
    double prevDx = 778;
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
      if (flag->signature != current_flag)
      {
        continue;
      }
      double dx = (double)flag->x_middle_coord + 4.0 * (current_flag == RED_FLAG)? 1 : -1;
      if (prevDx == 778)
      {
        prevDx = dx;
      }
      if (abs(dx - prevDx) > 50)
      {
        continue;
      }
      prevDx = dx;
      bool ok = abs(dx) < 5;
      if (ok && timeWhenDxOk == -1)
      {
        timeWhenDxOk = pros::millis();
      }
      else if (ok && pros::millis() - timeWhenDxOk > 50)
      {
        drivetrain.tank(0.0, 0.0);
        break;
      }
      else if (!ok)
      {
        timeWhenDxOk = -1;
      }
      int sign = (dx > 0) ? 1 : -1;
      if (initialSign == 778)
      {
        initialSign = sign;
      }
      printf("%f, (%d %d)\n", dx, flag->width, flag->height);

      double vel = 0.275;
      if (abs(dx) <= 45)
      {
        vel = 0.114;
      }
      else if (abs(dx) <= 23)
      {
        vel = 0.064;
      }
      else if (abs(dx) <= 3)
      {
        vel = 0.0;
      }
      drivetrain.tank(sign * vel, -sign * vel);
      pros::delay(25);
    }

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