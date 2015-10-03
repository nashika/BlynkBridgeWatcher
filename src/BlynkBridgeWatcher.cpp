#include <Arduino.h>
#include "BlynkBridgeWatcher.h"

BlynkBridgeWatcher::BlynkBridgeWatcher(int vPin, const char* name) {
  _bridge = new WidgetBridge(vPin);
  _name = name;
}

BlynkBridgeWatcher::setAuthToken(const char* token) {
  while (Blynk.connect() == false) {}
  _bridge.setAuthToken(BRIDGE_WATHER_TOKEN);
}

BlynkBridgeWatcher::send(const char* command, int argument) {
  char *msg = "";
  sprintf(msg, "%d", argument);
  send(command, msg);
}


BlynkBridgeWatcher::send(const char* command, const char* argument) {
  char *msg = "";
  sprintf(msg, "%d,%d,%d", _name, command, argument);
  _bridge.virtualWrite(0, msg);
}
