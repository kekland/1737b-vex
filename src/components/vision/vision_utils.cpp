#include "main.h"

std::vector<pros::vision_object_s_t> getFlags()
{
  std::vector<pros::vision_object_s_t> flags;

  for (int size = 0; size < 9; size++)
  {
    auto flag = visionSensor.get_by_size(size);
    double area = flag.width * flag.height;
    int diff = abs(flag.width - flag.height);
    if (flag.width >= 8 && flag.height >= 8 && diff <= 8 && (flag.signature == (int)Flag::red || flag.signature == (int)Flag::blue))
    {
      flags.push_back(flag);
    }
  }

  return flags;
}

int getHighestFlagIndex(std::vector<pros::vision_object_s_t> flags, int skip = -1)
{
  int highestIndex = -1;

  for(int i = 0; i < flags.size(); i++) {
    for(int j = 0; j < flags.size(); j++) {
      int yPosI = -(flags[i].y_middle_coord - 106);
      int yPosJ = -(flags[j].y_middle_coord - 106);

      int dxI = abs(flags[i].x_middle_coord);
      int dxJ = abs(flags[j].x_middle_coord);

      if(yPosI < yPosJ) {
        pros::vision_object_s_t temp = flags[i];
        flags[i] = flags[j];
        flags[j] = temp;
      }
    }
  }

  for (int i = 0; i < flags.size(); i++)
  {
    auto flag = flags[i];
    printf("flag: pos: (%d %d) size: (%d %d) sig: %s\n", flag.x_middle_coord, flag.y_middle_coord, flag.width, flag.height,
           flag.signature == (int)Flag::red ? "red" : "blue");
    /*auto flag = flags[i];
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
    }*/
  }

  printf("highest: %d, skip: %d\n", highestIndex, skip);

  return highestIndex;
}

pros::vision_object_s_t *getTopFlag()
{
  std::vector<pros::vision_object_s_t> flags = getFlags();

  int total = flags.size();

  printf("total top %d\n", total);
  if (total < 2)
  {
    return NULL;
  }

  int highestFlagIndex = getHighestFlagIndex(flags);

  if (highestFlagIndex == -1)
  {
    return NULL;
  }

  printf("high flag signature: %d\n", flags[highestFlagIndex].signature);
  return &(flags[highestFlagIndex]);
}

pros::vision_object_s_t *getMiddleFlag()
{
  std::vector<pros::vision_object_s_t> flags = getFlags();

  int total = flags.size();

  printf("total middle %d\n", total);
  if (total < 2)
  {
    return NULL;
  }

  int topFlagIndex = getHighestFlagIndex(flags);
  int middleFlagIndex = getHighestFlagIndex(flags, topFlagIndex);
  printf("middle top index %d, middle middle index:\n", topFlagIndex, middleFlagIndex);

  if (middleFlagIndex == -1)
  {
    return NULL;
  }

  printf("middle flag signature: %d\n", flags[middleFlagIndex].signature);
  return &(flags[middleFlagIndex]);
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