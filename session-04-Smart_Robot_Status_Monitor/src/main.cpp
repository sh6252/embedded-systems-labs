#include <Arduino.h>
#include <DHT.h>

#define DHT_PIN 21
#define DHTTYPE DHT22

#define TRIG_PIN 4
#define ECHO_PIN 16
#define LED_BUILTIN 18

DHT dht(DHT_PIN, DHTTYPE);

float distance = 999.0;

float readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  return duration * 0.034 / 2;
}

void taskDistance(void *pvParameters) {
  while (true) {
    distance = readDistanceCM();

    bool isNearby = distance < 20;

    digitalWrite(LED_BUILTIN, isNearby);

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  xTaskCreate(taskDistance, "Distance Task", 4096, NULL, 1, NULL);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT Failed!");
  } else {
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.println("°C");

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("%");
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 20) {
    Serial.println("DANGER ⚠️⚠️⚠️");
  }

  Serial.println("---");

  delay(2000);
}