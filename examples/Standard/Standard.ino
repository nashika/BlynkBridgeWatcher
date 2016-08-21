#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleStream.h>
#include <BlynkBridgeWatcher.h>

#define TOKEN "this board token"
#define WATCHER_TOKEN "watcher board token"

#define BRIDGE_INPUT_VPIN V0
#define BRIDGE_OUTPUT_VPIN V1
#define BRIGE_NAME "BR01"

BlynkBridgeWatcher blynkBridgeWatcher(BRIDGE_OUTPUT_VPIN, BRIGE_NAME);

void setup() {
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  Serial.begin(9600);
  Blynk.begin(TOKEN, Serial);
  blynkBridgeWatcher.connect(WATCHER_TOKEN);
}

BLYNK_WRITE(BRIDGE_INPUT_VPIN) {
  blynkBridgeWatcher.recv(param.asStr());
}

void loop() {
  Blynk.run();
}
