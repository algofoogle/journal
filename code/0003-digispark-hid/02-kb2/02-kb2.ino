// This example is designed to work with a Mac.
#include "DigiKeyboard.h"

#define LED 1

#define KB DigiKeyboard

#define KEY_EQUAL 0x2e // Keyboard = and +
#define KEY_ESC 0x29 // Keyboard ESCAPE

void setup() {
  pinMode(LED, OUTPUT);
  analogWrite(LED, 100); // Dimly lit LED.
}

void loop() {
  // Make sure the Mac is definitely ready to receive our keys.
  // At least the first line out of the next 4 seems to be required.
  KB.sendKeyStroke(0);
  KB.delay(100);
  KB.sendKeyStroke(0);
  KB.delay(100);
  // Send CMD+Space to open Spotlight Search:
  KB.sendKeyStroke(KEY_SPACE, MOD_GUI_LEFT);
  // Wait a moment...
  KB.delay(500);
  // Find TextEdit.
  KB.print("textedit");
  // Wait another moment for the search to react...
  KB.delay(1000);
  // Hit ENTER, hoping that TextEdit is selected by default.
  KB.sendKeyStroke(KEY_ENTER);
  // Wait a moment for TextEdit to launch...
  while (1) {
    KB.delay(1000);
    // Make LED go bright:
    analogWrite(LED, 255);
    // Type something:
    KB.println("Hello, World! I hope I'm typing into TextEdit...");
    // Increase the font size by doing CMD+Plus a couple times:
    KB.sendKeyStroke(KEY_EQUAL, MOD_GUI_LEFT);
    KB.sendKeyStroke(KEY_EQUAL, MOD_GUI_LEFT);
    // Do something in the Properties window:
    KB.sendKeyStroke(KEY_P, MOD_GUI_LEFT | MOD_ALT_LEFT);
    KB.delay(100);
    KB.print("Anton");
    KB.sendKeyStroke(KEY_ESC);
    // Make LED dim again:
    analogWrite(LED, 100);
  }
}
