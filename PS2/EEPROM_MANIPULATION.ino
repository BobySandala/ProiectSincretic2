

typedef struct EEPROMMessageEntry
{
    char message[EEPROM_MESSAGE_TABLE_MESSAGE_SIZE];
} EEPROMMessageEntry;

typedef struct EEPROMMessageTable
{
    EEPROMMessageEntry entry[EEPROM_MESSAGE_TABLE_ENTRIES_SIZE];
} EEPROMMessageTable;
EEPROMMessageTable msg_table;

void eeprom_read_msg() {
  int eeprom_addr = 0;
  int eeprom_read;
  for (int i = 0; i < EEPROM_MESSAGE_TABLE_ENTRIES_SIZE; i++) {
    for (int j = 0; j < EEPROM_MESSAGE_TABLE_MESSAGE_SIZE; j++) {
      eeprom_read = EEPROM.read(eeprom_addr++);
      msg_table.entry[i].message[j] = eeprom_read;
    }
  }
}

void eeprom_serial_write() {
  for (int i = 0; i < EEPROM_MESSAGE_TABLE_ENTRIES_SIZE; i++) {
    for (int j = 0; j < EEPROM_MESSAGE_TABLE_MESSAGE_SIZE; j++) {
      Serial.print(msg_table.entry[i].message[j]);
    }
    Serial.println();
  }
}

void eeprom_write_msg() {
  int adr = 0;
  for (int i = 0; i < EEPROM_MESSAGE_TABLE_ENTRIES_SIZE; i++) {
    for (int j = 0; j < EEPROM_MESSAGE_TABLE_MESSAGE_SIZE; j++) {
      //Serial.print(msg_table.entry[i].message[j]);
      EEPROM.write(adr, msg_table.entry[i].message[j]);
      adr++;
    }
  }
}

void rotate_msg_table(int from, int to) {
  for (int i = 0; i < EEPROM_MESSAGE_TABLE_MESSAGE_SIZE; i++) {
    msg_table.entry[to].message[i] = msg_table.entry[from].message[i];
  }
}

void update_msg_table(int msg_byte[]) {
  for (int i = EEPROM_MESSAGE_TABLE_ENTRIES_SIZE - 1; i > 0; i--) {
    rotate_msg_table(i - 1, i);
  }
  for (int i = 0; i < EEPROM_MESSAGE_TABLE_MESSAGE_SIZE; i++) {
    msg_table.entry[0].message[i] = msg_byte[i];
  }
}


