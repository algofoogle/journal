#include "DigiKeyboard.h"

#define LED 1

#define KB DigiKeyboard // Shorthand.

#define KEY_ESC       0x29
#define KEY_TAB       0x2b
#define KEY_CAPSLOCK  0x39
#define KEY_PRTSC     0x46  // Print Screen key.

void setup() {
  // DigiKeyboard requires no setup.
  // Prep LED for status updates, though:
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  static int counter = 1;
  // Recommended to help older systems avoid missing the first character after a delay:
  KB.sendKeyStroke(0);
  // Type out the counter:
  KB.print(counter++);
  // Hit TAB key twice:
  KB.sendKeyStroke(KEY_TAB);
  KB.sendKeyStroke(KEY_TAB);
  // Type out a message using keystrokes:
  KB.println(F("Hello, world! This is a DigiSpark USB keyboard device talking to you."));
  // Toggle CAPS LOCK:
  KB.sendKeyStroke(KEY_CAPSLOCK);
  KB.println(F("Hi There!"));
  // Delay until we do it all over again. We use KB.delay() to ensure it keeps USB comms fresh.
  KB.delay(1000);
  // Toggle LED state:
  digitalWrite(LED, !digitalRead(LED));
}
