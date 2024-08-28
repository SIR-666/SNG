#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define btn1 51
#define btn2 50

#define buzzer 53
#define next_btn 48
bool initial = false;
bool next = false;
int Nwire = 11; //dibuah jika wire kebanyakan/kurang

bool wrongwire = false;
int stepNav = 0;

// 
String sm;
String idname[7] = {
  "QC1",
  "QC2",
  "QC3",
  "AUTO",
  "HARI",
  "2112W09",
  "KN"
};

struct pinset {
  const int pin_sens;
  const int pin_led;
};

pinset set_pin[11] = {
  {43, 42},
  {23, 22},
  {25, 24},
  {27, 26},
  {29, 28},
  {31, 30},
  {33, 32},
  {35, 34},
  {37, 36},
  {39, 38},
  {41, 40},
 //{43, 42},
 //{45, 44},
};

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(9600);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("<<  BISMILLAH >>");
  lcd.setCursor(0, 1);
  lcd.print("<<   TARGET   >>");

  for (int i = 0; i < Nwire; i++)
  { pinMode(set_pin[i].pin_sens, INPUT_PULLUP);
    pinMode(set_pin[i].pin_led, OUTPUT);
  }
  /*
    //tes LED
    for(int i=0; i<Nwire; i++)
    {
    digitalWrite(set_pin[i].pin_led,HIGH);
    delay(1000);
    digitalWrite(set_pin[i].pin_led,LOW);
    }
    digitalWrite(buzzer,LOW);


  */
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(next_btn , INPUT_PULLUP);

  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<   ZYG089   >>");
  lcd.setCursor(0, 1);
  lcd.print("<<  RUNNING!  >>");

  //uncomment
  while (initial == false)
  {
    select_history();
  }

  

}

void loop() {
  // put your main code here, to run repeatedly:
  /// Serial.print(digitalRead(set_pin[stepNav].pin_sens));
  // Serial.print(" | ");
  //  Serial.println(digitalRead(set_pin[4].pin_sens));

  if(digitalRead(next_btn)== LOW && next==true){
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print("   AMBIL WIRE   ");
    
    digitalWrite(set_pin[stepNav].pin_led, LOW);
    stepNav++;
    next = false;
    Serial.println("OK");
    EEPROM.write(1, stepNav);

    if (stepNav < Nwire)
    digitalWrite(set_pin[stepNav].pin_led, HIGH);
    analogWrite(buzzer, 400);
    delay(300);
    analogWrite(buzzer, 0);

    if (stepNav == Nwire)
    {
      finish();
    }
  }

  baca_nano();

 // if (next == true) {
    running_program();
  //}

  if (wrongwire == true)
  {
    analogWrite(buzzer, 300);
  }
}



void select_history()
{
  lcd.setCursor(0, 0);
  lcd.print("<<CONT-PROCESS>>");
  lcd.setCursor(0, 1);
  lcd.print("NO           YES");

  //Serial.println(digitalRead(btn1));
  if (digitalRead(btn1) == LOW)
  {
    delay(10);
    while (digitalRead(btn1) == LOW)
      stepNav = EEPROM.read(1);
    digitalWrite(set_pin[stepNav].pin_led, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print("   AMBIL WIRE   ");
    initial = true;
  }

  if (digitalRead(btn2) == LOW)
  {
    delay(10);
    while (digitalRead(btn2) == LOW)
      EEPROM.write(1, 0);
    stepNav = 0;
    digitalWrite(set_pin[0].pin_led, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    initial = true;
    lcd.print("   AMBIL WIRE   ");
  }

}
//edited
