#include <ArduinoJson.h>

#define RXD2 4
#define TXD2 5

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("ESP32 UART2 ready. Waiting for RPi...");
}


void loop() {
  float angles[18];
  int cnt = 0;

  if(Serial2.available() > 0){
    String msg = Serial2.readStringUntil('\n');
    msg.trim();

    Serial.println("Received:");
    Serial.println(msg);

    char buffer[128];
    msg.toCharArray(buffer, sizeof(buffer));

    char *token = strtok(buffer, ",");

    while (token != NULL && cnt < 18) {
      angles[cnt] = atof(token);
      token = strtok(NULL, ",");
      cnt++;
    }

    for (int i = 0; i < cnt; i++) {
      Serial.print("Angle ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(angles[i]);
    }

    if (cnt != 18) {
      Serial2.println("{ \"status\": \"ERROR\", \"reason\": \"bad_format\" }");
    } else {
      Serial2.println("{ \"status\": \"OK\", \"received\": 18 }");
    }

  }

}
