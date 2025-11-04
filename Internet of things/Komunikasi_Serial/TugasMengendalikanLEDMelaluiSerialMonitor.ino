const int LED = 22;
char data;
void setup() {
 pinMode(LED, OUTPUT);
 Serial.begin(9600); // memulai komunikasi serial
 Serial.println("Ketik '1' untuk LED ON, '0' untuk LED OFF");
}
void loop() {
 if (Serial.available() > 0) {
 data = Serial.read();
 if (data == '1') {
 digitalWrite(LED, HIGH);
 Serial.println("LED MENYALA");
 } else if (data == '0') {
 digitalWrite(LED, LOW);
 Serial.println("LED MATI");
 }
 }
}