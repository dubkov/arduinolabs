#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);
void setup() {
  lcd.begin(16, 2);
}
void loop() {
  lcd.home();
  value = map(analogRead(A0),0,1023,0,16);
  lcd.print("value = ");
  lcd.print(value);
  lcd.setCursor(0, 1);
  for(int i = 0; i < value+1; i++){
    lcd.print("\xFF");
  }
  delay(300);
  lcd.clear();
}

