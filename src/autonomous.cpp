#include "main.h"
#include "./autonomous/autonomous_controller.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void autonomous() {
  intakeController->control(IntakeDirection::up);
  drive(130.0);
  pros::delay(200);
  intakeController->control(IntakeDirection::stop);
  drive(-115.0);
  turn(-90.0);
  shootTwiceAutomated(BLUE_FLAG);
  turn(45.0);
  intakeController->control(IntakeDirection::down);
  drive(115.0);
  turn(-45.0);
  drive(-160.0);
}
