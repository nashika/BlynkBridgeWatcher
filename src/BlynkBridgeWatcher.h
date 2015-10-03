#ifndef BlynkBridgeWatcher_h
#define BlynkBridgeWatcher_h

#include <SoftwareSerial.h>
#include <BlynkSimpleSerial.h>

class BlynkBridgeWatcher {
public:
  BlynkBridgeWatcher(int vPin, const char* name);
  void setAuthToken(const char* token);
  void send(const char* command, int argument);
  void send(const char* command, const char* argument);
private:
  WidgetBridge _bridge;
  const char* _name;
};

#endif
