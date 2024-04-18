#include <OneWire.h>
#include <EEPROM.h>

#define EEPROM_MESSAGE_TABLE_MESSAGE_SIZE 15
#define EEPROM_MESSAGE_TABLE_ENTRIES_SIZE 10
#define EEPROM_MESSAGE_DELIMITATOR '|'

#define LED_PIN 12
#define INUNDATIE_PIN 8
#define TEMP_READ 't'
#define LED_STATE_READ 'l'
#define READ_MESSAGE_EEPROM 'm'
#define LED_TEMP_INUNDATIE_READ 'd'
#define MSG_LENGTH 15
#define END_LINE 10
#define MSG_RECEIVED 'o'

#define LM335_SENSOR_CHANNEL 0
#define ADC_REF_VOLTAGE 5.0

// DS18S20 Temperature chip i/o
OneWire ds(13);  // on pin 13

double dutyCycle = 0.0; // Duty cycle in percentage
float current_temp = 0.0;
int led_state = 0;
int inundatie_state = 0;
int inundatie_pin_last_state = 0;

void initi(void) 
{  
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRA |= (1 << ADEN);
}

void setup() {
  //initi();
  digitalWrite(LED_PIN, LOW);
  led_state = 0;
  Serial.begin(9600);
  eeprom_read_msg();
  //eeprom_serial_write();
  pinMode(INUNDATIE_PIN, INPUT);
}

void toggle_led() {
  digitalWrite(LED_PIN, !led_state);
  led_state = !led_state;
}

void serial_print_data() {
  Serial.print(current_temp);
  Serial.print(":");
  Serial.print(led_state);
  Serial.print(":");
  Serial.println(inundatie_state);
}

void loop() {
  read_temp();
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial.read();

    if (incomingByte == 'a' || incomingByte == 's') {
      toggle_led();
    } else if(incomingByte == LED_TEMP_INUNDATIE_READ) {
      serial_print_data();
    } else if (incomingByte == READ_MESSAGE_EEPROM) {
      int msg_byte[MSG_LENGTH];
      for (int i = 0; i < MSG_LENGTH; i++) {
        msg_byte[i] = Serial.read();
      }
      update_msg_table(msg_byte);
      //eeprom_serial_write();
      eeprom_write_msg();
    }
  }
  if (digitalRead(INUNDATIE_PIN) == HIGH && inundatie_pin_last_state == 0) {
    inundatie_state = !inundatie_state;
    inundatie_pin_last_state = 1;
  } else {
    inundatie_pin_last_state = 0;
  }
}
