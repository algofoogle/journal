#include <DigiCDC.h>

#define PREP(pin) pinMode(pin, OUTPUT); digitalWrite(pin, 0);

void setup() {
  SerialUSB.begin();
  // Configure pins for output. Note that we can't use pins 3 and 4 because they're used for USB:
  PREP(0);
  PREP(1);
  PREP(2);
  PREP(5);
}

void loop() {
  uint8_t cmd;
  if (SerialUSB.available()) {
    cmd = SerialUSB.read();
    // Bits 6 and 5 define what we want to do:
    switch (cmd & 0b01100000 >> 5) {
      case 0:
        // Toggle pins for which their corresponding bit is set.
        break;
      case 1:
        // Set the explicit state of pins using their corresponding bits:
        // Valid characters: (space) and !"#$%&'01234567
        break;
      case 2:
        // Turn on pins that have their corresponding bit set.
        // Valid characters: ABCDEFGHPQRSTUVW (i.e. 0100_0000..0100_0111 and 0101_0000..0101_0111).
        break;
      case 3:
        // Turn off pins that have their corresponding bit set.
        // Valid characters: abcdefghpqrstuvw
        break;
    }
    //TODO: Respond with bit 5 set, and the current state of all pins in bits 4..0
    //NOTE: It's possible to just read the status of all pins by sending 'A' or 'a' (i.e. don't change anything).
  }
}