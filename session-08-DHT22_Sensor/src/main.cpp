#include "DHTesp.h"
DHTesp dht;
const int DHT_PIN = 4;   // GPIO4
const int WARN_LED_PIN = 15;
const int LED_PIN = 14;

void dhtTask(void *param){
  dht.setup(DHT_PIN, DHTesp::DHT22);
  pinMode(WARN_LED_PIN, OUTPUT);
  Serial.println("=== DHT22 Sensor Ready ===");
  while(true){
    TempAndHumidity data = dht.getTempAndHumidity();
    if (!isnan(data.temperature)) { 
      float heatIndex = data.temperature + 0.33 * data.humidity - 4.0;
      Serial.printf("%ds | Temp: %.1f C | Hum: %.1f %% | Heat: %.1f\n",
              millis()/1000,
              data.temperature,
              data.humidity,
              heatIndex);
      if (data.temperature > 30 || data.humidity > 70) {
        Serial.println("WARNING⚠️: Temperature or humidity is too high!");
        digitalWrite(WARN_LED_PIN, HIGH);
      } else {
        digitalWrite(WARN_LED_PIN, LOW);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void blinkTask(void *param) {

  pinMode(LED_PIN, OUTPUT);

  while(true) {

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));

    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


void setup() {
  Serial.begin(115200);
  xTaskCreate(dhtTask, "DHT", 3000, NULL, 1, NULL);
  xTaskCreate(blinkTask, "blink", 2048, NULL, 1, NULL);
}

void loop() {
 
}
