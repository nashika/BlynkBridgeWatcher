#ifndef BlynkBridgeWatcher_h
#define BlynkBridgeWatcher_h

#include <string.h>
#include <stdlib.h>

#include <BlynkWidgets.h>

class BlynkBridgeWatcher {
public:
  BlynkBridgeWatcher(int vPin, const char* token) : _bridge(vPin) {
    _token = token;
    _timeout = 60000;
    _lasttime = 0;
  }

  void recv(const char* input) {
    char* buff = new char[strlen(input) + 1];
    strcpy(buff, input);
    char* msg = new char[MAX_LENGTH];
    char *callbackKey, *command, *pin, *param;
    callbackKey = strtok(buff, ",");
    command = strtok(NULL, ",");
    pin = strtok(NULL, ",");
    param = strtok(NULL, ",");
    if (strcmp(command, "pi") == 0) {
      snprintf(msg, MAX_LENGTH, "%s", callbackKey);
    } else if (strcmp(command, "dr") == 0) {
      snprintf(msg, MAX_LENGTH, "%s,%d", callbackKey, digitalRead(atoi(pin)));
    } else if (strcmp(command, "ar") == 0) {
      snprintf(msg, MAX_LENGTH, "%s,%d", callbackKey, analogRead(atoi(pin)));
    } else if (strcmp(command, "vr") == 0) {
      //snprintf(msg, MAX_LENGTH, "%s,%d", callbackKey, Blynk.virtualRead(atoi(pin)));
      snprintf(msg, MAX_LENGTH, "%s", callbackKey);
    } else if (strcmp(command, "dw") == 0) {
      digitalWrite(atoi(pin), atoi(param));
      snprintf(msg, MAX_LENGTH, "%s", callbackKey);
    } else if (strcmp(command, "aw") == 0) {
      analogWrite(atoi(pin), atoi(param));
      snprintf(msg, MAX_LENGTH, "%s", callbackKey);
    } else if (strcmp(command, "vw") == 0) {
      Blynk.virtualWrite(atoi(pin), atoi(param));
      snprintf(msg, MAX_LENGTH, "%s", callbackKey);
    } else if (strcmp(command, "co") == 0) {
      snprintf(msg, MAX_LENGTH, "%s", callbackKey);
    } else if (strcmp(command, "pm") == 0) {
      int mode = atoi(param);
      snprintf(msg, MAX_LENGTH, "%s", callbackKey);
      if (mode == 0 || mode == 3) {
        pinMode(atoi(pin), INPUT);
      } else if (mode == 1) {
        pinMode(atoi(pin), OUTPUT);
      } else if (mode == 2 || mode == 4) {
        pinMode(atoi(pin), INPUT_PULLUP);
      } else {
        snprintf(msg, MAX_LENGTH, "%s,%s,%s", callbackKey, "er", "INVALID PIN MODE");
      }
    } else {
      snprintf(msg, MAX_LENGTH, "%s,%s,%s", callbackKey, "er", "INVALID COMMAND");
    }
    _bridge.virtualWrite(0, msg);
    delete [] buff;
    delete [] msg;
  }

  void send(const char* id) {
    char* msg = new char[MAX_LENGTH];
    snprintf(msg, MAX_LENGTH, "%s", id);
    _bridge.virtualWrite(0, msg);
    delete [] msg;
  }

  void send(const char* id, int value) {
    char* msg = new char[MAX_LENGTH];
    snprintf(msg, MAX_LENGTH, "%s,%d", id, value);
    _bridge.virtualWrite(0, msg);
    delete [] msg;
  }

  void send(const char* id, const char* arg) {
    char* msg = new char[MAX_LENGTH];
    snprintf(msg, MAX_LENGTH, "%s,%s", id, arg);
    _bridge.virtualWrite(0, msg);
    delete [] msg;
  }

  void send(const char* id, const char* arg, const int value) {
    char* msg = new char[MAX_LENGTH];
    snprintf(msg, MAX_LENGTH, "%s,%s,%d", id, arg, value);
    _bridge.virtualWrite(0, msg);
    delete [] msg;
  }

  void run() {
    if (_lasttime == 0 || millis() - _lasttime > _timeout) {
      _bridge.setAuthToken(_token);
      _lasttime = millis();
    }
  }

private:
  static const int MAX_LENGTH = 32;
  WidgetBridge _bridge;
  const char* _token;
  uint32_t _timeout;
  unsigned long _lasttime;
};

#endif
