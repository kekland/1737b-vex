#include "main.h"

std::vector<pros::vision_object_s_t> getFlags()
{
  std::vector<pros::vision_object_s_t> flags;

  for (int size = 0; size < 3; size++)
  {
    auto flag = visionSensor.get_by_size(size);
    if (flag.width >= 6 && flag.height >= 6 && (flag.signature == (int)Flag::red || flag.signature == (int)Flag::blue))
    {
      flags.push_back(flag);
    }
  }

  return flags;
}

int getHighestFlagIndex(std::vector<pros::vision_object_s_t> flags, int skip = -1)
{
  int highestIndex = 0;
  int highestY = -1000;
  int secondHighestIndex = 0;

  for (int i = 0; i < flags.size(); i++)
  {
    auto flag = flags[i];

    if (i == skip)
    {
      continue;
    }

    if (highestY == -1000)
    {
      highestY = flag.y_middle_coord;
      highestIndex = i;
      continue;
    }

    double flagArea = flag.width * flag.height;
    double highestIndexArea = flags[highestIndex].width * flags[highestIndex].height;
    if (flag.y_middle_coord > highestY || (abs(flag.y_middle_coord - highestY) < 20 && flagArea >= highestIndexArea))
    {
      highestY = flag.y_middle_coord;
      highestIndex = i;
    }
  }

  return highestIndex;
}

pros::vision_object_s_t *getTopFlag()
{
  std::vector<pros::vision_object_s_t> flags = getFlags();

  int total = flags.size();

  if (total < 2)
  {
    return NULL;
  }

  return &flags[getHighestFlagIndex(flags)];
}

pros::vision_object_s_t *getMiddleFlag()
{
  std::vector<pros::vision_object_s_t> flags = getFlags();

  int total = flags.size();

  if (total < 2)
  {
    return NULL;
  }

  int topFlagIndex = getHighestFlagIndex(flags);
  int middleFlagIndex = getHighestFlagIndex(flags, topFlagIndex);

  return &flags[middleFlagIndex];
}

bool checkFlag(pros::vision_object_s_t *flag, Flag currentFlag)
{
  if (flag != NULL)
  {
    if (flag->signature == (int)currentFlag)
    {
      return true;
    }
  }

  return false;
}

pros::vision_object_s_t *getFlagForShooting(Flag currentFlag)
{
  auto highFlag = getTopFlag();
  auto middleFlag = getMiddleFlag();

  bool shouldShootHighFlag = checkFlag(highFlag, currentFlag);
  bool shouldShootMiddleFlag = checkFlag(middleFlag, currentFlag);

  if (shouldShootHighFlag)
  {
    return highFlag;
  }
  else if (shouldShootMiddleFlag)
  {
    return middleFlag;
  }

  return NULL;
}