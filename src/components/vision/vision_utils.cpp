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
  int highestIndex = -1;

  for (int i = 0; i < flags.size(); i++)
  {
    auto flag = flags[i];
    auto highestFlag = flags[highestIndex];

    if (i == skip)
    {
      continue;
    }

    if (highestIndex == -1)
    {
      highestIndex = i;
      continue;
    }

    double flagArea = flag.width * flag.height;
    double highestFlagArea = highestFlag.width * highestFlag.height;

    bool isFlagHigher = flag.y_middle_coord > highestFlag.y_middle_coord;
    bool isFlagMoreArea = flagArea >= highestFlagArea;
    bool isFlagAlmostSameLevel = abs(flag.y_middle_coord - highestFlag.y_middle_coord) < 20;

    bool isFlagAlmostSameArea = abs(flagArea - highestFlagArea) < 30;
    bool isFlagCloserToCenter = abs(flag.x_middle_coord) < abs(highestFlag.x_middle_coord);
    if ((isFlagHigher) ||
        (isFlagAlmostSameLevel && isFlagMoreArea) ||
        (isFlagAlmostSameLevel && isFlagAlmostSameArea && isFlagCloserToCenter))
    {
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