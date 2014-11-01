#include <OneWire.h>
#include <LiquidCrystal.h>

OneWire  ds(9);  // on pin 10 (a 4.7K resistor is necessary)
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

void setup(void) {
  lcd.begin(16, 2);
}

int iter;
int d,k;
char quad[4];
void loop(void) {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;
  
  if ( !ds.search(addr)) {
    Serial.println();
    iter = 0;
    ds.reset_search();
    delay(500);
    return;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      type_s = 1;
      break;
    case 0x28:
    case 0x22:
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end
  
  delay(100);
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  Serial.print(" ");
  for ( i = 0; i < 9; i++)            // we need 9 bytes
    data[i] = ds.read();
  

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  
  sprintf(quad,"%d",celsius);
  
  lcd.setCursor(iter * 5,0);
  lcd.print("T"); lcd.print(iter); lcd.print("=");
  lcd.setCursor(iter * 5,1);
  lcd.print(celsius);
  
  iter++;
  lcd.setCursor(iter * 5 - 1,1);
  lcd.print(" ");
}
