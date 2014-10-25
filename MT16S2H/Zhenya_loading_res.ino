#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Loading... ");
  for (int g=0;g<101;g++){
  lcd.print(g);
  lcd.print("%");
    delay (250);  
    lcd.setCursor (12,0);
  }
//  delay(25000);
  
}

void loop() {
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print ("A0 value = ");
int T=analogRead (A0); 
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(12, 0);
  lcd.print (T);
  delay (100);
  
  // print the number of seconds since reset:
}
