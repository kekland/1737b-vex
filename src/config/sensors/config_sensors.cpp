#include "main.h"

pros::Vision visionSensor(18, pros::E_VISION_ZERO_CENTER);
okapi::ADIGyro gyro(1, 0.9715);

void configure_sensors() {
  configure_vision();
}

void configure_vision() {
  visionSensor.clear_led();
  pros::vision_signature_s_t RED_SIG = visionSensor.signature_from_utility(1, 7077, 8495, 7786, -631, 263, -184, 5.900, 0);
  pros::vision_signature_s_t BLUE_SIG = visionSensor.signature_from_utility(2, -4133, -2875, -3504, 9551, 16115, 12833, 3.0, 0);
  visionSensor.set_exposure(58);
  visionSensor.set_signature(1, &RED_SIG);
  visionSensor.set_signature(2, &BLUE_SIG);
}