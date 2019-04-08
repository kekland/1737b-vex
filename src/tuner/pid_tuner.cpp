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
  /*info("Starting to tune autoaim.", "tuneAutoaim");
  std::shared_ptr<VisionAimInputController> input = std::make_shared<VisionAimInputController>(VisionAimInputController(Flag::red));
  std::shared_ptr<DrivetrainTurnController> output = std::make_shared<DrivetrainTurnController>(DrivetrainTurnController());

  auto tuner = PIDTunerFactory::create(input,
                                       output, 
                                       2_s, 0, 0.0, 0.2, 0.0, 0.2, 0.0, 0.2, 20);
  
  auto values = tuner.autotune();
  printf("Tuned: %f %f %f\n", values.kP, values.kI, values.kD);

  FILE* outputFile = fopen("pid_output.txt", "w");
  fprintf(outputFile, "%f %f %f\n", values.kP, values.kI, values.kD);
  fclose(outputFile);
  
  info("Finished tuning.", "tuneAutoaim");*/
}

void tune()
{
  tuneAutoaim();
}
