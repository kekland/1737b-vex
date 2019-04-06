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
    if (flag.width >= 12 && flag.height >= 12 && (flag.signature == BLUE_FLAG || flag.signature == RED_FLAG))
    {
      flags.push_back(flag);
    }
  }

  int total = flags.size();

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
    if (flag.width >= 12 && flag.height >= 12 && (flag.signature == BLUE_FLAG || flag.signature == RED_FLAG))
    {
      flags.push_back(flag);
    }
  }

  int total = flags.size();

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

int current_flag = RED_FLAG;
void opcontrol()
{
  shooterAngle.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
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
    else if (masterController.getDigital(ControllerDigital::R1))
    {
      shooterController->shootTwice();
    }
    else
    {
      shooterController->control(ShooterState::stop);
    }

    if (masterController.getDigital(ControllerDigital::right))
    {
      while(masterController.getDigital(ControllerDigital::right)) {pros::delay(20);}
      current_flag = (current_flag == RED_FLAG)? BLUE_FLAG : RED_FLAG;
    }

    if (masterController.getDigital(ControllerDigital::left))
    {
      printf("shootin\n");

      auto highFlag = get_top_flag();
      auto middleFlag = get_middle_flag();
      bool driveHigh = false;
      bool driveMiddle = false;
      if (highFlag != NULL)
      {
        if (highFlag->signature == current_flag)
        {
          driveHigh = true;
        }
      }
      if (middleFlag != NULL)
      {
        if (middleFlag->signature == current_flag)
        {
          driveMiddle = true;
        }
      }

      if (driveHigh || driveMiddle)
      {
        printf("flags\n%d\n%d\n", highFlag->signature, middleFlag->signature);

        int initialSign = 778;
        while (true)
        {
          auto flag = (driveHigh) ? get_top_flag() : get_middle_flag();
          if (flag == NULL)
          {
            continue;
          }
          if (flag->signature != RED_FLAG && flag->signature != BLUE_FLAG)
          {
            continue;
          }
          double dx = (double)flag->x_middle_coord;
          if (abs(dx) < 4)
          {
            drivetrain.tank(0.0, 0.0);
            pros::delay(50);
            break;
          }
          printf("%d\n", dx);
          int sign = (dx > 0) ? 1 : -1;
          if (initialSign == 778)
          {
            initialSign = sign;
          }
          int absdx = abs(dx);
          double vel = 0.2;
          if (absdx <= 10)
          {
            vel = 0.075;
          }
          else if (absdx <= 5)
          {
            vel = 0.05;
          }
          drivetrain.tank(vel * sign, -vel * sign);
          pros::delay(25);
        }

        if (driveHigh && driveMiddle)
        {
          shooterController->shootTwice();
        }
        else if (driveHigh)
        {
          shooterAngleController->control(ShooterAngle::upFlag);
          pros::delay(200);
          shooterController->shootOnce();
        }
        else if (driveMiddle)
        {
          shooterAngleController->control(ShooterAngle::downFlag);
          pros::delay(200);
          shooterController->shootOnce();
        }
        pros::delay(100);
      }
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
