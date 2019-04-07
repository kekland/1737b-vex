#ifndef VISION_CONTROLLER_H_
#define VISION_CONTROLLER_H_

#include "main.h"

using namespace okapi;
class VisionAimInputController: public ControllerInput<double> {
  VisionAimInputController(Flag flagToAim);
  double controllerGet() override;
  Flag flag;
};

class VisionZoomInputController: public ControllerInput<double> {
  VisionZoomInputController(Flag flagToAim);
  double controllerGet() override;
  Flag flag;
};

#endif