// Example sketch for Digispark to blink onboard LED at 1Hz.
#define PERIOD  1000    // A period of 1000ms means 1Hz. 500ms is hence needed per delay.
#define LED     1       // LED is pin 1 for Digispark Model A or Pro. Pin 0 for Model B.

// setup() runs before entering loop(), i.e. after bootloader exits, following power-on or reset.
void setup() {
  // Make sure LED pin is configured for output:
  pinMode(LED, OUTPUT);
}

// loop() runs on endless repeat after setup():
void loop() {
  digitalWrite(LED, HIGH);  // Turn LED on.
  delay(PERIOD/2);          // Wait for half of our period.
  digitalWrite(LED, LOW);   // Turn LED off.
  delay(PERIOD/2);          // Wait for the other half of our period.
  // ...and then we'll loop back to the start.
}
