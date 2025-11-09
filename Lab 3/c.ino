#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 4          // Signal pin connected to GPIO4
#define DHTTYPE DHT22     // DHT22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

// Moving Average Filter
const int numReadings = 10;
float tempReadings[numReadings];
float humReadings[numReadings];
int readIndex = 0;
float totalTemp = 0, totalHum = 0;
float avgTemp = 0, avgHum = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  for (int i = 0; i < numReadings; i++) {
    tempReadings[i] = 0;
    humReadings[i] = 0;
  }
}

void loop() {
  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("0 0 0 0");  // output zeros so plotter keeps working
    delay(2000);
    return;
  }

  // Remove oldest and add newest readings
  totalTemp -= tempReadings[readIndex];
  totalHum -= humReadings[readIndex];

  tempReadings[readIndex] = temperatureC;
  humReadings[readIndex] = humidity;

  totalTemp += temperatureC;
  totalHum += humidity;

  readIndex = (readIndex + 1) % numReadings;

  avgTemp = totalTemp / numReadings;
  avgHum = totalHum / numReadings;

  // ---- Serial Plotter Output ----
  // Format: Raw_Temp Smoothed_Temp Raw_Hum Smoothed_Hum
  Serial.print(temperatureC);
  Serial.print(" ");
  Serial.print(avgTemp);
  Serial.print(" ");
  Serial.print(humidity);
  Serial.print(" ");
  Serial.println(avgHum);

  delay(2000);
}


