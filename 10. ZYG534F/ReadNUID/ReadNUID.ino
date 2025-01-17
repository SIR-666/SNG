/*
   --------------------------------------------------------------------------------------------------------------------
   Example sketch/program showing how to read new NUID from a PICC to serial.
   --------------------------------------------------------------------------------------------------------------------
   This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid

   Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
   Reader on the Arduino SPI interface.

   When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
   then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
   you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
   will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
   when removing the PICC from reading distance too early.

   @license Released into the public domain.

   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/
//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(5, 6); // RX, TX


#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 21
#define RST_PIN 22

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;


// Init array that will store new NUID
byte nuidPICC[4];
String id = "";
struct no_id {
  String UID;
  String nama;
};
no_id nama_id[55] //ganti
{
  {"160606034", "QC1"},
  {"1604719234", "QC2"},
  {"13721772163", "QC3"},
  {"1243920451", "AUTO"},
  {"1699250104", "AUTO"},
  {"207106250146", "HARI"},
  {"4723625185", "2112W09"},
  {"239219155211", "KN"},
  {"7464135129", "QC1"},
  {"127235183137", "SYAHRONI"},
  {"6979160172", "AUTO"},
  {"9622410027", "AUTO"},
  {"12738174137", "AUTO"},
  {"1510184137", "AUTO"},
  {"9012159180", "AUTO"},
  {"1021647126", "AUTO"},
  {"16812617377", "AUTO"},
  {"682421069", "AUTO"},
  {"71112335", "AUTO"},
  {"841136169", "AUTO"},
  {"18421320477", "AUTO"},
  {"232116935", "AUTO"},
  {"16814113677", "AUTO"},
  {"1682316077", "AUTO"},
  {"14721625", "AUTO"},
  {"191602166", "AUTO"},
  {"10247244126", "AUTO"},
  {"184599677", "AUTO"},
  {"1688811777", "AUTO"},
  {"16822819177", "AUTO"},
  {"1841534377", "AUTO"},
  {"1681328877", "AUTO"},
  {"1684518877", "AUTO"},
  {"1841595877", "AUTO"},
  {"184204677", "AUTO"},
  {"184951077", "AUTO"},
  {"1841472677", "AUTO"},
  {"18413924277", "AUTO"},
  {"1604719234", "AUTO"},
  {"160606034", "AUTO"},
  {"122176124128", "AUTO"},
  {"1243920451", "AUTO"},
  {"8118516439", "AUTO"},
  {"25021715128", "AUTO"},
  {"21827144122", "AUTO"},
  {"19523622113", "AUTO"},
  {"13114521313", "AUTO"},
  {"4219190126", "AUTO"},
  {"1531943104", "AUTO"},
  {"19523622113", "AUTO"},
  {"2391891166", "AUTO"},
  {"19557417", "AUTO"},
  {"49232183137", "AUTO"},
  {"17565143215", "AUTO"},
  {"35147216", "AUTO"},
  
};

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  pinMode(A7, OUTPUT);
  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  //printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
  digitalWrite(A7, HIGH);
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

  for (int i = 0; i < 55; i++) //ganti
  {
    if (nama_id[i].UID == id)
    {
      Serial.println(nama_id[i].nama);
      Serial2.println(nama_id[i].nama);
      delay(1000);

      //  mySerial.println(nama_id[i].nama);
      digitalWrite(A7, LOW);

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
