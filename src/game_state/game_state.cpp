#include "main.h"

void GameState::autonStarted()
{
  isAuton = true;
  isDriver = false;
  timeAutonStarted = pros::millis();
}

void GameState::driverStarted()
{
  isAuton = false;
  isDriver = true;
  timeDriverStarted = pros::millis();
}

Alliance GameState::getAlliance()
{
  return selectedAlliance;
}

Flag GameState::getOpposingFlag()
{
  if (getAlliance() == Alliance::none)
  {
    return Flag::none;
  }

  if (getAlliance() == Alliance::red)
  {
    return Flag::blue;
  }

  if (getAlliance() == Alliance::blue)
  {
    return Flag::red;
  }
}

int GameState::getTimeFromGameStartMillis() {
  if(isAuton) {
    return pros::millis() - timeAutonStarted;
  }
  else if(isDriver) {
    return pros::millis() - timeDriverStarted;
  }
  return 0;
}

double GameState::getTimeFromGameStartSeconds() {
  return (double)getTimeFromGameStartMillis() / 1000.0;
}

void GameState::setAlliance(Alliance alliance) {
  selectedAlliance = alliance;
}

void GameState::setAutonomous(int selection) {
  selectedAutonomous = selection;
}

GameState gameState = GameState();