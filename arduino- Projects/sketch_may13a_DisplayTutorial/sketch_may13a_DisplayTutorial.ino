#include <LiquidCrystal.h>

LiquidCrystal lcd(1,2,3,4,5,6);
void setup() {
  // put your setup code here, to run once:
  
  lcd.begin(16,2);

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.print("Jesus Saves");
  delay(10000);
  lcd.print("AMEN");
  delay(10000);
  lcd.clear();

}
