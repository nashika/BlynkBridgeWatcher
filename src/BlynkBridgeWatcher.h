#ifndef BlynkBridgeWatcher_h
#define BlynkBridgeWatcher_h

class BlynkBridgeWatcher {
public:
  BlynkBridgeWatcher(const char* name);
  char* pong();
  char* message(const char* command, int argument);
  char* message(const char* command, const char* argument);
private:
  static const int MAX_LENGTH = 32;
  const char* _name;
};

#endif
