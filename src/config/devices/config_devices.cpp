#include "main.h"

okapi::Controller* masterController;

void configure_devices() {
  info("Starting configuration", "config_devices");

  masterController = new okapi::Controller();

  info("Finished configuration", "config_devices");
}