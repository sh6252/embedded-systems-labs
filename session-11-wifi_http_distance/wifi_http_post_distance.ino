#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

//=======================
// WIFI + SERVER
//=======================
const char* ssid = "DDID";
const char* password = "PASSWORD";

const char* SERVER = "http://httpbin.org/post";

//=======================
// PINS
//=======================
#define TRIG_PIN 5
#define ECHO_PIN 27
#define LED_PIN 4

//=======================
// GLOBALS
//=======================
float g_distance = 0;

BLECharacteristic *pCharacteristic;

//=======================
// SENSOR
//=======================
float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  return duration * 0.0343 / 2;
}

//=======================
// TASK: SENSOR
//=======================
void sensorTask(void *pvParameters) {
  while (true) {
    g_distance = readDistance();
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

//=======================
// TASK: DISPLAY + LED
//=======================
void displayTask(void *pvParameters) {
  while (true) {

    Serial.print("Distance: ");
    Serial.println(g_distance);

    if (g_distance > 0 && g_distance <= 5) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

//=======================
// TASK: BLE
//=======================
void bleTask(void *pvParameters) {
  while (true) {

    char msg[64];
    snprintf(msg, sizeof(msg), "Distance: %.1f", g_distance);

    pCharacteristic->setValue(msg);
    pCharacteristic->notify();

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

//=======================
// TASK: WIFI (HTTP)
//=======================
void wifiTask(void *pvParameters) {
  while (true) {

    if (WiFi.status() == WL_CONNECTED) {

      HTTPClient http;
      http.begin(SERVER);
      http.addHeader("Content-Type", "application/json");

      StaticJsonDocument<200> doc;
      doc["distance"] = g_distance;

      String body;
      serializeJson(doc, body);

      int code = http.POST(body);

      Serial.print("HTTP Code: ");
      Serial.println(code);

      String response = http.getString();
      Serial.println("Server response:");
      Serial.println(response);

      http.end();
    }

    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

//=======================
// SETUP
//=======================
void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  // WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // BLE INIT
  BLEDevice::init("ESP32");

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService("1234");

  pCharacteristic = pService->createCharacteristic(
    "5678",
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  BLEDevice::getAdvertising()->start();

  // TASKS
  xTaskCreate(sensorTask, "sensorTask", 2048, NULL, 1, NULL);
  xTaskCreate(displayTask, "displayTask", 2048, NULL, 1, NULL);
  xTaskCreate(bleTask, "bleTask", 4096, NULL, 1, NULL);
  xTaskCreate(wifiTask, "wifiTask", 8192, NULL, 1, NULL);
}

//=======================
// LOOP
//=======================
void loop() {
  vTaskDelay(portMAX_DELAY);
}