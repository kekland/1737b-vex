#include "main.h"

pros::Vision visionSensor(18, pros::E_VISION_ZERO_CENTER);
okapi::ADIGyro gyro(1, 0.9715);


void configure_vision() {
  // Set LED color to green (0, 255, 0)
  visionSensor.clear_led();
  visionSensor.set_led(65280);

  // Set the signatures
  pros::vision_signature_s_t RED_SIG = visionSensor.signature_from_utility(1, 7077, 8495, 7786, -631, 263, -184, 5.900, 0);
  pros::vision_signature_s_t BLUE_SIG = visionSensor.signature_from_utility(2, -4133, -2875, -3504, 9551, 16115, 12833, 3.0, 0);
  
  visionSensor.set_signature(1, &RED_SIG);
  visionSensor.set_signature(2, &BLUE_SIG);

  // Set the exposure
  visionSensor.set_exposure(58);

  //Wait 100ms for calibration
  pros::delay(100);
}

void configure_sensors() {
  info("Starting configuration", "config_sensors");

  configure_vision();

  //Wait 1sec for gyro calibration
  pros::delay(1000);
  
  info("Finished configuration", "config_sensors");
}