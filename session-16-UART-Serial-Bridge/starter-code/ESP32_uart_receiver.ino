#define RXD2 4
#define TXD2 5

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("ESP32 UART2 ready. Waiting for RPi...");
}

void loop() {
  if(Serial2.available() > 0){
    String msg = Serial2.readStringUntil('\n');
    msg.trim();

    Serial.print("Received from RPi: ");
    Serial.println(msg);

    String reply = "ESP32_ACK: " + msg + "\n";
    Serial2.print(reply);
    Serial.print("Sent reply: ");
    Serial.println(reply);
  }

}
