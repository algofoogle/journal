// This uses quite a different approach from 01-blinky and 02-blinky:
// It checks system time (in milliseconds) to see whether a state change is due.
// This just demonstrates a concept, but it might be useful to ensure that
// certain events happen on a very precise schedule, without inherent drift,
// by measuring the clock rather than just padding out time.
// This time we use a frequency of 0.5Hz, but derived differently.
#define PERIOD    2000
#define INV_DUTY  5     // 1/5 => 20% duty cycle.
#define LED       1

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  // Declared static, so it persists between iterations:
  static unsigned long start = millis();
  // NOTE: millis() can wrap around after 2^32 milliseconds (~49.7 days),
  // but hopefully the maths will still work out correctly...?
  if (((millis() - start) / (PERIOD/INV_DUTY)) % INV_DUTY) {
    digitalWrite(LED, LOW);
  }
  else {
    digitalWrite(LED, HIGH);
  }
}
