void setup() {
  pinMode(30, INPUT_PULLUP); // tombol sebagai input dengan pull-up internal
  pinMode(22, OUTPUT); // LED sebagai output
}
void loop() {
  bool tombol = digitalRead(30); // baca status tombol
  if (tombol == LOW) { // ditekan → LOW
    digitalWrite(22, HIGH); // LED ON
  }  else { // dilepas → HIGH
    digitalWrite(22, LOW); // LED OFF
  }
}
