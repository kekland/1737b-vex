#ifndef AUTONOMOUS_CONTROLLER_H_
#define AUTONOMOUS_CONTROLLER_H_
#include "main.h"

void stop();

void drive(double cm);
void turn(double targetDegrees);

#endif