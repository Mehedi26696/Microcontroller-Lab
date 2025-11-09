#include <Arduino.h>

const int potPin = 34;  // Use GPIO34 (ADC1_CH6) for analog input

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud
}

void loop() {
  int val = analogRead(potPin);  // Read analog value (0–4095 range)
  Serial.println(val);           // Print to Serial Plotter
  delay(100);                    // Small delay for stable reading
}
