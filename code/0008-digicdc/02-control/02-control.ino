#include <DigiCDC.h>

#define PREP(pin) pinMode(pin, OUTPUT); digitalWrite(pin, 0);

void setup() {
  SerialUSB.begin();
  // Configure pins for output. Note that we can't use pins 3 and 4 because they're used for USB,
  // and we choose not to use pin 5 in order to keep the protocol simple:
  PREP(0);
  PREP(1);
  PREP(2);
}

void loop() {
  uint8_t cmd;
  uint8_t pins;
  uint8_t state;
  int i;
  if (SerialUSB.available()) {
    cmd = SerialUSB.read();
    pins = cmd & 0b111;
    cmd >>= 5;
    state = 0;
    for (i=0; i<3; ++i, pins>>=1) {
      switch (cmd) {
        case 0:
          // Toggle pins for which their corresponding bit is set.
          digitalWrite(i, !digitalRead(i));
          break;
        case 1:
          // Set the explicit state of pins using their corresponding bits:
          // Valid characters: (space) and !"#$%&'
          // (space)  Turn off all
          // !        Turn on P0
          // "        Turn on P1
          // $        Turn on P2
          digitalWrite(i, (pins&1) ? HIGH : LOW);
          break;
        case 2:
          // Turn on pins that have their corresponding bit set.
          // Valid characters: @ABCDEFG (i.e. 0100_0000..0100_0111).
          if (pins&1) digitalWrite(i, HIGH);
          break;
        case 3:
          // Turn off pins that have their corresponding bit set.
          // Valid characters: `abcdefg
          if (pins&1) digitalWrite(i, LOW);
          break;
      }
      state |= (digitalRead(i) ? 1 : 0) << i;
    }
    // Respond with bit 5 set, and the current state of all pins in bits 2..0:
    state |= 0b100000;
    SerialUSB.write(state);
    //NOTE: It's possible to just read the status of all pins by sending @ or ` (i.e. don't change anything).
  }
}
