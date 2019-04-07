#include "main.h"
#include "autonomous_variants.h"
#include "../autonomous/autonomous_controller.h"

using namespace okapi;

void autonomousFront1() {
  Alliance alliance = gameState.getAlliance();
  Flag opposingFlag = gameState.getOpposingFlag();

  double turnMultiplier = (alliance == Alliance::red)? 1.0 : -1.0;

  drive(100.0_cm);
  turn(90.0_deg, turnMultiplier);
}