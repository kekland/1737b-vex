#ifndef VISION_CONTROLLER_H_
#define VISION_CONTROLLER_H_

#include "main.h"

using namespace okapi;
class VisionAimInputController : public ControllerInput<double>
{
public:
  VisionAimInputController(Flag flagToAim);
  double controllerGet() override;
  Flag flag;
};

class VisionZoomInputController : public ControllerInput<double>
{
public:
  VisionZoomInputController(Flag flagToAim);
  double controllerGet() override;
  Flag flag;
};

#endif