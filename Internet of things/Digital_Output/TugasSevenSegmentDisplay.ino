// ----- Seven Segment Multiplexing: Tampilkan 678 -----

// Urutan pin segmen (a,b,c,d,e,f,g,dp)
int segPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};  

// Hanya 3 digit digunakan (kanan ke kiri: digit0 = satuan, digit2 = ratusan)
int digitPins[3] = {10, 11, 12};  

// Pola angka 0-9 untuk common anode → 1 = ON, 0 = OFF
byte numbers[10][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}  // 9
};

// 3 digit terakhir NIM → Contoh: 678
int nimDigits[3] = {6, 7, 8};  // urut dari digit paling kiri ke kanan

void setup() {
  // Set semua pin segmen sebagai OUTPUT
  for (int i = 0; i < 8; i++) {
    pinMode(segPins[i], OUTPUT);
  }

  // Set semua digit control sebagai OUTPUT
  for (int i = 0; i < 3; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
}

void showDigit(int value, int digit) {
  // Matikan semua digit (agar hanya 1 digit aktif setiap saat)
  for (int i = 0; i < 3; i++) {
    digitalWrite(digitPins[i], HIGH); // HIGH = OFF (common anode)
  }

  // Tampilkan angka ke segmen
  for (int s = 0; s < 8; s++) {
    digitalWrite(segPins[s], numbers[value][s] ? LOW : HIGH); 
    // LOW = ON (common anode)
  }

  // Aktifkan digit yang dimaksud
  digitalWrite(digitPins[digit], LOW);  // LOW = ON
  delay(3);  // Delay multiplexing
}

void loop() {
  // Tampilkan 3 digit angka NIM satu per satu
  for (int d = 0; d < 3; d++) {
    showDigit(nimDigits[d], d);
  }
}
