#include "protocol.ino"
#include "config.ino"
#include <Wire.h>

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
      
    Wire.begin(SDA_PIN, SCL_PIN);
    pca.begin();
    pca.setPWMFreq(50);

    delay(1000);

    Serial.println("Scanning I2C...");

    for (byte addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            Serial.print("Found device at 0x");
            Serial.println(addr, HEX);
        }
    }

    xTaskCreate(uartTask, "uartTask", 4096, NULL, 3, NULL);

    Serial.println("ESP32 UART Protocol Ready");
}

void loop() {
    // Main loop does nothing, all work is done in uartTask
    delay(1000);
}
