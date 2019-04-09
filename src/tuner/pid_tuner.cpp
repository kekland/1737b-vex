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
  std::shared_ptr<VisionZoomInputController> input = std::make_shared<VisionZoomInputController>(VisionZoomInputController(Flag::red));
  std::shared_ptr<DrivetrainForwardController> output = std::make_shared<DrivetrainForwardController>(DrivetrainForwardController());

  auto tuner = PIDTunerFactory::create(input,
                                       output, 
                                       2_s, 0, 760.0, 0.01, 0.0, 0.01, 0.0, 0.01, 30);
  
  auto values = tuner.autotune();
  printf("Tuned: %f %f %f\n", values.kP, values.kI, values.kD);

  FILE* outputFile = fopen("pid_output.txt", "w");
  fprintf(outputFile, "%f %f %f\n", values.kP, values.kI, values.kD);
  fclose(outputFile);
  
  info("Finished tuning.", "tuneAutoaim");
}

void tune()
{
  tuneAutoaim();
}
