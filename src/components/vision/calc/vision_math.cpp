#include "main.h"

using namespace okapi;

const QLength flagWidth = 13.2_mm;
const QLength flagHeight = 13.2_mm;

const double areaTopFlagAtOneMeterInPixels = 1100;    //TODO: calculate this
const double areaMiddleFlagAtOneMeterInPixels = 1100; //px

const double cameraWidthInPixels = 640.0;
const double cameraHeightInPixels = 400.0;

QLength calculateDistanceToFlag(pros::vision_object_s_t *flag, bool isTopFlag)
{
  double areaAtOneMeterInPixels = (isTopFlag) ? areaTopFlagAtOneMeterInPixels
                                              : areaMiddleFlagAtOneMeterInPixels;
  double area = flag->width * flag->height;

  //Inverse square law.
  QLength distance = sqrt(areaAtOneMeterInPixels / area) * meter;
  return distance;
}

QLength calculateVerticalDistanceToFlag(pros::vision_object_s_t *flag)
{
  double distanceFromBottomInPixels = flag->y_middle_coord + (cameraHeightInPixels / 2.0);
  double distanceFromBottomInFlags = (distanceFromBottomInPixels / flag->height);

  return distanceFromBottomInFlags * flagHeight;
}

QLength calculateHorizontalErrorFromFlag(pros::vision_object_s_t *flag) {
  double errorInPixels = flag->x_middle_coord;
  double errorInFlags = errorInPixels / flag->width;

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
  // QAngle verticalAngle = calculateVerticalAngle(verticalDistance, distance);
  // double verticalAngleInRadians = verticalAngle.convert(radian);

  // Pythagoras
  double verticalDistanceInMetersSquared = pow(verticalDistance.convert(meter), 2);
  double distanceInMetersSquared = pow(distance.convert(meter), 2);

  double flatDistanceInMeters = sqrt(distanceInMetersSquared - verticalDistanceInMetersSquared);
  return flatDistanceInMeters * meter;
}

QAngle calculateHorizontalAngle(QLength horizontalError, QLength flatDistance) {
  double horizontalErrorInMeters = horizontalError.convert(meter);
  double flatDistanceInMeters = flatDistance.convert(meter);

  double angleInRadians = atan(horizontalErrorInMeters / flatDistanceInMeters);

  return angleInRadians * radian;
}