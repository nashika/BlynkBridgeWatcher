#include <Arduino.h>
#include "BlynkBridgeWatcher.h"

BlynkBridgeWatcher::BlynkBridgeWatcher(int vPin, const char* name) : _bridge(vPin) {
  _name = name;
}

void BlynkBridgeWatcher::connect(const char* token) {
  while (Blynk.connect() == false) {}
  _bridge.setAuthToken(token);
}

void BlynkBridgeWatcher::recv(const char* input) {
  char* buff = (char*)input;
  char* msg = new char[MAX_LENGTH];
  char *callbackKey, *command, *pin, *param;
  callbackKey = strtok(buff, ",");
  command = strtok(NULL, ",");
  pin = strtok(NULL, ",");
  param = strtok(NULL, ",");
  if (strcmp(command, "pi") == 0) {
    snprintf(msg, MAX_LENGTH, "%s,$r,%s", _name, callbackKey);
  } else if (strcmp(command, "dr") == 0) {
    snprintf(msg, MAX_LENGTH, "%s,$r,%s,%d", _name, callbackKey, digitalRead(atoi(pin)));
  } else if (strcmp(command, "ar") == 0) {
    snprintf(msg, MAX_LENGTH, "%s,$r,%s,%d", _name, callbackKey, analogRead(atoi(pin)));
  } else if (strcmp(command, "vr") == 0) {
    //snprintf(msg, MAX_LENGTH, "%s,$r,%s,%d", _name, callbackKey, Blynk.virtualRead(atoi(pin)));
    snprintf(msg, MAX_LENGTH, "%s,$r,%s", _name, callbackKey);
  } else {
    snprintf(msg, MAX_LENGTH, "%s,$r,%s",-1, _name, callbackKey);
  }
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
