#include "main.h"

void shootTwiceTask(void *args)
{
  opcontrolState->drivetrainEnabled = true;
  opcontrolState->shooterAngleEnabled = false;
  opcontrolState->shooterEnabled = false;

  shooterController->shootTwice();

  opcontrolState->gracefulEndTask();
}