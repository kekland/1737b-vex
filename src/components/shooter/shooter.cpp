#include "main.h"

void controlShooter(ShooterState state) {
  shooter.move_velocity((int)state * 200.0);
}