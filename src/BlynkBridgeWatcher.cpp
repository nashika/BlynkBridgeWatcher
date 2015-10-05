#include <Arduino.h>
#include "BlynkBridgeWatcher.h"

BlynkBridgeWatcher::BlynkBridgeWatcher(int vPin, const char* name) : _bridge(vPin) {
  _name = name;
}

void BlynkBridgeWatcher::connect(const char* token) {
  while (Blynk.connect() == false) {}
  _bridge.setAuthToken(token);
}

void BlynkBridgeWatcher::recv(const char* command) {
  while (Blynk.connect() == false) {}
  char* msg = new char[MAX_LENGTH];
  snprintf(msg, MAX_LENGTH, "%s,$pong", _name);
  _bridge.virtualWrite(0, msg);
}

void BlynkBridgeWatcher::send(const char* command, int argument) {
  char* msg = new char[MAX_LENGTH];
  snprintf(msg, MAX_LENGTH, "%d", argument);
  send(command, msg);
}

void BlynkBridgeWatcher::send(const char* command, const char* argument) {
  char* msg = new char[MAX_LENGTH];
  snprintf(msg, MAX_LENGTH, "%s,%s,%s", _name, command, argument);
  _bridge.virtualWrite(0, msg);
}
