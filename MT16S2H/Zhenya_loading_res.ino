#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

void setup() {
  randomSeed(analogRead(A1)); 
  lcd.begin(16, 2);
  lcd.print("Loading... ");
  int percentOfBreak = 71;
  
  for (int percent=0;percent<=100;percent++){
    lcd.print(percent);
    lcd.print("%");
    if (percent <= percentOfBreak){
      delay (random(10,800));  
    }
    else {
      delay (100);
    }
    lcd.setCursor (12,0);
    
    if (percent == percentOfBreak){
      delay (4000);
    }
  }
}

void loop() {
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print ("A0 value = ");
  int T=analogRead (A0); 
  lcd.setCursor(12, 0);
  lcd.print (T);
  delay (100);
}
