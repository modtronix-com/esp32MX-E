/*
  Blink
*/
//#include <Arduino.h>

// LED on the MX1 board
static const uint8_t LED = 0;

// Button on the MX1 board
static const uint8_t USER_BTN = 34;

// Pin used to reset Phy
#define PHY_RESET 23

// Pin used to enable external oscillator
#define PHY_OSC_ENABLE 4

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);

  // initialize user Button
  pinMode(USER_BTN, INPUT);

  // initialize serial communication
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {

  if (digitalRead(USER_BTN) == 0) {
    Serial.println('x');
    
    digitalWrite(LED, HIGH);    // Turn the LED on (HIGH is the voltage level)

    delay(50);                 // Wait for a second

    digitalWrite(LED, LOW);     // Turn the LED off by making the voltage LOW
    delay(50);                 // Wait for a second
  }
}
