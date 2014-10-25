#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Loading...");
  delay(5000);
  
}

void loop() {
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print ("value from A0");
  int T=analogRead (A0); 
  lcd.setCursor(0, 1);
  lcd.print (T);
  delay (100);
}
