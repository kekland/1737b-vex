#include "main.h"
#include "components/intake/basic_intake_controller.h";
#include "components/shooter/basic_shooter_controller.h";
#include "components/shooterAngle/basic_shooter_angle_controller.h";

using namespace okapi;

/* Basic data such as gearsets, drive scales, etc */

AbstractMotor::gearset driveGearset = AbstractMotor::gearset::green;
ChassisScales driveScales = ChassisScales({4.0_in, 32.0_cm});

/* Motors and MotorGroups */

Motor driveLeftFront = Motor(1, false, driveGearset);
Motor driveLeftBack = Motor(2, false, driveGearset);
Motor driveRightFront = Motor(9, true, driveGearset);
Motor driveRightBack = Motor(10, true, driveGearset);

MotorGroup driveLeft = MotorGroup({driveLeftBack, driveLeftFront});
MotorGroup driveRight = MotorGroup({driveLeftBack, driveLeftFront});

Motor intake = Motor(4, false, AbstractMotor::gearset::green);
Motor shooter = Motor(5, false, AbstractMotor::gearset::green);
Motor shooterAngle = Motor(6, false, AbstractMotor::gearset::green);

/* Higher-level stuff like ChassisControllers, Controllers, etc. */
auto _shooterAngleController = AsyncControllerFactory::posIntegrated(shooterAngle, 200);

auto drivetrain = ChassisControllerFactory::create(driveLeft, driveRight, driveGearset, driveScales);
auto masterController = Controller();

std::shared_ptr<BaseIntakeController> intakeController =
    std::make_shared<BaseIntakeController>(SimpleIntakeController(intake, 200.0));

std::shared_ptr<BaseShooterController> shooterController =
    std::make_shared<BaseShooterController>(SimpleShooterController(shooter));

std::shared_ptr<BaseShooterAngleController> shooterAngleController =
    std::make_shared<BaseShooterAngleController>(SimpleShooterAngleController(_shooterAngleController, {20.0, 30.0}));
