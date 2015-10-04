#include <Arduino.h>
#include "BlynkBridgeWatcher.h"

BlynkBridgeWatcher::BlynkBridgeWatcher(const char* name) {
  _name = name;
}

char* BlynkBridgeWatcher::pong() {
  char* msg = new char[MAX_LENGTH];
  snprintf(msg, MAX_LENGTH, "%s,$pong", _name);
  return msg;
}

char* BlynkBridgeWatcher::message(const char* command, int argument) {
  char* msg = new char[MAX_LENGTH];
  snprintf(msg, MAX_LENGTH, "%d", argument);
  message(command, msg);
}

char* BlynkBridgeWatcher::message(const char* command, const char* argument) {
  char* msg = new char[MAX_LENGTH];
  snprintf(msg, MAX_LENGTH, "%s,%s,%s", _name, command, argument);
  return msg;
}
