#ifndef BlynkBridgeWatcher_h
#define BlynkBridgeWatcher_h

#include <string.h>
#include <stdlib.h>

#include <BlynkWidgets.h>

class BlynkBridgeWatcher {
public:
	BlynkBridgeWatcher(int vPin, const char* name) : _bridge(vPin) {
		_name = name;
	}
	
	void connect(const char* token) {
		while (Blynk.connect() == false) {}
		_bridge.setAuthToken(token);
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
		if (strcmp(command, "st") == 0) {
		snprintf(msg, MAX_LENGTH, "%s,$r,%s", _name, callbackKey);
		} else if (strcmp(command, "pi") == 0) {
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
		delete [] buff;
		delete [] msg;
	}
	
	void send(const char* command) {
		char* msg = new char[MAX_LENGTH];
		snprintf(msg, MAX_LENGTH, "%s,%s", _name, command);
		_bridge.virtualWrite(0, msg);
		delete [] msg;
	}
	
	void send(const char* command, int argument) {
		char* msg = new char[MAX_LENGTH];
		snprintf(msg, MAX_LENGTH, "%s,%s,%d", _name, command, argument);
		_bridge.virtualWrite(0, msg);
		delete [] msg;
	}
	
	void send(const char* command, const char* argument) {
		char* msg = new char[MAX_LENGTH];
		snprintf(msg, MAX_LENGTH, "%s,%s,%s", _name, command, argument);
		_bridge.virtualWrite(0, msg);
		delete [] msg;
	}
	
private:
	static const int MAX_LENGTH = 32;
	WidgetBridge _bridge;
	const char* _name;
};

#endif
