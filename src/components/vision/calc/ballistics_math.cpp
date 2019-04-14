#include "main.h"

using namespace okapi;
const QSpeed ballSpeed = 20.0_mps;

QAngle angleToHitCoordinates(QLength flatDistance, QLength verticalDistance) {
  double x = flatDistance.convert(meter);
  double y = verticalDistance.convert(meter);
  double v = ballSpeed.convert(mps);
  double g = gravity;

  double sqr = pow(v, 4) - g * (g * pow(x, 2) + 2 * y * pow(v, 2));
  double top = pow(v, 2) - sqrt(sqr);

  double bot = g * x;

  double angle = atan2(bot, top);

  return angle * radian;
}