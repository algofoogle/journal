#include "DigiKeyboard.h"

#define KB DigiKeyboard
#define LED 1
#define KEY_ESC       0x29
#define KEY_TAB       0x2b
#define KEY_CAPSLOCK  0x39
#define KEY_PRTSC     0x46  // Print Screen key.

void setup() {
    pinMode(LED, OUTPUT);
}

void loop() {
    analogWrite(LED, 50);
    KB.delay(1000);
    KB.sendKeyStroke(0);
    KB.delay(250);
    analogWrite(LED, 255);
    KB.sendKeyStroke(KEY_A);
    KB.sendKeyStroke(KEY_A);
    KB.sendKeyStroke(KEY_A, MOD_SHIFT_LEFT);
    KB.sendKeyStroke(KEY_CAPSLOCK);
    KB.sendKeyStroke(KEY_A);
    KB.sendKeyStroke(KEY_A);
    KB.sendKeyStroke(KEY_A, MOD_SHIFT_LEFT);
    KB.sendKeyStroke(KEY_CAPSLOCK);
    KB.print("Testing held key: ");
    KB.sendKeyPress(KEY_A);
    KB.delay(2000);
    KB.sendKeyPress(KEY_B, MOD_SHIFT_LEFT);
    KB.delay(2000);
    KB.sendKeyPress(0);
    KB.sendKeyStroke(KEY_ENTER);
    KB.println("Done!");
}
