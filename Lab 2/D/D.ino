/*
---------------------------------------------------------------
Part D: Debugging ISR — Bad Practices Demonstration
Board: Arduino Uno / Mega
---------------------------------------------------------------
*/

const int BUTTON_PIN = 2;
const int LED_PIN = 13;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Debugging ISR: Observe Serial blocking behavior...");

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), badISR, FALLING);
}

void badISR() {
  // ❌ BAD PRACTICE: Long operations in ISR
  Serial.println("Button pressed! (This may cause issues)");
  delay(500);  // ❌ Blocks other interrupts
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void loop() {
  // Observe LED and Serial behavior when pressing button
  Serial.println("Main loop running...");
  delay(1000);
}
