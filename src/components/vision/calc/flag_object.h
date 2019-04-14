#ifndef FLAG_OBJECT_H_
#define FLAG_OBJECT_H_

#include "main.h"

struct FlagObject {
  pros::vision_object_s_t* flagPointer;
  bool isTopFlag;
};

#endif