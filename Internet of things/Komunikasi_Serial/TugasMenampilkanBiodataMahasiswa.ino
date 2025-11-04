void setup() {
 Serial.begin(9600); // memulai komunikasi serial dengan baudrate 9600
}
void loop() {
 Serial.println("NIM    : 2320506034");
 Serial.println("Nama   : Tania Adna Shafira");
 Serial.println("Prodi  : Teknologi Informasi");
 delay(3000); // kirim pesan setiap 3 detik
}
