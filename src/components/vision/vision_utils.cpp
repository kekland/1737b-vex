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

std::pair<pros::vision_object_s_t*, pros::vision_object_s_t*> getFlagPair()
{
  std::vector<pros::vision_object_s_t> flags = getFlags();

  int total = flags.size();

  for (int i = 0; i < flags.size(); i++)
  {
    for (int j = 0; j < flags.size(); j++)
    {

      int dxI = abs(flags[i].x_middle_coord);
      int dxJ = abs(flags[j].x_middle_coord);

      if (dxI < dxJ)
      {
        pros::vision_object_s_t temp = flags[i];
        flags[i] = flags[j];
        flags[j] = temp;
      }
    }
  }

  std::pair<int, int> range_mid = std::make_pair<int, int>(-40, 30);

  std::vector<pros::vision_object_s_t> topFlags = {};
  std::vector<pros::vision_object_s_t> midFlags = {};

  for (int i = 0; i < flags.size(); i++)
  {
    auto flag = flags[i];
    //printf("flag: pos: (%d %d) size: (%d %d) sig: %s ", flag.x_middle_coord, flag.y_middle_coord, flag.width, flag.height,
    //       flag.signature == (int)Flag::red ? "red" : (flag.signature == (int)Flag::blue) ? "blue": "unknown");

    int posY = flag.y_middle_coord;
    if (posY >= range_mid.first && posY <= range_mid.second)
    {
      //printf("mid");
      midFlags.push_back(flags[i]);
    }
    else if (posY > range_mid.second)
    {
      //printf("top");
      topFlags.push_back(flags[i]);
    }
    //printf("\n");
  }
  pros::vision_object_s_t* topFlag = (topFlags.size() == 0)? NULL : new pros::vision_object_s_t(topFlags[0]);
  pros::vision_object_s_t* midFlag = (midFlags.size() == 0)? NULL : new pros::vision_object_s_t(midFlags[0]);
  
  //printf("top %s\n", (topFlag != NULL)? "exists" : "doesnt exist");
  //printf("mid %s\n", (topFlag != NULL)? "exists" : "doesnt exist");
  return std::make_pair(topFlag, midFlag);
}

pros::vision_object_s_t *getTopFlag()
{
  pros::vision_object_s_t *topFlag = getFlagPair().first;
  return topFlag;
}

pros::vision_object_s_t *getMiddleFlag()
{
  pros::vision_object_s_t *midFlag = getFlagPair().second;
  return midFlag;
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

  if (shouldShootHighFlag && shouldShootMiddleFlag)
  {
    return (highFlag->width > middleFlag->width)? highFlag : middleFlag;
  }
  else if(shouldShootHighFlag) {
    return highFlag;
  }
  else if (shouldShootMiddleFlag)
  {
    return middleFlag;
  }

  return NULL;
}