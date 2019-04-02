#ifndef SHOOTER_H_
#define SHOOTER_H_

enum ShooterState
{
  shoot = 1,
  stop = 0,
};

void controlShooter(ShooterState state);

#endif