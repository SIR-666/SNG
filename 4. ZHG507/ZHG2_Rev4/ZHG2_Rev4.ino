#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include "step_ec.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);



#define Buzzer A0
#define relay2 50
#define relay1 51

#define btn1 A2
#define btn2 A1

#define Sw1 10
#define Sw2 11

#define lock_con A6
#define BTN_NEXT 14
#define And_On 46

#define sensJig1 A9
#define sensJig2 A8
#define sensJig3 A7


int Nwire = 4;

int i_TP = 0;

int status_ec = 0;
int cekstatus = 0;
int start_ = 0;
int guide = 0;
int Step = 0;

unsigned long int prevmilis = 0, currentmilis = 0;
long unsigned int PREV_T_STEP = 0, CUR_T_STEP = 0 , currentTP = 0, lastTP = 0;


int Val_sw1, Val_sw2;
bool f1 = 0, f2 = 0;
bool NEXT_STEP = false;
bool FINISH = false;
bool WIRE_DETECT = false;
bool MISSWIRE = false;
bool MISSLOC = false;
bool initial = false;
bool NGstats = false;
bool NG_VT = false;

String disp_lcd[12] = {"   AMBIL WIRE   ", "   AMBIL WIRE   ", " AMBIL MATERIAL ", " AMBIL MATERIAL  ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", " AMBIL MATERIAL ", " AMBIL MATERIAL ", " AMBIL MATERIAL "};
String disp_lcd2[12] = {"WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", " AMBIL MATERIAL ", " AMBIL MATERIAL ", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", " AMBIL MATERIAL ", " AMBIL MATERIAL "};


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


unsigned long previousmillis1 = 0, previousmillis2 = 0;
unsigned long interval1 = 2, interval2 = 2;

struct pinset {
  const int pin_in_WIRE;
  const int pin_in_TP;
  const int pin_out;
  const int led_WIRE;
  const int led_TP;
  const int led_PJ;
  int numstep;
};
/*
  pinset set_pin[8] = {
  {2,19,P13,P7,P8,1},
  {2,17,P13,P6,P8,1},
  {4,15,P14,P5,P0,1},
  {10,3,P15,0,P9,2},
  {8,5,P6,P1,P10,2},
  {14,7,P5,P2,P11,2},
  {16,9,P7,P3,P12,2},
  {6,12,P3,0,P4,2},
  };
*/
pinset set_pin[4] = {
  //  {A3,33,13,A15,A15,A15,0},
  //  {A7,33,13,5,25,5,1},
  //  {A8,34,14,6,26,6,1},
  //  {A9,35,15,7,27,7,1},
  //  {A10,36,18,8,28,8,1},
  {A11, 5, 19, 12, 52, 12, 1},
  //  {A12,38,22,10,30,10,1},
  //  {A13,39,23,11,31,11,1},
  {A14, 6, 24, 9, 53, 9, 1},
  {A5, 33, 13, 3, 3, 3, 0},
  {A4, 33, 13, 2, 2, 2, 0},

};


int sens_wire_read(int flow)
{
  int detect_sens = 0;
  for (int i = 0; i < Nwire; i++)
  {
    if (digitalRead(set_pin[i].pin_in_WIRE) == LOW)
    {
      detect_sens = i + 1;

    }
  }
  if (detect_sens > 0)
    return detect_sens;
  else
    return 0;
}



void setup() {
  Serial.begin(9600);
  Serial2.begin(115200);
  lcd.begin();
  Initial();
  Serial.println("Ready");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<    READY   >>");
  lcd.setCursor(0, 1);
  lcd.print("<<   ZHG507   >>");
  start_ = 1;
  //uncomment

  while (initial == false)
  {
    select_history();
  }

}

void cek_sens()
{
  for (int i = 0; i < Nwire; i++)
  {
    // Serial.print(digitalRead(set_pin[i].pin_in_WIRE));
    Serial.print(digitalRead(set_pin[i].pin_in_TP));
    digitalWrite((set_pin[i].pin_out), HIGH);
  }
  Serial.print(" | ");
  Serial.print(digitalRead(btn1));
  Serial.print(digitalRead(btn2));
  Serial.print(" | ");
  Serial.print(digitalRead(BTN_NEXT));
  Serial.print(digitalRead(lock_con));
  Serial.print(digitalRead(sensJig1));
  Serial.print(digitalRead(sensJig2));
  Serial.print(digitalRead(sensJig3));
  Serial.println();

}

void loop() {
  // cek_sens();
  // Serial.println();
  baca_esp();
  // Run();
  run_SNG();
  //digitalWrite(A15,HIGH);


}




void finish_step()
{
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  lcd.setCursor(0, 1);
  lcd.print("   HARNESS  OK   ");
  for (int i = 0; i < Nwire; i++)
  {
    digitalWrite(set_pin[i].led_WIRE, HIGH);
    digitalWrite(set_pin[i].led_TP, HIGH);
    digitalWrite(set_pin[i].led_PJ, HIGH);
  }
  digitalWrite(Buzzer, HIGH);
  digitalWrite(relay1, HIGH);
  delay(100);
  digitalWrite(relay1, LOW);
  digitalWrite(Buzzer, LOW);
  for (int i = 0; i < Nwire; i++)
  {
    digitalWrite(set_pin[i].led_WIRE, LOW);
    digitalWrite(set_pin[i].led_TP, LOW);
    digitalWrite(set_pin[i].led_PJ, LOW);
  }

  cekstatus = 0;
  lcd.setCursor(0, 0);
  lcd.print("<<  RUNNING!  >>");
  lcd.setCursor(0, 1);
  lcd.print(disp_lcd[cekstatus]);
  start_ = 1;
}

void Initial() {
  pinMode(Sw1, INPUT_PULLUP);
  pinMode(Sw2, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(lock_con, INPUT_PULLUP);
  pinMode(sensJig1, INPUT);
  pinMode(sensJig2, INPUT);
  pinMode(sensJig3, INPUT);
  pinMode(And_On, OUTPUT);
  digitalWrite(And_On, LOW);
  // pinMode(19,OUTPUT);
  //pinMode(40,OUTPUT);

  for (int i = 0; i < Nwire; i++)
  {
    pinMode(set_pin[i].pin_out, OUTPUT);
    pinMode(set_pin[i].pin_in_WIRE, INPUT_PULLUP);
    pinMode(set_pin[i].pin_in_TP, INPUT);
    pinMode(set_pin[i].led_WIRE, OUTPUT);
    pinMode(set_pin[i].led_PJ, OUTPUT);
    pinMode(set_pin[i].led_TP, OUTPUT);
  }


  digitalWrite(Buzzer, LOW);
  cek_LED();

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
      cekstatus = EEPROM.read(1);
    MISSWIRE = EEPROM.read(50);
    MISSLOC = EEPROM.read(51);
    digitalWrite(set_pin[cekstatus].led_WIRE, HIGH);
    digitalWrite(set_pin[cekstatus].led_TP, HIGH);
    digitalWrite(set_pin[cekstatus].led_PJ, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd[cekstatus]);
    initial = true;
  }

  if (digitalRead(btn2) == LOW)
  {
    delay(10);
    while (digitalRead(btn2) == LOW)
      EEPROM.write(1, 0);
    MISSWIRE = EEPROM.read(50);
    MISSLOC = EEPROM.read(51);
    cekstatus = 0;
    digitalWrite(set_pin[0].led_WIRE, HIGH);
    digitalWrite(set_pin[0].led_TP, HIGH);
    digitalWrite(set_pin[0].led_PJ, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    initial = true;
    lcd.print(disp_lcd[cekstatus]);
  }

}


void cek_LED() {

  for (int i = 0; i < Nwire; i++)
  {
    digitalWrite(set_pin[i].led_WIRE, HIGH);
    digitalWrite(set_pin[i].led_TP, HIGH);
    digitalWrite(set_pin[i].led_PJ, HIGH);
    delay(500);
    digitalWrite(set_pin[i].led_WIRE, LOW);
    digitalWrite(set_pin[i].led_TP, LOW);
    digitalWrite(set_pin[i].led_PJ, LOW);
  }

  //    for(int i=0; i<Nwire; i++)
  //    {
  //    digitalWrite(set_pin[i].led_WIRE,LOW);
  //    digitalWrite(set_pin[i].led_TP,LOW);
  //    digitalWrite(set_pin[i].led_PJ,LOW);
  //    }

}
