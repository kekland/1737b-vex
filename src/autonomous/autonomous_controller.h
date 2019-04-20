#pragma once
#ifndef AUTONOMOUS_CONTROLLER_H_
#define AUTONOMOUS_CONTROLLER_H_

#include "main.h"
#include "../components/vision/vision_driving.h"

using namespace okapi;

void stop();

void drive(QLength cm);
void driveIndependent(QLength leftLength, QLength rightLength);
void turn(QAngle targetDegrees, double turnMultiplier = 1);
void driveWithLeft(QLength length);
void driveWithRight(QLength length);


void shootOnce(void *param);
void shootTwice(void *param);
void getBallUntilBallIsInIntake(void *param);
void releaseBallUntilBallIsInIntake(void *param);

#endif