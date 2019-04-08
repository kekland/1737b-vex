#pragma once
#ifndef VISION_UTILS_H_
#define VISION_UTILS_H_

#include "main.h"
std::vector<pros::vision_object_s_t> getFlags();
int getHighestFlagIndex(std::vector<pros::vision_object_s_t> flags, int skip = -1);
pros::vision_object_s_t* getTopFlag();
pros::vision_object_s_t* getMiddleFlag();

bool checkFlag(pros::vision_object_s_t* flag, Flag currentFlag);
pros::vision_object_s_t* getFlagForShooting(Flag currentFlag);

#endif