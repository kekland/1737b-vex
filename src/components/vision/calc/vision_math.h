#ifndef VISION_MATH_H_
#define VISION_MATH_H_

#include "main.h"

QLength calculateDistanceToFlag(pros::vision_object_s_t *flag, bool isTopFlag);
QLength calculateVerticalDistanceToFlag(pros::vision_object_s_t *flag);
QLength calculateHorizontalErrorFromFlag(pros::vision_object_s_t *flag);
QAngle calculateVerticalAngle(QLength verticalDistance, QLength distance);
QLength calculateFlatDistanceToFlag(QLength verticalDistance, QLength distance);
QAngle calculateHorizontalAngle(QLength horizontalError, QLength flatDistance);

#endif