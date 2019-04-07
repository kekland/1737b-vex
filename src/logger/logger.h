#ifndef LOGGER_H_
#define LOGGER_H_

#include "main.h"

enum class LogLevel {
  info = 1,
  warn = 2,
  error = 3,
};

void log(string message, string context = "");
void warn(string message, string context = "");
void error(string message, string context = "");

#endif