#include "main.h"
#include "autonomous_variants.h"
#include "../autonomous/autonomous_controller.h"

void autonomousFront1() {
  Alliance alliance = gameState.getAlliance();
  Flag opposingFlag = gameState.getOpposingFlag();

  drive(100.0);
  
}