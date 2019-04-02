#ifndef INTAKE_H_
#define INTAKE_H_

enum IntakeDirection
{
  up = 1,
  down = -1,
};

extern void control(IntakeDirection direction);

#endif