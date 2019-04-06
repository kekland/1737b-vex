#ifndef CONFIG_H_
#define CONFIG_H_

#include "main.h"

using namespace okapi;

/* Higher-level stuff like ChassisControllers, Controllers, etc. */

extern okapi::ChassisControllerIntegrated drivetrain;
extern okapi::Controller masterController;

extern Motor shooter;
extern Motor shooterAngle;

extern MotorGroup driveLeft;
extern MotorGroup driveRight;

extern BaseIntakeController* intakeController;
extern BaseShooterController* shooterController;
extern BaseShooterAngleController* shooterAngleController;
extern pros::Vision visionSensor;
extern okapi::ADIGyro gyro;

extern IterativePosPIDController leftDriveController;
extern IterativePosPIDController rightDriveController;
extern IterativePosPIDController turnController;

extern void configure();

#endif