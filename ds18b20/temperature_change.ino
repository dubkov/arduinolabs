#include <OneWire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);
OneWire  ds(8);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A1)); 
  lcd.begin(16, 2);
  lcd.print("Loading... ");
  int percentOfBreak = 71;
  
  for (int percent=0;percent<=99;percent++){
    lcd.print(percent);
    lcd.print("%");
    if (percent <= percentOfBreak){
      delay (random(10,400));  
    }
    else {
      delay (1500);
    }
    lcd.setCursor (12,0);
    
    if (percent == percentOfBreak){
      delay (200);
    }
  }
  lcd.clear();
}

void loop(void) {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;
  
  if ( !ds.search(addr) ) {
    ds.reset_search();
    delay(250);
    return;
  }
  
  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return;
  }
  
  Serial.println();
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);
  delay(500);
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);
  
  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
    int16_t raw = (data[1] << 8) | data[0];
    if (type_s) {
      raw = raw << 3;
      if (data[7] == 0x10) raw = (raw & 0xFFF0) + 12 - data[6];
    } else {
      byte cfg = (data[4] & 0x60);
      if (cfg == 0x00) raw = raw & ~7;
      else if (cfg == 0x20) raw = raw & ~3;
      else if (cfg == 0x40) raw = raw & ~1;
    }
    
    celsius = (float)raw / 16.0;
    lcd.setCursor(0,0);
    lcd.print(celsius);
    lcd.setCursor(5,0);
    lcd.print(" Gradusov ");
    Serial.print(celsius);
    Serial.print(" Gradusov ");
    if (celsius<20){
      lcd.setCursor(0,1);
      lcd.print(" COLD           ");
    }
    if (celsius>=20 && celsius<26){
      lcd.setCursor(0,1);
      lcd.print(" ROOM TEMPERATUR");
    }
    if (celsius>=26 && celsius<31){
      lcd.setCursor(0,1);
      lcd.print(" MEDIUM         ");
    }
    if (celsius>=31 && celsius<40){
      lcd.setCursor(0,1);
      lcd.print(" HOT            ");
    }
    if (celsius>=40){
      lcd.setCursor(0,1);
      lcd.print("YOU BURN, RUN!");
    }
  }
}

void enotPoloskun(){}
