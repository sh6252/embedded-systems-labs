#include <Arduino.h>

// =========================
// PINS
// =========================
const int CAR_RED_PIN = 32;
const int CAR_YELLOW_PIN = 33;
const int CAR_GREEN_PIN = 25;

const int PED_RED_PIN = 19;
const int PED_GREEN_PIN = 18;

const int BUTTON_PIN = 17;

// =========================
// STATE MACHINE
// =========================
enum State {
  CAR_GREEN,
  CAR_YELLOW,
  ALL_RED,
  PED_GREEN
};

volatile State state = CAR_GREEN;
volatile State prevState = CAR_YELLOW;
volatile bool pedRequest = false;

SemaphoreHandle_t lock;

// =========================
// LED HELPERS
// =========================
void setCars(bool red = false, bool yellow = false, bool green = false) {
  digitalWrite(CAR_RED_PIN, red);
  digitalWrite(CAR_YELLOW_PIN, yellow);
  digitalWrite(CAR_GREEN_PIN, green);
}

void setPeds(bool red = false, bool green = false) {
  digitalWrite(PED_RED_PIN, red);
  digitalWrite(PED_GREEN_PIN, green);
}

void allRed() {
  setCars(true, false, false);
  setPeds(true, false);
}

void resetAll() {
  digitalWrite(CAR_RED_PIN, LOW);
  digitalWrite(CAR_YELLOW_PIN, LOW);
  digitalWrite(CAR_GREEN_PIN, HIGH);

  digitalWrite(PED_RED_PIN, HIGH);
  digitalWrite(PED_GREEN_PIN, LOW);
}

// =========================
// BUTTON TASK
// =========================
void buttonTask(void *parameter) {
  while (true) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      xSemaphoreTake(lock, portMAX_DELAY);
      pedRequest = true;
      xSemaphoreGive(lock);
    }

    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

// =========================
// CONTROLLER TASK
// =========================
void controllerTask(void *parameter) {

  resetAll();

  while (true) {

    // -------- CAR GREEN --------
    if (state == CAR_GREEN) {

      setCars(false, false, true);
      setPeds(true, false);

      vTaskDelay(pdMS_TO_TICKS(2000));

      xSemaphoreTake(lock, portMAX_DELAY);

      if (pedRequest) {
        xSemaphoreGive(lock);

        prevState = state;
        state = CAR_YELLOW;
        continue;
      }

      xSemaphoreGive(lock);

      vTaskDelay(pdMS_TO_TICKS(2000));

      prevState = state;
      state = CAR_YELLOW;
    }

    // -------- CAR YELLOW --------
    else if (state == CAR_YELLOW) {

      setCars(false, true, false);
      setPeds(true, false);

      vTaskDelay(pdMS_TO_TICKS(1500));

      if (prevState == CAR_GREEN) {
        prevState = state;
        state = ALL_RED;
      } else {
        prevState = state;
        state = CAR_GREEN;
      }
    }

    // -------- ALL RED --------
    else if (state == ALL_RED) {

      allRed();

      vTaskDelay(pdMS_TO_TICKS(300));

      prevState = state;
      state = PED_GREEN;
    }

    // -------- PEDESTRIAN GREEN --------
    else if (state == PED_GREEN) {

      setCars(true, false, false);
      setPeds(false, true);

      vTaskDelay(pdMS_TO_TICKS(3000));

      xSemaphoreTake(lock, portMAX_DELAY);
      pedRequest = false;
      xSemaphoreGive(lock);

      prevState = state;
      state = CAR_YELLOW;
    }
  }
}

// =========================
// SETUP
// =========================
void setup() {

  pinMode(CAR_RED_PIN, OUTPUT);
  pinMode(CAR_YELLOW_PIN, OUTPUT);
  pinMode(CAR_GREEN_PIN, OUTPUT);

  pinMode(PED_RED_PIN, OUTPUT);
  pinMode(PED_GREEN_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(115200);

  lock = xSemaphoreCreateMutex();

  xTaskCreate(
    buttonTask,
    "Button Task",
    2048,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    controllerTask,
    "Controller Task",
    4096,
    NULL,
    1,
    NULL
  );
}

void loop() {
  vTaskDelay(portMAX_DELAY);
}