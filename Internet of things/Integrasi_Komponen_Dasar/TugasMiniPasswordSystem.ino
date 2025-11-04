#include <Keypad.h>

// Setup keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {8, 9, 10, 11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Pin LED dan buzzer
const int LED = 22;
const int BUZZ = 24;

// Ganti sesuai 2 digit terakhir NIM kamu!
String password = "34"; 

String input = "";

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(9600);
  Serial.println("Masukkan 2 digit password, tekan '#' untuk submit:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      Serial.print("Password dimasukkan: "); Serial.println(input);

      if (input == password) {
        digitalWrite(LED, HIGH);
        digitalWrite(BUZZ, HIGH);
        delay(200);  // bunyi pendek
        digitalWrite(BUZZ, LOW);
        Serial.println("Password Benar!");
      } else {
        digitalWrite(LED, LOW);
        digitalWrite(BUZZ, HIGH);
        delay(800);  // bunyi panjang
        digitalWrite(BUZZ, LOW);
        Serial.println("Password Salah!");
      }

      input = "";  // reset setelah submit
    } 
    else if (key == '*') {
      input = "";  // reset manual
      Serial.println("Input direset.");
    } 
    else {
      // hanya terima maksimal 2 digit
      if (input.length() < 2 && isDigit(key)) {
        input += key;
        Serial.print("Input sekarang: "); Serial.println(input);
      }
    }
  }
}
