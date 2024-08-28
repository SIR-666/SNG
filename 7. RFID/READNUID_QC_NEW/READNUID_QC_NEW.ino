//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(5, 6); // RX, TX

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5 //5
#define RST_PIN 0  //0
#define RES 25
#define RESET_MACHIN 26
#define EN 34
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];
String id = "";
struct no_id {
  String UID;
  String nama;
};
no_id nama_id[43] //ganti
{ {"137125192104", "QC1"},
  {"5845182129", "QC1"},
  {"160606034", "QC1"},
  {"1604719234", "QC2"},
  {"13721772163", "QC3"},
  {"1243920451", "AUTO"},
  {"1699250104", "AUTO"},
  {"207106250146", "HARI"}, //HARI K
  {"4723625185", "2112W09"}, //SYAHRONI
  {"239219155211", "KN"}, //NASHIKIN
  {"1066012129", "QC1"},
  {"127235183137", "SYAHRONI"}, //SYAHRONI
  {"18413924277", "AUTO"}, //YD
  {"19523622113", "AUTO"},
  {"831061433", "AUTO"},
  {"1792717348", "AUTO"},
  {"83459453", "AUTO"},
  {"147171662", "AUTO"},
  {"99175200254", "AUTO"},
  {"195218448", "AUTO"},
  {"163132353", "AUTO"},
  {"1473922652", "AUTO"},
  {"19993148", "AUTO"},
  {"9991196254", "AUTO"},
  {"831545928", "AUTO"},
  {"99246176254", "AUTO"},
  {"147126102254", "AUTO"},
  {"8320510748", "AUTO"},
  {"11543248", "AUTO"},
  {"995311448", "AUTO"},
  {"512422752", "AUTO"},
  {"351207428", "AUTO"},
  {"19514714952", "AUTO"},
  {"16311811952", "AUTO"},
  {"20811015088", "AUTO"},
  {"147255192254", "AUTO"},
  {"796719353", "AUTO"}, //YURA BAGUS N.T
  {"17565143215", "AUTO"}, //WAHYU DARMAWAN
  {"2391891166", "AUTO"}, //SUBHAN AWALI
  {"1514518481", "AUTO"}, //IKHSAN MAHARDIKA.U
  {"7916170197", "AUTO"}, //ADAM GUMELAR S.
  {"1119715479", "AUTO"}, //RIKA HANDAYANI
  {"79182195238", "AUTO"}, //DODDY OSCHAR


};

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  pinMode(RES, OUTPUT);
  pinMode(RESET_MACHIN, OUTPUT);
  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  //Serial.print Hex(key.keyByte, MFRC522::MF_KEY_SIZE);
  digitalWrite(EN, LOW);
  delay(1000);
  digitalWrite(EN, HIGH);
  digitalWrite(RES, HIGH);
  digitalWrite(RESET_MACHIN, HIGH);

}

void loop() {
  //mySerial.println("coba");
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  //Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));


  //  Serial.println(F("A new card has been detected."));

  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
    id = id + String(nuidPICC[i]);

  }

  for (int i = 0; i < 43; i++) //ganti
  {
    if (nama_id[i].UID == id)
    {
      Serial.println(nama_id[i].nama);
      Serial2.println(nama_id[i].nama);
      delay(1000);
      //reset_manual();
      //mySerial.println(nama_id[i].nama);


      //digitalWrite(6,LOW);

    }
    else
    {
      Serial.println(id);
      // Serial.print(" | ");
      //int leng = id.length();
      //Serial.println(leng);
    }
    //digitalWrite(pinLED,LOW);
  }

  id = "";
  /*
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
  */
  //  Serial.println();
  //}
  // else Serial.println(F("Card read previously."));

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
   Helper routine to dump a byte array as dec values to Serial.
*/
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
