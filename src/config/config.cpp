#include "main.h"
#include "../components/intake/basic_intake_controller.h"
#include "../components/shooter/basic_shooter_controller.h"
#include "../components/shooterAngle/basic_shooter_angle_controller.h"

using namespace okapi;

/* Basic data such as gearsets, drive scales, etc */

AbstractMotor::gearset driveGearset = AbstractMotor::gearset::green;
ChassisScales driveScales = ChassisScales({4.0_in, 32.0_cm});

/* Motors and MotorGroups */

Motor driveLeftFront = Motor(12, false, driveGearset);
Motor driveLeftBack = Motor(13, false, driveGearset);
Motor driveRightFront = Motor(19, true, driveGearset);
Motor driveRightBack = Motor(18, true, driveGearset);

MotorGroup driveLeft = MotorGroup({driveLeftBack, driveLeftFront});
MotorGroup driveRight = MotorGroup({driveRightBack, driveRightFront});

Motor intake = Motor(14, true, AbstractMotor::gearset::green);
Motor shooter = Motor(15, true, AbstractMotor::gearset::green);
Motor shooterAngle = Motor(10, false, AbstractMotor::gearset::green);

/* Higher-level stuff like ChassisControllers, Controllers, etc. */
okapi::AsyncPosIntegratedController _saController = AsyncControllerFactory::posIntegrated(shooterAngle, 100);

okapi::ChassisControllerIntegrated drivetrain = ChassisControllerFactory::create(driveLeft, driveRight, driveGearset, driveScales);
okapi::Controller masterController = Controller();

auto _intakeController = SimpleIntakeController(intake, 200.0);
auto _shooterController = SimpleShooterController(shooter);
auto _shooterAngleController = SimpleShooterAngleController(_saController, {27.0, 57.0});

BaseIntakeController *intakeController = &_intakeController;

BaseShooterController *shooterController = &_shooterController;

BaseShooterAngleController *shooterAngleController = &_shooterAngleController;

pros::Vision visionSensor(17, pros::E_VISION_ZERO_CENTER);

void configure() {
    shooterAngle.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    visionSensor.clear_led();
    pros::vision_signature_s_t RED_SIG = visionSensor.signature_from_utility(1, 7077, 8495, 7786, -631, 263, -184, 5.900, 0);
    pros::vision_signature_s_t BLUE_SIG = visionSensor.signature_from_utility(2, -4133, -2875, -3504, 9551, 16115, 12833, 3.0, 0);
    visionSensor.set_exposure(58);
    visionSensor.set_signature(1, &RED_SIG);
    visionSensor.set_signature(2, &BLUE_SIG);
}