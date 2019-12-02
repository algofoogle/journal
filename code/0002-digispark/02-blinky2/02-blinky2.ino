// This differs from 01-blinky in that it toggles the state of the pin on each iteration.
// It runs faster (2Hz) so you can tell it's different from 01-blinky.
#define PERIOD  500
#define LED     1

void setup() {
  pinMode(LED, OUTPUT);
  // Set initial pin state:
  digitalWrite(LED, LOW);
}

void loop() {
  delay(PERIOD/2);
  // Toggle pin state:
  digitalWrite(LED, ~digitalRead(LED));
}
