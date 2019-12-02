// This is very similar to 03-blinky3, but it uses a switch statement
// to create different LED flash patterns.
#define PERIOD 2000
#define SLOTS 10
#define LED 1
#define led(state) digitalWrite(LED, state)

void setup() {
    pinMode(LED, OUTPUT);
    led(LOW);
}

void loop() {
    static unsigned long start = millis();
    switch ( ((millis()-start)/(PERIOD/SLOTS)) % SLOTS ) {
        case 0: led(HIGH);  break;
        case 1: led(LOW);   break;
        case 2: led(HIGH);  break;
        case 3: led(LOW);   break;
        //   4
        //   5
        case 6: led(HIGH);  break;
        case 7: led(LOW);   break;
        //   8
        //   9 
    } 
}
