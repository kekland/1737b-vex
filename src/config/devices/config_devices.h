#pragma once
#ifndef CONFIG_DEVICES_H_
#define CONFIG_DEVICES_H_

#include "main.h"

extern okapi::Controller* masterController;
extern okapi::Controller* partnerController;

void configure_devices();

#endif