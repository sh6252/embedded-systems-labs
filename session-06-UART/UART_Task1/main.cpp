#define LED_PIN 2  

void setup() {
    Serial.begin(11520);       
    pinMode(LED_PIN, OUTPUT);   
}

void loop() {
    if (Serial.available() > 0) {       
        char cmd = Serial.read();        

        if (cmd == '1') {
            digitalWrite(LED_PIN, HIGH); 
            Serial.println("LED ON");
        } 
        else if (cmd == '0') {
            digitalWrite(LED_PIN, LOW);  
            Serial.println("LED OFF");
        }
    }
}