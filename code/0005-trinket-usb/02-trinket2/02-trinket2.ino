#include <TrinketKeyboard.h>

#define LED 1
#define LED_DIM     10
#define LED_BRIGHT  255

#define TK TrinketKeyboard

#define ULONG unsigned long

uint8_t gLedState;

void TKDelay(ULONG ms) {
  ULONG start = millis();
  while ( (millis()-start) < ms ) TK.poll();
}

void setup() {
  pinMode(LED, OUTPUT);
  analogWrite(LED, LED_DIM);
  TK.begin();
  TKDelay(1000);
  TK.poll();
  TK.pressKey(KEYCODE_MOD_LEFT_SHIFT, 0);
  TK.pressKey(0, 0);
  gLedState = TK.getLEDstate();
  TK.print(F("Hello, World! I will try to monitor your keyboard LEDs. Initial state: "));
  TK.println((int)gLedState);
}

void loop() {
  uint8_t new_led_state = TK.getLEDstate();
  if (new_led_state != gLedState) {
    gLedState = new_led_state;
    TK.print(F("LED state changed: "));
    TK.println((int)gLedState);
  }
}

