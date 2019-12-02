// This is similar to 04-blinky4, but just uses a sequence of bits to represent the pattern.

#define PERIOD 4000
#define SLOTS 32
#define LED 1
// This pattern below plays out in reverse order, and is basically "SMS" in morse code:
//                ////DotDotDotDaashDaashDotDotDot   
#define PATTERN 0b00000010010010011100111001001001UL

void setup() {
    pinMode(LED, OUTPUT);
}

void loop() {
    static unsigned long start = millis();
    unsigned long slot = ((millis()-start)/(PERIOD/SLOTS)) % SLOTS;
    digitalWrite(LED, ((PATTERN >> slot) & 1) ? HIGH : LOW);
}
