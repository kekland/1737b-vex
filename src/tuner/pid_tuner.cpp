#include "main.h"
#include "../components/vision/vision_controller.h"

using namespace okapi;

void DrivetrainForwardController::controllerSet(double ivalue)
{
  drivetrain->forward(ivalue);
}

void DrivetrainTurnController::controllerSet(double ivalue)
{
  drivetrain->rotate(ivalue);
}

void tuneAutoaim()
{
  info("Starting to tune autoaim.", "tuneAutoaim");
  pros::lcd::print(0, "Tuning now! %s", "Zhangir loh");
  std::shared_ptr<ADIGyro> input = std::make_shared<ADIGyro>(gyro);
  std::shared_ptr<DrivetrainTurnController> output = std::make_shared<DrivetrainTurnController>(DrivetrainTurnController());

  auto tuner = PIDTunerFactory::createPtr(input,
                                          output,
                                          2_s, 90.0, 0.0001, 0.05, 0.0001, 0.05, 0.0001, 0.05, 10);

  okapi::PIDTuner::Output values = tuner->autotune();
  printf("Tuned: %f %f %f\n", values.kP, values.kI, values.kD);
  pros::lcd::print(1, "Tuned %f %f %f", values.kP, values.kI, values.kD);

  info("Finished tuning.", "tuneAutoaim");
}

void tune()
{
  tuneAutoaim();
}
