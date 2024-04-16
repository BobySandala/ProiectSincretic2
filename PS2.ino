#include <OneWire.h>

#define LED_PIN 12

// DS18S20 Temperature chip i/o
OneWire ds(13);  // on pin 13

double dutyCycle = 0.0; // Duty cycle in percentage
float current_temp = 0.0;

void setup() {
  
  Serial.begin(9600);
}

void loop() {
  read_temp();
  Serial.print(current_temp);
  Serial.print("\n");

  if (Serial.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial.read();

    if (incomingByte == 'a') {
      digitalWrite(LED_PIN, HIGH);
    } else if (incomingByte == 's') {
      digitalWrite(LED_PIN, LOW);
    }
    
  }

}
