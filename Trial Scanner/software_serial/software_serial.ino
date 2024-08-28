#include <SoftwareSerial.h>

SoftwareSerial mySerial(53,A0); // RX, TX

void setup() {
  // Inisialisasi komunikasi serial dengan baud rate 9600
  Serial.begin(9600);

  // Inisialisasi komunikasi serial software dengan baud rate 9600
  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available()) {
    char data = mySerial.read(); // Membaca data dari scanner

    if (data == '\n') {
      Serial.println(); // Menambahkan baris baru di Serial Monitor
    } else {
      Serial.print(data); // Menampilkan karakter dari scanner di Serial Monitor
    }
  }
}
