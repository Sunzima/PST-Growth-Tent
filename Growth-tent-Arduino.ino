#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <BH1750.h>
//Code by Rangga Vallian Sayoga, Hanif A Rahadiansyah, Putra Wisnu Adjie
#define DHTPIN 13
#define TIPEDHT DHT11
#define relay 3
#define fanPin 2  // Pin untuk mengontrol kipas
#define pumpPin 5  // Pin untuk mengontrol water pump

const int LampPin = 7; //Relay Lamp

DHT dht(DHTPIN, TIPEDHT);
BH1750 Cahaya;

// Inisialisasi objek LCD menggunakan I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  // Inisialisasi LCD dengan 16 kolom dan 2 baris
  lcd.backlight();   // Nyalakan backlight LCD
  pinMode(relay, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(LampPin, OUTPUT);
  dht.begin();
  Cahaya.begin();

  // Menampilkan judul di LCD
  lcd.setCursor(3, 0);
  lcd.print("Monitoring");
  lcd.setCursor(4, 1);
  lcd.print("GROW TENT");
  delay(2000);  // Tunggu 2 detik

  // Bersihkan LCD
  lcd.clear();
}

void loop() {
  unsigned int Variabel_1 = 0;
  int IntensitasCahaya = Cahaya.readLightLevel();
  float kelembaban = dht.readHumidity();
  float temperatur = dht.readTemperature();

  if (isnan(kelembaban) || isnan(temperatur) || isnan(IntensitasCahaya)) {
    Serial.println(F("Gagal membaca sensor"));
    return;
  }
{

  if (IntensitasCahaya < 60){
    digitalWrite(LampPin, LOW);
  } else {
    digitalWrite(LampPin, HIGH);
  }

  if (millis() - Variabel_1 > 300) {
    // Mengontrol kipas berdasarkan tingkat kelembaban
    if (kelembaban < 80) {
      digitalWrite(fanPin, LOW);  // Nyalakan kipas
    } else {
      digitalWrite(fanPin, HIGH);   // Matikan kipas
    }

    // Mengontrol water pump berdasarkan suhu
  
    

    // Mengontrol relay berdasarkan tingkat kelembaban
  
    }

    // Menampilkan data di LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("H:");
    lcd.print(kelembaban);
    lcd.print("% ");
    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(temperatur);
    lcd.print("C ");
    lcd.setCursor(9, 1); // Pindah ke kolom ke-9 pada baris ke-1
    lcd.print("Lux: ");
    lcd.print(IntensitasCahaya);
  }

  Serial.print("Kelembaban: ");
  Serial.print(kelembaban);
  Serial.print("%  Temperatur: ");
  Serial.print(temperatur);
  Serial.print("°C ");
  Serial.print("  Lux: ");
  Serial.print(IntensitasCahaya);
  Serial.println();

  delay(1000);
}
