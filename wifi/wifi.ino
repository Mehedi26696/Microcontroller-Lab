#include <WiFi.h>
#include <WebServer.h>

// Replace with your WiFi credentials
const char* ssid = "Mehedi";
const char* password = "Mehedi26696";

// Create a web server on port 80
WebServer server(80);

const int ledPin = 2;  // On-board LED (GPIO 2)

bool ledState = false; // Track LED state

String getHTML() {
  String stateText = ledState ? "ON" : "OFF";

  String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>ESP32 LED Control</title>
      <style>
        body {
          font-family: Arial, sans-serif;
          text-align: center;
          background: linear-gradient(135deg, #74ebd5, #9face6);
          height: 100vh;
          margin: 0;
          display: flex;
          justify-content: center;
          align-items: center;
        }
        .card {
          background: white;
          padding: 30px;
          border-radius: 20px;
          box-shadow: 0 4px 20px rgba(0,0,0,0.2);
          max-width: 300px;
          width: 90%;
        }
        h1 {
          color: #333;
          font-size: 24px;
          margin-bottom: 20px;
        }
        p {
          font-size: 18px;
          margin: 10px 0;
        }
        .state {
          font-weight: bold;
          color: #007BFF;
        }
        .btn {
          display: inline-block;
          margin: 10px;
          padding: 12px 25px;
          font-size: 16px;
          font-weight: bold;
          text-decoration: none;
          border-radius: 10px;
          transition: 0.3s;
        }
        .on {
          background: #28a745;
          color: white;
        }
        .on:hover {
          background: #218838;
        }
        .off {
          background: #dc3545;
          color: white;
        }
        .off:hover {
          background: #c82333;
        }
      </style>
    </head>
    <body>
      <div class="card">
        <h1>ESP32 LED Control</h1>
        <p>LED is currently: <span class="state">)rawliteral" + stateText + R"rawliteral(</span></p>
        <a href="/on" class="btn on">Turn ON</a>
        <a href="/off" class="btn off">Turn OFF</a>
      </div>
    </body>
    </html>
  )rawliteral";

  return html;
}

void handleRoot() {
  server.send(200, "text/html", getHTML());
}

void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  ledState = true;
  server.send(200, "text/html", getHTML());
}

void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  ledState = false;
  server.send(200, "text/html", getHTML());
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to WiFi");
  Serial.print("📡 ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Define routes
  server.on("/", handleRoot);
  server.on("/on", handleLEDOn);
  server.on("/off", handleLEDOff);

  // Start the server
  server.begin();
  Serial.println("🌍 HTTP server started");
}

void loop() {
  server.handleClient();
}
