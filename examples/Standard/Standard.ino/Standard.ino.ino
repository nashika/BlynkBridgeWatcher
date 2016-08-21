/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example shows how to use ordinary Arduino Serial
 * to connect your project to Blynk.
 * Feel free to apply it to any other example. It's simple!
 *
 **************************************************************
 *            USB HOWTO: http://tiny.cc/BlynkUSB
 **************************************************************/

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleStream.h>
#include <BlynkBridgeWatcher.h>

#define TOKEN "8425d9b6c9b145d6839c7573ffae91ca"
#define BRIDGE_WATCHER_TOKEN "50fb6cded51e462191e9109df8aa7bd8"

#define LED_PIN 13
#define BUTTON_PIN A0
#define BRIDGE_VPIN V1

#define BRIGE_NAME "BR01"

BlynkBridgeWatcher blynkBridgeWatcher(BRIDGE_VPIN, BRIGE_NAME);

void setup() {
  // Debug console
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  Serial.begin(9600);
  Blynk.begin(TOKEN, Serial);
  blynkBridgeWatcher.connect(BRIDGE_WATCHER_TOKEN);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

BLYNK_WRITE(V0) {
  blynkBridgeWatcher.recv(param.asStr());
}

BLYNK_READ(V2) {
  Blynk.virtualWrite(V2, digitalRead(2));
}

void loop() {
  Blynk.run();
}

