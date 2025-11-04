#include <Keypad.h>
#include <LiquidCrystal.h>
// Konfigurasi LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7
// Ukuran keypad
const byte ROWS = 4;
const byte COLS = 4;
// Susunan tombol pada keypad
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
5
};
// Pin baris dan kolom keypad
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {8, 9, 10, 11};
// Objek keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
void setup() {
 lcd.begin(16,2);
 lcd.print("Test Keypad 4x4");
 lcd.setCursor(0,1);
 lcd.print("Keypad:");
}
void loop() {
 char key = keypad.getKey(); // baca tombol yang ditekan
 if (key != NO_KEY) {
 lcd.setCursor(7,1); // posisi kolom ke-7 di baris kedua
 lcd.print(key); // tampilkan karakter tombol
 }
