#include <LiquidCrystal.h>
#include <SPI.h>

#define LOW_SS 14
#define SLAVES 2
#define lsc00 lcd.setCursor(0,0)
#define lsc01 lcd.setCursor(8,0)
#define lsc10 lcd.setCursor(0,1)
#define lsc11 lcd.setCursor(8,1)
#define lsp lcd.print

LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

unsigned int ss;
unsigned int gaiar[SLAVES];
unsigned char raw[SLAVES*2];

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  Serial.begin(38400);
  
  SPI.begin();
  
  DDRC =  0b00111111; // all output instead of analog
  PORTC = 0b00111111; // all high by default
}

void loop() {
  
  
  // Read from slaves
  for(ss=0; ss<SLAVES; ss++)
  {
    PORTC &=~(1 << ss);    // pull down (hear me)
    delay(100);
    raw[ss*2]  = SPI.transfer(0xAA); // low byte
    delay(1);
    raw[ss*2+1]= SPI.transfer(0xCC); // high byte
    // Get temperature
    gaiar[ss] = (raw[ss*2]<<8 + raw[ss*2+1]) >> 4;
    PORTC |= (1 << ss);    // restore  (i'm gone)
  }
  
  
  // Publish data
  lcd.clear();
  lsc00; lsp(gaiar[0]);
  lsc01; lsp(gaiar[1]);
  //lsc10; lsp(gaiar[2]);
  //lsc11; lsp(gaiar[3]);
  
  delay(10);
}
