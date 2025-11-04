//----- Menampilkan angka 012345 di 6 digit 7-seg ----- 
// Pin segmen (a,b,c,d,e,f,g,dp) → sesuaikan urutan di modul 
int segPins[8] = {2,3,4,5,6,7,8,9};   
// Pin digit (digit1..digit6) → sesuai kode asli (10,11,12,13,A0,A1) 
int digitPins[6] = {10,11,12,13,A0,A1}; 
// Pola angka 0-9 (a,b,c,d,e,f,g,dp) → 1 = ON, 0 = OFF 
// Asumsi common anode → segmen ON = LOW, OFF = HIGH 
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
// Isi digit: 0 1 2 3 4 5 
int displayDigits[6] = {0,1,2,3,4,5}; 
void setup() { 
for(int i=0;i<8;i++) pinMode(segPins[i], OUTPUT); 
for(int i=0;i<6;i++) pinMode(digitPins[i], OUTPUT); 
} 
void showDigit(int value, int digit) { 
// Matikan semua digit dulu 
for(int i=0;i<6;i++) digitalWrite(digitPins[i], HIGH);  
// Tulis pola angka ke segmen 
for(int s=0;s<8;s++) { 
if(numbers[value][s]==1) digitalWrite(segPins[s], LOW);   // segmen ON 
else digitalWrite(segPins[s], HIGH);                      
} 
// Aktifkan digit yang dipilih 
digitalWrite(digitPins[digit], LOW);   
delay(3);   // multiplex delay (3ms) 
} 
void loop() { 
// loop semua digit (0..5) untuk menampilkan 012345 
for(int d=0; d<6; d++) { 
showDigit(displayDigits[d], d); 
} 
} 