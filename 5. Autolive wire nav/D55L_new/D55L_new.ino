 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define btn1 A2
#define btn2 A1

#define buzzer A0
#define next_btn 3
#define jig_teta 4



String partnum = "200C";

bool initial = false;
bool next = false;

//dibuah jika wire kebanyakan/kurang
int Nwire = 11; //200C
int Nwire2 = 6; //100C

bool btnPressed = false;
bool wrongwire = false;
bool nextStep = false;
bool sel_partnumb = false;
int stepNav = 0;

//
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

struct pinset {
  const int pin_sens;
  const int pin_led;
};

pinset set_pin[11] = {
  {22, 23},
  {24, 25},
  {26, 27},
  {28, 29},
  {30, 31},
  {32, 33},
  {34, 35},
  {36, 37},
  {38, 39},
  {40, 41},
  {42, 43},
  //{45, 44},
};

int urutan_200C[11] = {0, 1, 7, 8, 3, 6, 9, 4, 2, 5 };
int urutan_100C[11] = {0, 1, 7, 8, 10,6 }; // {8,9,0,1,3,7};
String step_100C[11] = {" AMBIL MATERIAL ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", " AMBIL MATERIAL ", " AMBIL MATERIAL "};
String step_200C[11] = {" AMBIL MATERIAL ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", " AMBIL MATERIAL ", " AMBIL MATERIAL ", "   AMBIL WIRE   ", " AMBIL MATERIAL ", " AMBIL MATERIAL ", " AMBIL MATERIAL "};

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(115200);
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

  //tes LED
  for (int i = 0; i < Nwire; i++)
  {
    digitalWrite(set_pin[i].pin_led, HIGH);
    delay(200);
    digitalWrite(set_pin[i].pin_led, LOW);
  }
  digitalWrite(buzzer, LOW);

/*


  for (int i = 0; i <= 10; i++)
  {
    digitalWrite(set_pin[urutan_200C[i]].pin_led, HIGH);
    delay(200);
    digitalWrite(set_pin[urutan_200C[i]].pin_led, LOW);
    delay(200);
  }

  for (int i = 0; i <= 5; i++)
  {
    digitalWrite(set_pin[urutan_100C[i]].pin_led, HIGH);
    delay(200);
    digitalWrite(set_pin[urutan_100C[i]].pin_led, LOW);
    delay(200);
  }
*/
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(jig_teta , INPUT_PULLUP);
  pinMode(next_btn , INPUT_PULLUP);

  Serial.begin(115200);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<  AUTOLIVE  >>");
  lcd.setCursor(0, 1);
  lcd.print("<<  RUNNING!  >>");

  //uncomment
  while (sel_partnumb == false)
  {
    select_partnumb();
  }

  while (initial == false)
  {
    select_history();
  }



}

void loop() {
//put your main code here, to run repeatedly:
  Serial.print(digitalRead(set_pin[stepNav].pin_sens));
  //Serial.print(" | ");
 // Serial.println(digitalRead(jig_teta));
  //Serial.print( digitalRead(next_btn));
  // Serial.println();

 
  next_step();
  baca_nano();





  if (partnum == "200C")
  {
    partnum1();

  }
  else
  {
    partnum2();
  }

  if (next == true) {
    running_program();
  }

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

    if (partnum == "200C")
      digitalWrite(set_pin[urutan_200C[stepNav]].pin_led, HIGH);
    else
      digitalWrite(set_pin[urutan_100C[stepNav]].pin_led, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    if (partnum == "200C")
    {
      lcd.print("      200C      ");
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(step_200C[stepNav]);
    }
    else
    {
      lcd.print("      100C      ");
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(step_100C[stepNav]);
    }
    initial = true;
  }

  if (digitalRead(btn2) == LOW)
  {
    delay(10);
    while (digitalRead(btn2) == LOW)
      EEPROM.write(1, 0);
    stepNav = 0;

    if (partnum == "200C")
      digitalWrite(set_pin[urutan_200C[0]].pin_led, HIGH);
    else
      digitalWrite(set_pin[urutan_100C[0]].pin_led, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    initial = true;

    if (partnum == "200C")
    {
      lcd.print("      200C      ");
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(step_200C[stepNav]);
    }
    else
    {
      lcd.print("      100C      ");
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(step_100C[stepNav]);
    }
  }

}


//---------------------------- select part numb
void select_partnumb()
{
  lcd.setCursor(0, 0);
  lcd.print("SELECT PARTNUMB:");
  lcd.setCursor(0, 1);
  lcd.print("100C        200C");

  //Serial.println(digitalRead(btn1));
  if (digitalRead(btn1) == LOW)
  {
    delay(10);
    while (digitalRead(btn1) == LOW)
      partnum = "200C";
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print("      200C      ");
    sel_partnumb = true;
  }

  if (digitalRead(btn2) == LOW)
  {
    delay(10);
    while (digitalRead(btn2) == LOW)
      partnum = "100C";
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    sel_partnumb = true;
    lcd.print("      100C      ");
  }

}
//---------------------------- select part numb
//edited
