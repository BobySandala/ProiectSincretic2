void read_temp(void) {
  int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;
 
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
 
  if ( !ds.search(addr)) {
    //Serial.print("No more addresses.\n");
    ds.reset_search();
     
     return;
 }
 
  //Serial.print("R=");
  for( i = 0; i < 8; i++) {
    //Serial.print(addr[i], HEX);
   // Serial.print(" ");
  }
 
  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.print("CRC is not valid!\n");
      return 0.0;
  }
 
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end
 
  delay(800); 
 
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad
 

  for ( i = 0; i < 9; i++) {        // we need 9 bytes
    data[i] = ds.read();
  }
 
  //Conversion of raw data to C
  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit
  if (SignBit) // negative
  {
    TReading = (TReading ^ 0xffff) + 1; // 2's comp
  }
  Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25
 
  Whole = Tc_100 / 100;  // separate off the whole and fractional portions
  Fract = Tc_100 % 100;
  current_temp = (float)(Whole + (float)Fract / 100);
}