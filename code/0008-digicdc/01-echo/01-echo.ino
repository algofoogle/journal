#include <DigiCDC.h>

#define LED 1

void setup() {
  SerialUSB.begin();
  pinMode(LED, OUTPUT);
}

void loop() {
  uint8_t data;
  if (SerialUSB.available()) {
    // There is at least one byte available, so read it and write it back out:
    data = SerialUSB.read();
    SerialUSB.write(data);
    // Also toggle the LED to show we're alive:
    digitalWrite(LED, !digitalRead(LED));
  }
}
