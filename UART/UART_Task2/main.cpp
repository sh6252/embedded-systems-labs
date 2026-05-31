#define TX2_PIN 17
#define RX2_PIN 16

void setup() {
    Serial.begin(115200);       
    Serial2.begin(115200, SERIAL_8N1, RX2_PIN, TX2_PIN);  
    
    Serial.println("Loopback Test Ready!");
}

void loop() {

    if (Serial.available() > 0) {
        String msg = Serial.readStringUntil('\n');
        
        Serial2.println(msg);
        Serial.println("Sent: " + msg);
    }
    
    if (Serial2.available() > 0) {
        String received = Serial2.readStringUntil('\n');
        Serial.println("Received back: " + received);
    }
}