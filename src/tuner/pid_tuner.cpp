#include "main.h"
#include "../components/vision/vision_controller.h"

using namespace okapi;

void tune()
{
  tuneAutoaim();
}

void DrivetrainForwardController::controllerSet(double value)
{
  drivetrain.forward(value);
}

void DrivetrainTurnController::controllerSet(double value)
{
  drivetrain.rotate(value);
}
void tuneAutoaim()
{
  info("Starting to tune autoaim.", "tuneAutoaim");
  auto input = VisionAimInputController(Flag::red);
  auto output = DrivetrainTurnController();

  auto tuner = PIDTunerFactory::create(std::make_shared<okapi::ControllerInput<double>>(input),
                                       std::make_shared<okapi::ControllerOutput<double>>(output), 
                                       2_s, 0, 0.0, 0.2, 0.0, 0.2, 0.0, 0.2, 20);
  
  auto values = tuner.autotune();
  printf("Tuned: %f %f %f\n", values.kP, values.kI, values.kD);

  FILE* outputFile = fopen("pid_output.txt", "w");
  fprintf(outputFile, "%f %f %f\n", values.kP, values.kI, values.kD);
  fclose(outputFile);
  
  info("Finished tuning.", "tuneAutoaim");
}