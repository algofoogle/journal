#include <TrinketKeyboard.h>

#define LED 1
#define LED_DIM     10
#define LED_BRIGHT  255

unsigned long start;

void setup() {
  start = millis();
  pinMode(LED, OUTPUT);
  analogWrite(LED, LED_DIM); // Really DIM LED.
  TrinketKeyboard.begin();
}

// This waits for the specified amount of time while keeping our USB keyboard
// connection alive with regular polling:
void polledDelay(unsigned long ms) {
  unsigned long start = millis();
  while ( (millis()-start) < ms ) TrinketKeyboard.poll();
}

void loop() {
  unsigned long step1 = millis();
  static int count = 1;
  // Every 10ms, must poll at least once or trigger at least one keystroke:
  TrinketKeyboard.poll();
  unsigned long step2 = millis();
  // Dummy messages to wake things up:
  TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_SHIFT, 0);
  polledDelay(100);
  TrinketKeyboard.pressKey(0,0);
  polledDelay(100);
  TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_SHIFT, 0);
  polledDelay(100);
  TrinketKeyboard.pressKey(0,0);
  // Make LED full brightness:
  analogWrite(LED, LED_BRIGHT);
  // Now do some keyboard stuff:
  TrinketKeyboard.typeChar('#');
  TrinketKeyboard.print(count++);
  TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_SHIFT, KEYCODE_A);
  TrinketKeyboard.pressKey(0,0);
  TrinketKeyboard.print(F("This is a test. Time="));
  TrinketKeyboard.print(step1);
  TrinketKeyboard.print(F(".."));
  TrinketKeyboard.print(step2);
  TrinketKeyboard.print(F(" start="));
  TrinketKeyboard.print(start);
  TrinketKeyboard.print(F(" isConnected="));
  TrinketKeyboard.println((int)(TrinketKeyboard.isConnected()));
  // ...and we're done:
  analogWrite(LED, LED_DIM);
  // Wait 2 seconds:
  polledDelay(2000);
}
