int ledPin = 2; // Built-in LED for most ESP32 boards

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH); // LED ON
  delay(1000);                 // Wait 1 sec
  digitalWrite(ledPin, LOW);  // LED OFF
  delay(1000);                 // Wait 1 sec
}

