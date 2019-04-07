#include "main.h"
#include <sstream>
using namespace std;

void _start(LogLevel level, string context = "") {
  string color = "37";
  string bold = "0";
  if(level == LogLevel::warn) {
    color = "33";
  }
  else if(level == LogLevel::error) {
    color = "31";
    bold = "1";
  }

  int currentTime = pros::millis();

  printf("%dms\033[%s;%sm [%s] ", currentTime, bold, color, context);
}

void _end() {
  printf("\033[0m\n");
}

void info(string message, string context = "") {
  _start(LogLevel::info, context);
  printf(message.c_str());
  _end();
}

void warn(string message, string context = "") {
  _start(LogLevel::warn, context);
  printf(message.c_str());
  _end();
}
void error(string message, string context = "") {
  _start(LogLevel::error, context);
  printf(message.c_str());
  _end();
}