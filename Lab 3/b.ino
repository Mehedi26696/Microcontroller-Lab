#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 4         
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println("Failed to read from sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  |  Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  delay(2000);
}
