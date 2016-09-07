#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleStream.h>
#include <BlynkBridgeWatcher.h>

#define TOKEN "this board token"
#define WATCHER_TOKEN "watcher board token"

BlynkBridgeWatcher blynkBridgeWatcher(V1, WATCHER_TOKEN);

void setup() {
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  Serial.begin(9600);
  Blynk.begin(TOKEN, Serial);
}

BLYNK_WRITE(V0) {
  blynkBridgeWatcher.recv(param.asStr());
}

BLYNK_WRITE(V10) {
  blynkBridgeWatcher.send("_id_", param.asInt());
}

void loop() {
  Blynk.run();
  blynkBridgeWatcher.run();
}

