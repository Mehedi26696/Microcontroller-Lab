/*
---------------------------------------------------------------
Part B: External Interrupt (Button-controlled LED)
Board: Arduino Uno / Mega
---------------------------------------------------------------
*/

const int BUTTON_PIN = 2;  // Interrupt pin
const int LED_PIN = 13;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Internal pull-up resistor
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("External Interrupt Example...");

  // Trigger ISR on falling edge (button press)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggleLED, FALLING);
}

void toggleLED() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED
  // ⚠ Keep ISR short — no delay() or Serial.print()
}

void loop() {
  // Main loop remains free
  Serial.println("Main loop doing background work...");
  delay(1000);
}
