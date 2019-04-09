#pragma once
#ifndef VISION_UTILS_H_
#define VISION_UTILS_H_

#include "main.h"
std::vector<pros::vision_object_s_t> getFlags();
std::pair<pros::vision_object_s_t*, pros::vision_object_s_t*> getFlagPair(std::vector<pros::vision_object_s_t> flags);
pros::vision_object_s_t* getTopFlag();
pros::vision_object_s_t* getMiddleFlag();

bool checkFlag(pros::vision_object_s_t* flag, Flag currentFlag);
pros::vision_object_s_t* getFlagForShooting(Flag currentFlag);

#endif