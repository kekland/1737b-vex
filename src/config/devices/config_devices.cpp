#include "main.h"

okapi::Controller* masterController;
okapi::Controller* partnerController;

void configure_devices() {
  info("Starting configuration", "config_devices");

  masterController = new okapi::Controller();
  partnerController = new okapi::Controller(okapi::ControllerId::partner);

  info("Finished configuration", "config_devices");
}