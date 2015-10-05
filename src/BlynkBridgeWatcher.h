#ifndef BlynkBridgeWatcher_h
#define BlynkBridgeWatcher_h

#include "BlynkBridgeWatcher_BlynkSimpleSerial.h"

class BlynkBridgeWatcher {
public:
  BlynkBridgeWatcher(int vPin, const char* name);
  void connect(const char* token);
  void recv(const char* command);
  void send(const char* command, int argument);
  void send(const char* command, const char* argument);
private:
  static const int MAX_LENGTH = 32;
  WidgetBridge _bridge;
  const char* _name;
};

#endif
