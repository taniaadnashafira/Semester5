const int BUZZ = 24; 
void setup() { 
  pinMode(BUZZ, OUTPUT); 
} 
void loop() { 
  for (int i = 0; i < 5; i++) {
    digitalWrite(BUZZ, HIGH); // buzzer ON 
    delay(200); 
    digitalWrite(BUZZ, LOW);  // buzzer OFF 
    delay(200); 
  
  }
  while (true);
}