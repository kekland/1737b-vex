#ifndef AUTONOMOUS_CONTROLLER_H_
#define AUTONOMOUS_CONTROLLER_H_
#include "main.h"
using namespace okapi;

void stop();

void drive(QLength cm);
void turn(QAngle targetDegrees);

#endif