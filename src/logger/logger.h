#pragma once
#ifndef LOGGER_H_
#define LOGGER_H_

#include "main.h"

enum class LogLevel {
  info = 1,
  warn = 2,
  error = 3,
};

void info(std::string message, std::string context = "");
void warn(std::string message, std::string context = "");
void error(std::string message, std::string context = "");

#endif