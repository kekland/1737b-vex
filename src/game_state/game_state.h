#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "main.h"

class GameState {
  public:
    int getTimeFromGameStartMillis();
    double getTimeFromGameStartSeconds();

    void autonStarted();
    void driverStarted();
    
    void setAlliance(Alliance alliance);
    void setAutonomous(int index);

    Alliance getAlliance();
    Flag getOpposingFlag();

  protected:
    Alliance selectedAlliance = Alliance::none;
    int selectedAutonomous = -1;
    int timeAutonStarted = -1;
    int timeDriverStarted = -1;
    bool isAuton = false;
    bool isDriver = false;
};

extern GameState gameState;
#endif