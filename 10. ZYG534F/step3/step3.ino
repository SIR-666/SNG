#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define tgt 34

struct pinmega {
  int pin_out;
  int pin_in;
  int pin_led;
  String Stats;
};

/*
  Pin² meja 089
  Pin TP : A3-A9
  Pin LED : A10-2
  Pin TG : 4-10
  pin_out;
  pin_in;
  pin_led;

*/
int n_wire = 10;
pinmega step_pin[11] = {
  {A3, 12, A13, "SKM9"},
  {A6, 15, 2, "SKM2"},
  {A7, 14, 3, "SKM1"},
  {A8, 11, 4, "SKM12"},
  {A9, 22, 5, "SKM6"},
  {A11, 19, 7, "SKM4"},
  {A12, 18, 8, "SKM3"},
  {A8, 10, 24, "OR"},
  {A3, 9, 23, "L/B"},
  {35, 13, 27, "SKM5"},


};

String sm;
String idname[9] = {
  "QC1",
  "QC2",
  "QC3",
  "ANDRY",
  "AUTO",
  "AUTO1",
  "HARI",
  "2112W09",
  "KN"
};

//-------------MILLIS-----------//
long int prevmilis = 0;
long int currentmilis = 0;




int urutan = 0;
bool misswire = false;
String inputString;
bool Start_ = false;
bool rst = false;
bool lock = false;
bool ng_interlock = false;
bool misswire_rst = false;
bool misslock = false;
bool tarik_goyang = false;
#define stamp 33
#define buzzer A0

#define rst_but A1
#define Start__stop A2
#define stamp 33



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(115200);
  for (int z = 0; z < 10; z++) {
    pinMode(step_pin[z].pin_in, INPUT);
  }
  for (int z = 0; z < 10; z++) {
    pinMode(step_pin[z].pin_out, OUTPUT);
  }
  for (int z = 0; z < 10; z++) {
    pinMode(step_pin[z].pin_led, OUTPUT);
  }
  pinMode(stamp, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(stamp, OUTPUT);
  pinMode(tgt, INPUT_PULLUP);
  pinMode(rst_but, INPUT_PULLUP);
  pinMode(Start__stop, INPUT_PULLUP);
  digitalWrite(stamp, LOW);
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("<<  BISMILLAH >>");
  lcd.setCursor(0, 1);
  lcd.print("<<   TARGET   >>");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<TARIK GOYANG>>");
  lcd.setCursor(7, 1);
  lcd.print(step_pin[urutan].Stats);
}

void loop() {
  //serialEvent();
 // delay(200);
  baca_esp();
  // put your main code here, to run repeatedly:

  Serial.print(digitalRead(tgt));


  if (misswire == true)
  {
    digitalWrite(buzzer, HIGH);
  }
  else
    run_prog();


}



void finish() {
  lock = false;
  digitalWrite(stamp, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(stamp, LOW);
  digitalWrite(buzzer, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" PASANG HARNESS ");
}
