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
  char* command, *param1, *param2, *param3;
  command = strtok(buff, ",");
  param1 = strtok(NULL, ",");
  param2 = strtok(NULL, ",");
  param3 = strtok(NULL, ",");
  if (strcmp(command, "pi") == 0) {
    snprintf(msg, MAX_LENGTH, "%s,$r,%s", _name, param2);
  } else if (strcmp(command, "dr") == 0) {
    snprintf(msg, MAX_LENGTH, "%s,$r,%s,%d", _name, param2, digitalRead(atoi(param1)));
  } else if (strcmp(command, "ar") == 0) {
    snprintf(msg, MAX_LENGTH, "%s,$r,%s,%d", _name, param2, analogRead(atoi(param1)));
  } else if (strcmp(command, "vr") == 0) {
    //snprintf(msg, MAX_LENGTH, "%s,$r,%s,%d", _name, param2, Blynk.virtualRead(atoi(param1)));
    snprintf(msg, MAX_LENGTH, "%s,$r,%s", _name, param2);
  } else if (strcmp(command, "dw") == 0) {
    digitalWrite(atoi(param1), atoi(param3));
    snprintf(msg, MAX_LENGTH, "%s,$r,%s,1", _name, param2);
  } else if (strcmp(command, "aw") == 0) {
    analogWrite(atoi(param1), atoi(param3));
    snprintf(msg, MAX_LENGTH, "%s,$r,%s,1", _name, param2);
  } else if (strcmp(command, "vw") == 0) {
    Blynk.virtualWrite(atoi(param1), atoi(param3));
    snprintf(msg, MAX_LENGTH, "%s,$r,%s,1", _name, param2);
  } else {
    snprintf(msg, MAX_LENGTH, "%s,$r,%s",-1, _name, param2);
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
