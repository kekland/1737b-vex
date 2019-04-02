#ifndef INTAKE_H_
#define INTAKE_H_

enum IntakeDirection
{
  up = 1,
  stop = 0,
  down = -1,
};

extern void controlIntake(IntakeDirection direction);

#endif