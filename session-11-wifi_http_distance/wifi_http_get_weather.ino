#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WIFI
const char* ssid = "SSID";
const char* password = "PASSWORD";

// API
const char* url = "http://api.open-meteo.com/v1/forecast?latitude=32&longitude=34&current_weather=true";

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(url);

    int code = http.GET();

    if (code > 0) {

      String payload = http.getString();
      Serial.println("Raw JSON:");
      Serial.println(payload);

      // Parse JSON
      StaticJsonDocument<1024> doc;

      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {

        float temp = doc["current_weather"]["temperature"];

        Serial.print("Current Temperature: ");
        Serial.println(temp);

      } else {
        Serial.print("JSON error: ");
        Serial.println(error.c_str());
      }

    } else {
      Serial.print("HTTP Error: ");
      Serial.println(code);
    }

    http.end();
  }

  delay(10000); 
}