#pragma once
#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "main.h"

class GameState {
  public:
    GameState();
    int getTimeFromGameStartMillis();
    double getTimeFromGameStartSeconds();

    void autonStarted();
    void driverStarted();
    
    void setAlliance(Alliance alliance);
    void setAutonomous(int index);

    Alliance getAlliance();
    Flag getOpposingFlag();

    int getAutonomous();

  protected:
    Alliance selectedAlliance;
    int selectedAutonomous;
    int timeAutonStarted;
    int timeDriverStarted;
    bool isAuton;
    bool isDriver;
};

extern GameState* gameState;
#endif