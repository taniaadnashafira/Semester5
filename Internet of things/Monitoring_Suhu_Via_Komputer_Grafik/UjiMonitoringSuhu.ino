#include <LiquidCrystal.h>

// Deklarasi pin LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Hardware Serial (misalnya Serial1 di Mega)
#define EspSerial Serial1

// Baud rate untuk komunikasi ESP8266
#define ESP8266_BAUD 9600

// Pin sensor LM35
#define Pin_LM35 A0

// Info koneksi Wi-Fi & ThingSpeak
String WIFI_SSID = "WIFI_DESKTOP1";  // Ganti dengan SSID kamu
String WIFI_PASS = "12345678";       // Ganti dengan password kamu
String API = "H9HJC2RTV93BF5K3";     // Write API Key
String HOST = "api.thingspeak.com";
String PORT = "80";

// Variabel untuk fungsi sendCommand()
int countTimeCommand = 0;
int countTrueCommand = 0;
boolean found = false;

// --- Fungsi kirim AT command ke ESP8266 ---
void sendCommand(String command, int maxTime, const char* expectedReply) {
  found = false;
  countTimeCommand = 0;

  Serial.print(countTrueCommand);
  Serial.print(". AT command => ");
  Serial.println(command);

  EspSerial.println(command);

  while (countTimeCommand < (maxTime * 100)) { // tiap 10 ms x100 = 1 detik
    if (EspSerial.find(const_cast<char*>(expectedReply))) {
      found = true;
      break;
    }
    delay(10);
    countTimeCommand++;
  }

  if (found) {
    Serial.println("OK");
    countTrueCommand++;
  } else {
    Serial.println("Fail");
  }
}

// --- Setup ---
void setup() {
  Serial.begin(9600);            // Serial monitor
  EspSerial.begin(ESP8266_BAUD); // ESP8266 serial

  lcd.begin(16, 2);
  lcd.print("Uji koneksi...");

  // Inisialisasi koneksi ESP8266
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + WIFI_SSID + "\",\"" + WIFI_PASS + "\"", 20, "OK");

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thermometer");
  lcd.setCursor(0, 1);
  lcd.print("Suhu:");
}

// --- Loop utama ---
void loop() {
  // Baca sensor LM35
  int adc_value = analogRead(Pin_LM35);
  float voltage = (adc_value * 5.0) / 1024.0;
  float suhu = voltage / 0.010; // 10 mV per °C

  // Tampilkan suhu
  Serial.print("Suhu = ");
  Serial.print(suhu);
  Serial.println(" C");

  lcd.setCursor(5, 1);
  lcd.print("     "); // hapus tampilan lama
  lcd.setCursor(5, 1);
  lcd.print(suhu, 1);
  lcd.print(" C");

  // Siapkan data untuk ThingSpeak
  String getData = "GET /update?api_key=" + API + "&field1=" + String(suhu) + " HTTP/1.1\r\nHost: " + HOST + "\r\nConnection: close\r\n\r\n";

  // Kirim data ke ThingSpeak
  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");

  int len = getData.length();
  sendCommand("AT+CIPSEND=0," + String(len), 10, ">");

  EspSerial.print(getData);
  delay(1500);
  sendCommand("AT+CIPCLOSE=0", 5, "OK");

  delay(200); // ThingSpeak limit: 15 detik antar kiriman
}
