#include "main.h"
#include "vision_controller.h"
#include "vision_utils.h"

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

  return (double)flagToShoot->width;
}