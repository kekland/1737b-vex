#include "main.h"
#include "motors/config_motors.h"
#include "sensors/config_sensors.h"
#include "devices/config_devices.h"
#include "controllers/config_controllers.h"
#include "pid/config_pid.h"

void configure()
{
  configure_motors();
  configure_sensors();
  configure_devices();
  configure_controllers();
  configure_pid();
}