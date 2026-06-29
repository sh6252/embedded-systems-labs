#ifndef  PROTOCOL_INO
#define  PROTOCOL_INO

#include <ArduinoJson.h>
#include <Adafruit_PWMServoDriver.h>
#include "HexLeg.ino"

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);
HexLeg leg(&pca, 0, 1, 2);

float g_joints[18] = {
  90, 90, 90,  // Leg 1
  90, 90, 90,  // Leg 2
  90, 90, 90,  // Leg 3
  90, 90, 90,  // Leg 4
  90, 90, 90,  // Leg 5
  90, 90, 90   // Leg 6
};
uint16_t g_last_seq = 0;

void sendACK(uint16_t seq, int applied){

  StaticJsonDocument<128> doc;

  doc["type"] = "ACK";
  doc["seq"] = seq;
  doc["ts"] = millis();
  doc["data"]["status"] = "OK";
  doc["data"]["applied"] = applied;

  String out;
  serializeJson(doc, out);
  Serial2.println(out);

}

void sendERR(uint16_t seq, const char* code, const char* msg){

  StaticJsonDocument<128> doc;

  doc["type"] = "ERR";
  doc["seq"] = seq;
  doc["data"]["code"] = code;
  doc["data"]["msg"] = msg;

  String out;
  serializeJson(doc, out);
  Serial2.println(out);

}

void parseFrame(String raw){

  StaticJsonDocument<512> doc;
  
  DeserializationError err = deserializeJson(doc, raw);

  if(err) {
    Serial.println("send ERR BAD_JSON");
    sendERR(0, "BAD_JSON", err.c_str());
    return;
  }

  const char* type = doc["type"];
  uint16_t seq = doc["seq"];

  
  if(strcmp(type, "CMD") == 0){
    JsonArray joints = doc["data"]["joints"];

    if(joints.size() != 18){
      Serial.print("send ERR BAD_SIZE seq: ");
      Serial.println(seq);
      String msg = "Need 18 joints, get ";
      msg += joints.size();
      sendERR(seq, "BAD_SIZE", msg.c_str());
      return;
    }

    Serial.print("Angles [ ");

    for (int i=0; i<18; i++){
      float angle = joints[i];

      if (angle < 0 || angle > 180) { 
        Serial.print("send ERR BAD_ANGLE seq: ");
        Serial.println(seq);
        sendERR(seq, "BAD_ANGLE", "Angle out of range");
        return;
      }

      Serial.print(angle);
      Serial.print(",");
      g_joints[i] = angle;
    }
    Serial.println("]");

    float pos[3] = {g_joints[0], g_joints[1], g_joints[2]};
    leg.smoothTo(pos);

    g_last_seq = seq;
    sendACK(seq, 18);
    Serial.print("send ACK seq: ");
    Serial.println(seq);
  }
}

void uartTask(void *p) {
  while (true) {
    if (Serial2.available()) {
      String raw = Serial2.readStringUntil('\n');
      raw.trim();

      if (raw.length() > 0) {
        parseFrame(raw);
      }
    }

    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

#endif
