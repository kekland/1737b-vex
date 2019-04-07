#include "main.h"
#include <sstream>
using namespace std;

void _log(LogLevel level, string message, string context = "")
{
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

  printf("%dms\033[%s;%sm [%s] %s\033[0m\n", currentTime, bold, color, context, message);
}

void log(string message, string context = "") {
  _log(LogLevel::info, message, context);
}
void warn(string message, string context = "") {
  _log(LogLevel::warn, message, context);
}
void error(string message, string context = "") {
  _log(LogLevel::error, message, context);
}