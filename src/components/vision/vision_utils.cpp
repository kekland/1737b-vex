#include "main.h"

std::vector<pros::vision_object_s_t> getFlags() {
  std::vector<pros::vision_object_s_t> flags;

  for (int size = 0; size < 3; size++)
  {
    auto flag = visionSensor.get_by_size(size);
    if (flag.width >= 6 && flag.height >= 6 && (flag.signature == BLUE_FLAG || flag.signature == RED_FLAG))
    {
      flags.push_back(flag);
    }
  }

  return flags;
}