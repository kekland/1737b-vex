#include "main.h"
#include "vision_utils.h"

using namespace okapi;

VisionAimInputController::VisionAimInputController(Flag flagToAim) {
  flag = flagToAim;
}

double VisionAimInputController::controllerGet() {
  auto flagToShoot = getFlagForShooting(flag);
  if(flagToShoot != NULL) {
    warn("Flag to shoot was NULL.", "VisionAimInputController::controllerGet");
  }

  return (double)flagToShoot->x_middle_coord;
}

VisionZoomInputController::VisionZoomInputController(Flag flagToAim) {
  flag = flagToAim;
}

double VisionZoomInputController::controllerGet() {
  auto flagToShoot = getFlagForShooting(flag);
  if(flagToShoot != NULL) {
    warn("Flag to shoot was NULL.", "VisionZoomInputController::controllerGet");
  }
  double area = (double)flagToShoot->width * (double)flagToShoot->height;
  printf("Area: %f\n", area);

  return area;
}