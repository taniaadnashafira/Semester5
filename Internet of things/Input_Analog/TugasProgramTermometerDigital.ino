#include <LiquidCrystal.h>

// Inisialisasi pin LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Pin sensor LM35 terhubung ke pin analog A0
const int lm35Pin = A0;

void setup() {
  lcd.begin(16, 2);          // Inisialisasi LCD 16x2
  lcd.print("Thermometer");
  delay(1000);
  lcd.clear();
  lcd.print("Suhu: ");
  lcd.print((char)223);      // Simbol derajat (°)
  lcd.print("C");
}

void loop() {
  int adcValue = analogRead(lm35Pin);   // Baca nilai ADC (0–1023)
  
  // 1. Konversi ADC ke tegangan (dalam mV)
  float voltage = (adcValue * 5000.0) / 1023.0;  // 5V = 5000mV
  
  // 2. Konversi tegangan ke suhu (°C)
  float temperature = voltage / 10.0;   // Karena 10mV = 1°C
  
  // 3. Tampilkan hasil pada LCD
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);  // Tampilkan 1 angka di belakang koma
  lcd.print((char)223);       // Simbol derajat
  lcd.print("C   ");          // Tambah spasi untuk menghapus sisa karakter
  
  delay(1000);  // Update tiap 1 detik
}
