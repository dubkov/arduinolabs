
#include <LiquidCrystal.h>
#include <SPI.h>

#define LOW_SS 14
#define SLAVES 4
#define lsc00 lcd.setCursor(0,0)
#define lsc01 lcd.setCursor(8,0)
#define lsc10 lcd.setCursor(0,1)
#define lsc11 lcd.setCursor(8,1)
#define lsp lcd.print

LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

int ss,raw[SLAVES];
unsigned char buff;

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
  lcd.clear();
  
  
  // Read from slaves
  for(ss=0; ss<SLAVES; ss++)
  {
    PORTC &=~(1 << ss);    // pull down (hear me)
    raw[ss]  = SPI.transfer(0);      // low byte
    raw[ss] |= SPI.transfer(0) << 8; // high byte
    PORTC |= (1 << ss);    // restore  (i'm gone)
  }
  
  // Publish data
  lsc00; lsp((int) (raw[0]%256)); lsp(','); lsp((int) (raw[0]/256));
  lsc01; lsp((int) (raw[1]%256)); lsp(','); lsp((int) (raw[1]/256));
  lsc10; lsp((int) (raw[2]%256)); lsp(','); lsp((int) (raw[2]/256));
  lsc11; lsp((int) (raw[3]%256)); lsp(','); lsp((int) (raw[3]/256));
  
  delay(10);
}
