#pragma once
#ifndef VISION_H_
#define VISION_H_

#include "main.h"

void aimAndZoomAutomated(Flag currentFlag);
void shootTwiceAutomated(Flag currentFlag);

void shootTwiceAutomatedTask(void* param);
void aimAndZoomAutomatedTask(void* param);
#endif