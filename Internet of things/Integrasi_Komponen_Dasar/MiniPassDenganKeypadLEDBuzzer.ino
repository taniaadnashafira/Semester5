#include <Keypad.h> 
 
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
 
const int LED = 22; 
const int BUZZ = 24; 
String password = "5";  // password sederhana 
String input = ""; 
 
void setup() { 
  pinMode(LED, OUTPUT); 
  pinMode(BUZZ, OUTPUT); 
  Serial.begin(9600); 
  Serial.println("Masukkan password:"); 
} 
 
void loop() { 
  char key = keypad.getKey(); 
  if (key) { 
    input = String(key); 
    Serial.print("Input: "); Serial.println(input); 
 
    if (input == password) { 
      digitalWrite(LED, HIGH); 
      digitalWrite(BUZZ, HIGH); 
      delay(200); 
      digitalWrite(BUZZ, LOW); 
      Serial.println("Password Benar"); 
    } else { 
      digitalWrite(LED, LOW); 
      digitalWrite(BUZZ, HIGH); 
      delay(600); 
      digitalWrite(BUZZ, LOW); 
      Serial.println("Password Salah"); 
    } 
  } 
} 