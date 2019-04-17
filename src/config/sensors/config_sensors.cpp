#include "main.h"

pros::Vision visionSensor(14, pros::E_VISION_ZERO_CENTER);
okapi::ADIGyro gyro(1, 0.9715);
okapi::ADIUltrasonic ultrasonic(3, 4);
pros::ADILineSensor intakeLineSensor = pros::ADILineSensor(2);
int lineSensorMid = 0; 

void configure_vision()
{
  // Set LED color to green (0, 255, 0)
  visionSensor.clear_led();
  //visionSensor.set_led(65280);

  // Set the signatures
  //  Working almost nicely
   pros::vision_signature_s_t RED_SIG = visionSensor.signature_from_utility(1, 6145, 10497, 8322, -1087, -147, -616, 3.000, 0);
   pros::vision_signature_s_t BLUE_SIG = visionSensor.signature_from_utility(2, -4741, -3709, -4226, 7399, 10115, 8756, 4.200, 0);

  //  Doesn't work
  //pros::vision_signature_s_t RED_SIG = visionSensor.signature_from_utility(1, 1419, 9921, 5670, -2191, -1205, -1698, 1.000, 0);
  //pros::vision_signature_s_t BLUE_SIG = visionSensor.signature_from_utility(2, -4891, -2827, -3858, 3323, 6055, 4688, 2.000, 0);
  //pros::vision_signature_s_t RED_SIG = visionSensor.signature_from_utility(1, 7949, 10041, 8995, -1, 707, 353, 4.900, 0);
  //pros::vision_signature_s_t BLUE_SIG = visionSensor.signature_from_utility(2, -3537, -2859, -3198, 11551, 13257, 12404, 4.600, 0);
  visionSensor.set_exposure(68);
  //visionSensor.set_exposure(44);
  visionSensor.set_signature(1, &RED_SIG);
  visionSensor.set_signature(2, &BLUE_SIG);
  // Set the exposure

  intakeLineSensor.calibrate();
  //Wait 100ms for calibration

  int startTime = pros::millis();
  int iters = 0;
  while(true) {
    pros::delay(10);
    if(pros::millis() - startTime > 1000) {
      break;
    }
    lineSensorMid += intakeLineSensor.get_value_calibrated();
    iters++;
  }

  lineSensorMid /= iters;

  pros::delay(100);
}

void configure_sensors()
{
  info("Starting configuration", "config_sensors");

  configure_vision();

  //Wait 1sec for gyro calibration
  pros::delay(1000);

  info("Finished configuration", "config_sensors");
}