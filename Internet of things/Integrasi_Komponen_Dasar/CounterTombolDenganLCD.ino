#include <LiquidCrystal.h> 
LiquidCrystal lcd(2,3,4,5,6,7); // CN3 (LCD) 
 
const int BTN_COUNT = 30;   // SW1 untuk increment 
const int BTN_RESET = 31;   // SW2 untuk reset 
int hitung = 0; 
int btnCount, btnReset; 
 
void setup() { 
  pinMode(BTN_COUNT, INPUT_PULLUP); // tombol ke GND 
  pinMode(BTN_RESET, INPUT_PULLUP); // tombol ke GND 
 
  lcd.begin(16,2); 
  lcd.print("Counter:"); 
  lcd.setCursor(0,1); 
  lcd.print("00"); 
} 
 
void loop() { 
  btnCount = digitalRead(BTN_COUNT); 
  btnReset = digitalRead(BTN_RESET); 
 
  // tombol reset ditekan (aktif LOW) 
  if (btnReset == LOW) { 
    hitung = 0; 
  }  
  // tombol count ditekan (aktif LOW) 
  else if (btnCount == LOW) { 
    if (hitung < 99) { 
      hitung = hitung + 1; 
    } else { 
      hitung = 0; // balik ke 00 kalau lebih dari 99 
    } 
    delay(200); // debounce sederhana 
  } 
 
  // tampilkan hasil 
  lcd.setCursor(0,1); 
  if (hitung < 10) lcd.print("0"); // selalu 2 digit 
  lcd.print(hitung); 
  lcd.print("  "); // hapus sisa digit lama 
} 