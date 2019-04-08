#pragma once
#ifndef LOGGER_H_
#define LOGGER_H_

#include "main.h"
enum class LogLevel {
  info = 1,
  warn = 2,
  error = 3,
};

void info(const std::string& message, const std::string& context = "");
void warn(const std::string& message, const std::string& context = "");
void error(const std::string& message, const std::string& context = "");

#endif