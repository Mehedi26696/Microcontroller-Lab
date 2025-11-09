/*
---------------------------------------------------------------
Part A: LED Blinking using Timer Interrupt (1 Hz)
Board: Arduino Uno / Mega
Library: TimerOne.h
---------------------------------------------------------------
*/

#include <TimerOne.h>

const int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Timer interrupt blinking started...");

  // Initialize Timer1 to overflow every 1 second (1,000,000 µs)
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(toggleLED);  // Attach ISR
}

void toggleLED() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED state
  // ⚠ Avoid Serial.print() or delay() inside ISR
}

void loop() {
  // The LED keeps blinking independently of main loop
  Serial.println("Main loop running...");
  delay(1000);
}






