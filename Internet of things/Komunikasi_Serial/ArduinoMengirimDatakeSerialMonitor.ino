void setup() {
 Serial.begin(9600); // memulai komunikasi serial dengan baudrate 9600
}
void loop() {
 Serial.println("Halo IoT UNTIDAR!");
 delay(1000); // kirim pesan setiap 1 detik
}
