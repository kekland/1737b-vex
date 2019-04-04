#include "main.h"

using namespace okapi;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

pros::vision_object_s_t *get_top_flag()
{
  std::vector<pros::vision_object_s_t> flags;

  for (int size = 0; size < 3; size++)
  {
    auto flag = visionSensor.get_by_size(size);
    printf("%d\n", flag.signature);
    if (flag.width >= 12 && flag.height >= 12 && (flag.signature == BLUE_FLAG || flag.signature == RED_FLAG))
    {
      flags.push_back(flag);
    }
  }

  int total = flags.size();
  printf("%d %d\n", total, visionSensor.get_object_count());

  if (total < 2)
  {
    return NULL;
  }

  int highestIndex = 0;
  int highestY = -1000;
  int secondHighestIndex = 0;

  for (int i = 0; i < total; i++)
  {
    if (highestY == -1000)
    {
      highestY = flags[i].y_middle_coord;
      highestIndex = i;
      continue;
    }

    auto flag = flags[i];
    if (flag.y_middle_coord > highestY || (abs(flag.y_middle_coord - highestY) < 10 && flag.width > flags[highestIndex].width && flag.height > flags[highestIndex].height))
    {
      highestY = flag.y_middle_coord;
      highestIndex = i;
    }
  }

  printf("%d", highestIndex);

  highestY = -1000;

  for (int i = 0; i < total; i++)
  {
    auto flag = flags[i];
    if (i == highestIndex)
    {
      continue;
    }
    if (highestY == -1000)
    {
      highestY = flags[i].y_middle_coord;
      secondHighestIndex = i;
      continue;
    }

    if (flag.y_middle_coord > highestY || (abs(flag.y_middle_coord - highestY) < 20 && flag.width * flag.height > flags[secondHighestIndex].width * flags[secondHighestIndex].height))
    {
      highestY = flag.y_middle_coord;
      secondHighestIndex = i;
    }
  }

  return &flags[highestIndex];
}

pros::vision_object_s_t *get_middle_flag()
{
  std::vector<pros::vision_object_s_t> flags;

  for (int size = 0; size < 3; size++)
  {
    auto flag = visionSensor.get_by_size(size);
    printf("%d\n", flag.signature);
    if (flag.width >= 12 && flag.height >= 12 && (flag.signature == BLUE_FLAG || flag.signature == RED_FLAG))
    {
      flags.push_back(flag);
    }
  }

  int total = flags.size();
  printf("%d %d\n", total, visionSensor.get_object_count());

  if (total < 2)
  {
    return NULL;
  }

  int highestIndex = 0;
  int highestY = -1000;
  int secondHighestIndex = 0;

  for (int i = 0; i < total; i++)
  {
    if (highestY == -1000)
    {
      highestY = flags[i].y_middle_coord;
      highestIndex = i;
      continue;
    }

    auto flag = flags[i];
    if (flag.y_middle_coord > highestY || (abs(flag.y_middle_coord - highestY) < 10 && flag.width > flags[highestIndex].width && flag.height > flags[highestIndex].height))
    {
      highestY = flag.y_middle_coord;
      highestIndex = i;
    }
  }

  printf("%d", highestIndex);

  highestY = -1000;

  for (int i = 0; i < total; i++)
  {
    auto flag = flags[i];
    if (i == highestIndex)
    {
      continue;
    }
    if (highestY == -1000)
    {
      highestY = flags[i].y_middle_coord;
      secondHighestIndex = i;
      continue;
    }

    if (flag.y_middle_coord > highestY || (abs(flag.y_middle_coord - highestY) < 20 && flag.width * flag.height > flags[secondHighestIndex].width * flags[secondHighestIndex].height))
    {
      highestY = flag.y_middle_coord;
      secondHighestIndex = i;
    }
  }

  return &flags[secondHighestIndex];
}

void opcontrol()
{
  drivetrain.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  while (true)
  {
    drivetrain.tank(masterController.getAnalog(ControllerAnalog::leftY),
                    masterController.getAnalog(ControllerAnalog::rightY));

    if (masterController.getDigital(ControllerDigital::up))
    {
      shooterAngleController->control(ShooterAngle::upFlag);
    }
    else if (masterController.getDigital(ControllerDigital::down))
    {
      shooterAngleController->control(ShooterAngle::downFlag);
    }

    if (masterController.getDigital(ControllerDigital::R2))
    {
      shooterController->control(ShooterState::shoot);
    }
    else if (masterController.getDigital(ControllerDigital::right))
    {
      printf("shootin");

      auto highFlag = get_top_flag();
      auto middleFlag = get_middle_flag();
      bool driveHigh = false;
      bool driveMiddle = false;
      if (highFlag != NULL && highFlag->signature == BLUE_FLAG)
      {
        driveHigh = true;
      }
      if (middleFlag != NULL && middleFlag->signature == BLUE_FLAG)
      {
        driveMiddle = true;
      }

      if (driveMiddle || driveHigh)
      {
        while (true)
        {
          auto flag = (driveHigh)? get_top_flag() : get_middle_flag();
          int dx = flag->x_middle_coord + flag->width / 3.0;
          if (abs(dx) < 5)
          {
            drivetrain.tank(0, 0);
            pros::delay(30);
            break;
          }
          printf("%d\n", dx);
          int sign = (dx > 0) ? 1 : -1;
          drivetrain.tank(0.2 * sign, -0.2 * sign);
          pros::delay(25);
        }
      }

      if(highFlag != NULL && highFlag->signature == BLUE_FLAG && middleFlag != NULL && middleFlag->signature == BLUE_FLAG) {
        shooterAngleController->control(ShooterAngle::upFlag);
        pros::delay(200);
        shooterController->control(ShooterState::shoot);
        pros::delay(500);
        shooterController->control(ShooterState::stop);
        pros::delay(150);
        shooterAngleController->control(ShooterAngle::downFlag);
        pros::delay(150);
        shooterController->control(ShooterState::shoot);
        pros::delay(500);
        shooterController->control(ShooterState::stop);
      }
      else if(highFlag != NULL && highFlag->signature == BLUE_FLAG) {
        shooterAngleController->control(ShooterAngle::upFlag);
        pros::delay(200);
        shooterController->control(ShooterState::shoot);
        pros::delay(500);
        shooterController->control(ShooterState::stop);
      }
      else if(middleFlag != NULL && middleFlag->signature == BLUE_FLAG) {
        shooterAngleController->control(ShooterAngle::downFlag);
        pros::delay(200);
        shooterController->control(ShooterState::shoot);
        pros::delay(500);
        shooterController->control(ShooterState::stop);
      }
      pros::delay(100);
    }
    else
    {
      shooterController->control(ShooterState::stop);
    }

    if (masterController.getDigital(ControllerDigital::L1))
    {
      intakeController->control(IntakeDirection::up);
    }
    else if (masterController.getDigital(ControllerDigital::L2))
    {
      intakeController->control(IntakeDirection::down);
    }
    else
    {
      intakeController->control(IntakeDirection::stop);
    }

    pros::delay(25);
  }
}
