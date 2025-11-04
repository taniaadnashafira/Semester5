const int BUZZ = 24; 
void setup() { 
pinMode(BUZZ, OUTPUT); 
} 
void loop() { 
digitalWrite(BUZZ, HIGH); // buzzer ON 
delay(500); 
digitalWrite(BUZZ, LOW);  // buzzer OFF 
delay(500); 
} 