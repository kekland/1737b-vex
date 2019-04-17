#include "main.h"

using namespace okapi;

const QLength flagWidth = 13.2_cm;
const QLength flagHeight = 13.9_cm;

const double areaTopFlagAtOneMeterInPixels = 685;    //TODO: calculate this
const double distanceTopFlag = 1.3;
const double areaMiddleFlagAtOneMeterInPixels = 1100; //px
const double distanceMidFlag = 1;

const double cameraWidthInPixels = 640.0;
const double cameraHeightInPixels = 400.0;

QLength calculateDistanceToFlag(pros::vision_object_s_t *flag, bool isTopFlag)
{
  double areaAtOneMeterInPixels = (isTopFlag) ? areaTopFlagAtOneMeterInPixels
                                              : areaMiddleFlagAtOneMeterInPixels;
  double area = flag->width * flag->height;

  //Inverse square law.
  QLength distance = sqrt(areaAtOneMeterInPixels / area) * meter * ((isTopFlag)? distanceTopFlag : distanceMidFlag);
  return distance;
}

QLength calculateVerticalDistanceToFlag(pros::vision_object_s_t *flag)
{
  double distanceFromBottomInPixels = (double)flag->y_middle_coord;// + (cameraHeightInPixels / 2.0);
  double distanceFromBottomInFlags = (distanceFromBottomInPixels / (double)flag->height);

  printf("vert | %d / %d -> %f\n", flag->y_middle_coord, flag->height, distanceFromBottomInFlags);

  return distanceFromBottomInFlags * flagHeight;
}

QLength calculateHorizontalErrorFromFlag(pros::vision_object_s_t *flag) {
  double errorInPixels = (double)flag->x_middle_coord;
  double errorInFlags = errorInPixels / (double)flag->width;

  printf("horiz | %d / %d -> %f\n", flag->x_middle_coord, flag->width, errorInFlags);

  return errorInFlags * flagWidth;
}

QAngle calculateVerticalAngle(QLength verticalDistance, QLength distance) {
  double verticalDistanceInMeters = verticalDistance.convert(meter);
  double distanceInMeters = distance.convert(meter);

  QAngle verticalAngle = asin(verticalDistanceInMeters / distanceInMeters) * radian;
  return verticalAngle;
}

QLength calculateFlatDistanceToFlag(QLength verticalDistance, QLength distance)
{
  // Calculating with angles - deprecated
  QAngle verticalAngle = calculateVerticalAngle(verticalDistance, distance);
  double verticalAngleInRadians = verticalAngle.convert(radian);

  // Pythagoras
  // double verticalDistanceInMetersSquared = pow(verticalDistance.convert(meter), 2);
  // double distanceInMetersSquared = pow(distance.convert(meter), 2);

  // printf("flat | %f %f\n", distanceInMetersSquared, verticalDistanceInMetersSquared);

  double flatDistanceInMeters = cos(verticalAngleInRadians) * distance.convert(meter); // = sqrt(distanceInMetersSquared - verticalDistanceInMetersSquared);
  return flatDistanceInMeters * meter;
}

QAngle calculateHorizontalAngle(QLength horizontalError, QLength flatDistance) {
  double horizontalErrorInMeters = horizontalError.convert(meter);
  double flatDistanceInMeters = flatDistance.convert(meter);

  double angleInRadians = atan(horizontalErrorInMeters / flatDistanceInMeters);

  return angleInRadians * radian;
}