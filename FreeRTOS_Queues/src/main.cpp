#include <Arduino.h>

// Pin definitions for ESP32 DOIT DevKit V1
const int BUTTON_PIN = 4;    // Push button input pin (safer than IO0)
const int LED_PIN = 2;       // On-board LED or external LED pin

QueueHandle_t buttonQueue;

void buttonTask(void *pvParameters) {
  int lastRawState = HIGH;
  int stableState = HIGH;
  int buttonState;
  int valueToSend;
  const TickType_t debounceDelay = pdMS_TO_TICKS(50);
  TickType_t lastDebounceTime = 0;

  while (true) {
    buttonState = digitalRead(BUTTON_PIN);

    if (buttonState != lastRawState) {
      lastDebounceTime = xTaskGetTickCount();
    }

    if ((xTaskGetTickCount() - lastDebounceTime) > debounceDelay) {
      if (buttonState != stableState) {
        stableState = buttonState;
        valueToSend = (stableState == LOW) ? 1 : 0;

        if (xQueueSend(buttonQueue, &valueToSend, pdMS_TO_TICKS(10)) == pdPASS) {
          Serial.printf("Sent: %d\r\n", valueToSend);
        }
      }
    }

    lastRawState = buttonState;
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

void ledTask(void *pvParameters) {
  int receivedValue;

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  while (true) {
    if (xQueueReceive(buttonQueue, &receivedValue, portMAX_DELAY) == pdPASS) {
      if (receivedValue == 1) {
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }

      Serial.printf("Received: %d\r\n", receivedValue);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  buttonQueue = xQueueCreate(10, sizeof(int));
  if (buttonQueue == NULL) {
    Serial.println("Failed to create queue");
    while (true) {
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }

  xTaskCreate(buttonTask, "ButtonTask", 2048, NULL, 1, NULL);
  xTaskCreate(ledTask, "LEDTask", 2048, NULL, 1, NULL);

  Serial.println("FreeRTOS queue example started");
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
