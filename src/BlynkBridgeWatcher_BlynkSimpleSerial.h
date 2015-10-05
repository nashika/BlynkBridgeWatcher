#ifndef BlynkBridgeWatcher_BlynkSimpleSerial_h
#define BlynkBridgeWatcher_BlynkSimpleSerial_h

#include <Adapters/BlynkSerial.h>

#if defined(__SAMD21G18A__)
  // For Arduino Zero (M0)
  extern BLYNK_TYPE BlynkSerial<BlynkTransportSerialChecked<Uart> > Blynk;
#elif defined(__SAM3X8E__)
  // For Arduino Due
  extern BlynkSerial<BlynkTransportSerialChecked<UARTClass> > Blynk;
#elif defined(USBCON)
  // For versions with hw USB, like Micro
  extern BlynkSerial<BlynkTransportSerialChecked<Serial_> > Blynk;
#else
  // For versions with UART
  extern BlynkSerial<BlynkTransportSerial<HardwareSerial> > Blynk;
#endif

#include <BlynkWidgets.h>

#endif
