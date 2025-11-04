#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int adc0;

void setup() {
  lcd.begin(16, 2);          
  lcd.print("ADC Channel 0"); 
  lcd.setCursor(0, 1);
  lcd.print("ADC0=");
}

void loop() {
  adc0 = analogRead(A0);     
  lcd.setCursor(5, 1);
  lcd.print(adc0);           
  lcd.print("   ");          
  delay(1000);
}
