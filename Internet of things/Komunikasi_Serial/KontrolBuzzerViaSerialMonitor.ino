const int BUZZ = 22;
String data = "";  // Ubah dari char menjadi String agar bisa baca "ON" atau "OFF"

void setup() {
  pinMode(BUZZ, OUTPUT);
  Serial.begin(9600); // Memulai komunikasi serial
  Serial.println("Ketik 'ON' untuk buzzer menyala, Ketik 'OFF' untuk buzzer mati");
}

void loop() {
  if (Serial.available() > 0) {
    data = Serial.readStringUntil('\n'); // Baca input sampai newline
    data.trim(); // Hapus spasi atau newline dari input

    if (data == "ON") {
      digitalWrite(BUZZ, HIGH);
      Serial.println("BUZZER AKTIF");
    } else if (data == "OFF") {
      digitalWrite(BUZZ, LOW);
      Serial.println("BUZZER NONAKTIF");
    } else {
      Serial.println("Perintah tidak dikenali. Ketik ON atau OFF.");
    }
  }
}
