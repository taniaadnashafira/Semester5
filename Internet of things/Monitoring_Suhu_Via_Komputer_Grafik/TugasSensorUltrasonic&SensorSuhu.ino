#include <LiquidCrystal.h>

// --- Deklarasi pin LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// --- Hardware Serial (misalnya Serial1 di Mega)
#define EspSerial Serial1

// --- Baud rate ESP8266
#define ESP8266_BAUD 9600

// --- Pin sensor LM35
#define Pin_LM35 A0

// --- Pin sensor Ultrasonik
#define trigPin 8
#define echoPin 9

// --- Info Wi-Fi & ThingSpeak
String WIFI_SSID = "WIFI_DESKTOP1";
String WIFI_PASS = "12345678";
String API = "H9HJC2RTV93BF5K3";
String HOST = "api.thingspeak.com";
String PORT = "80";

// --- Variabel fungsi sendCommand()
int countTimeCommand = 0;
int countTrueCommand = 0;
boolean found = false;

// --- Fungsi kirim AT command ---
void sendCommand(String command, int maxTime, const char* expectedReply) {
  found = false;
  countTimeCommand = 0;

  Serial.print(countTrueCommand);
  Serial.print(". AT command => ");
  Serial.println(command);

  EspSerial.println(command);

  while (countTimeCommand < (maxTime * 100)) {
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
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);

  lcd.begin(16, 2);
  lcd.print("Uji koneksi...");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Koneksi ke Wi-Fi
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + WIFI_SSID + "\",\"" + WIFI_PASS + "\"", 20, "OK");

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thermometer+");
  lcd.setCursor(0, 1);
  lcd.print("Ultrasonic");
  delay(2000);
  lcd.clear();
}

// --- Loop utama ---
void loop() {
  // === Baca suhu dari LM35 ===
  int adc_value = analogRead(Pin_LM35);
  float voltage = (adc_value * 5.0) / 1024.0;
  float suhu = voltage / 0.010; // 10mV per °C

  // === Baca jarak dari Ultrasonik ===
  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2.0; // cm

  // === Tampilkan hasil di Serial Monitor ===
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C,  Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // === Tampilkan di LCD ===
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Suhu:");
  lcd.print(suhu, 1);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Jarak:");
  lcd.print(distance, 1);
  lcd.print("cm");

  // === Kirim data ke ThingSpeak ===
  String getData = "GET /update?api_key=" + API +
                   "&field1=" + String(suhu, 1) +
                   "&field2=" + String(distance, 1) +
                   " HTTP/1.1\r\nHost: " + HOST + "\r\nConnection: close\r\n\r\n";

  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");

  int len = getData.length();
  sendCommand("AT+CIPSEND=0," + String(len), 10, ">");

  EspSerial.print(getData);
  delay(1500);
  sendCommand("AT+CIPCLOSE=0", 5, "OK");

  // === Tunggu sebelum kirim data lagi ===
  delay(20000); // 20 detik, sesuai limit ThingSpeak
}
