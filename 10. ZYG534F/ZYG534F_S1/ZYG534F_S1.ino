#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(53, 52); // RX, TX
//#include "step_ec.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);



#define Buzzer A0
#define relay2 43
#define relay1 42
#define resetEsp 52
#define btn1 A2
#define btn2 A1
#define Sw1 44 // line 2 pin 52
#define Sw2 45

#define BTN_NEXT 41


int Nwire = 14;


int status_ec = 0;
int cekstatus = 0;
int start_ = 0;
int guide = 0;
int Step = 0;

bool material_wrong = false;
bool WireSupply_wrong = false;
int sisa_mat[5] = {0, 0, 0, 0, 0};
int sisa_wire[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
String partnum_mat[5] = {"RMI.WH.02.00000733", "RMI.WH.13.00000148", "RMI.WH.14.00001293", "RMI.WH.14.00001294"};
String rmi_conv[5] = {"2FK-110(A)-BK", "EVTT 12x3", "EVTT 7x8", "EVTT 12x13"};
bool tray_scan_stats[7] = {false, false, false, false, false, false, false};
String pn_mat;
String tray_pos;
String wire_skema;
unsigned long int prevmilis = 0, currentmilis = 0;
long unsigned int PREV_T_STEP = 0, CUR_T_STEP = 0 , currentTP = 0, lastTP = 0;

int i_TP = 2;

struct wire_sup {
  const String wire_skm;
  const String wire_tray;
  const int Step_SA;
};

wire_sup WIRESUPPLY[10] = {
  {"0014", "TRAY 1", 1},
  {"0013", "TRAY 2", 1},
  {"0001","TRAY 3",1},
  {"0002", "TRAY 4", 1},
  {"0009", "TRAY 5", 1},
  {"0012", "TRAY 6", 1},
  {"0003", "TRAY 7", 1},
  {"0004", "TRAY 8", 1},
  {"0005", "TRAY 9", 2},
  {"0006", "TRAY 10", 2},
};

int Val_sw1, Val_sw2;
bool f1 = 0, f2 = 0;
bool NEXT_STEP = false;
bool FINISH = false;
bool WIRE_DETECT = false;
bool MISSWIRE = false;
bool MISSLOC = false;
bool initial = false;
bool initial_mat = false;
bool initial_wire = false;
bool empty_mat = false;
bool empty_wire = false;
bool tray_scan = false;
bool NGstats = false;


String disp_lcd[15] = {"   AMBIL CONN   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", " AMBIL MATERIAL ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", " AMBIL MATERIAL ", " AMBIL MATERIAL ", "  TARIK GOYANG  ", "  TARIK GOYANG  ", " WIRE TO TP CHECK"};
String disp_lcd2[15] = {"   AMBIL CONN   ", " AMBIL MATERIAL ", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", " WIRE TO TP CHECK", "WIRE TO TP CHECK", " WIRE TO TP CHECK", " WIRE TO TP CHECK", " WIRE TO TP CHECK"};


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
  const int pin_in_WIRE;  //proxy
  const int pin_in_TP;  //touchpad
  const int pin_out;  //jig
  const int led_WIRE; //led
  const int led_TP;
  const int led_PJ;
  int numstep;
};

pinset set_pin[14] = {
  {A3,    0,  13,  A15, 0,  0,  0},
  {A4,    0,  0,  2,   0,  28,  0},

  {A5,    0,  0,  3,   0,  29,  0},
  {A6,    0,  18,  4,   0,  0,  0},

  {A7,    0,  19,  5,   0,  0,  0}, // LINE 2
  {A8,    0,  22,  6,   0,  0,  0}, // LINE 2
  {A9,    0,  23,  7,   0,  0,  0}, // LINE 2]

  {A10,   0, 24,  8,   0,  0, 0}, //not used
  {A11,   0, 25,  9,   0,  0, 0}, //not used
  {A12,   0,  26,  10,  0,  0,  0}, //not used
  {A13,   0,  0,   11,  0,  0,  0}, //not used
  {A14,   0,  0,   12,  0,  0,  0}, //not used
  {0,   39,  14,   0,  37,  28,  0}, //not used
  {0,   40,  15,   0,  38,  29,  0}, //not used
};


int sens_wire_read(int flow)
{
  int detect_sens = 0;
  for (int i = 0; i < Nwire; i++)
  {
    if (set_pin[i].pin_in_WIRE != 0)
    {
      if (digitalRead(set_pin[i].pin_in_WIRE) == LOW)
      {
        detect_sens = i + 1;

      }
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
  mySerial.begin(9600);
  lcd.begin();
digitalWrite(resetEsp, LOW);
delay(1000);
digitalWrite(resetEsp, HIGH);
  Initial();
  Serial.println("Ready");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<    READY   >>");
  lcd.setCursor(0, 1);
  lcd.print("<<   ZYG534F  >>");
  start_ = 1;
  //uncomment
  
    while (initial_wire == false)
    {
    count_wire();
    }

    while (initial_mat == false)
    {
    count_mat();
    }

    while (initial == false)
    {
    select_history();
    }

    if (sisa_mat[0] == 0 || sisa_mat[1] == 0 || sisa_mat[2] == 0)
    lcd.clear();
  

}

void cek_sens()
{
  for (int i = 0; i < Nwire; i++)
  {
    //Serial.print(digitalRead(set_pin[i].pin_in_WIRE));
    if (set_pin[i].pin_in_TP != 0)
    {
      Serial.print(digitalRead(set_pin[i].pin_in_TP));
      digitalWrite((set_pin[i].pin_out), LOW);
    }
  }
  Serial.print(" | ");
  Serial.print(digitalRead(btn1));
  Serial.print(digitalRead(btn2));
  Serial.print(" | ");
  Serial.print(digitalRead(BTN_NEXT));
  Serial.print(digitalRead(Sw1));
  Serial.println();

}

void loop() {
  // cek_sens();
  // Serial.println();

  
    while (sisa_wire[0] == 0 || sisa_wire[1] == 0 || sisa_wire[2] == 0 || sisa_wire[3] == 0 || sisa_wire[4] == 0 || sisa_wire[5] == 0 || sisa_wire[6] == 0 || sisa_wire[7] == 0 || sisa_wire[8] == 0 || sisa_wire[9] == 0)
    {
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  SUPPLY WIRE  ");
      supply_wire_process();
    }
  
    if (sisa_mat[0] == 0 && sisa_mat[1] == 0 && sisa_mat[2] == 0 && sisa_mat[3] == 0)
    {
      empty_mat = true;
      lcd.setCursor(0, 0);
      lcd.print("SUPPLY  MATERIAL");
      lcd.setCursor(0, 1);
      lcd.print("                ");


      //delay(1000);

    }
    else if (sisa_mat[0] == 0)
    {
      empty_mat = true;
      lcd.setCursor(0, 0);
      lcd.print("SUPPLY  CONECTOR");
      lcd.setCursor(0, 1);
      lcd.print("                ");

      //delay(1000);

    }
    else if (sisa_mat[1] == 0)
    {
      empty_mat = true;
      lcd.setCursor(0, 0);
      lcd.print("SUPPLY  SEAL PIN");

      //delay(1000);

    }
    else if (sisa_mat[2] == 0)
    {
      empty_mat = true;
      lcd.setCursor(0, 0);
      lcd.print("SUPPLY  TUBE VT ");
      lcd.setCursor(0, 1);
      lcd.print("                ");

      //delay(1000);

    }
    else if (sisa_mat[3] == 0)
    {
      empty_mat = true;
      lcd.setCursor(0, 0);
      lcd.print("SUPPLY  TUBE VT ");
      lcd.setCursor(0, 1);
      lcd.print("                ");

      //delay(1000);

    }
    else
      empty_mat = false;
    baca_scanner();

  

  //  digitalWrite(relay1, HIGH);
  //  digitalWrite(relay2, HIGH);
  //  delay(300);
  //  digitalWrite(relay1, LOW);
  //  digitalWrite(relay2, LOW);
  //  delay(300);
 // baca_scanner();
 // cek_sens();
  //  Serial.print(digitalRead(Sw1));
  //  Serial.print(digitalRead(Sw2));
  //  Serial.print(digitalRead(BTN_NEXT));
  //Serial.println();


  baca_esp();
  //Run();
  //Serial.println(empty_mat);
  if (empty_mat == false)
  run_SNG();
  //digitalWrite(A15,HIGH);


}




void finish_step()
{
  lcd.setCursor(0, 0);
  lcd.print("                 ");
  lcd.setCursor(0, 1);
  lcd.print("   HARNESS  OK   ");
  for (int i = 0; i < Nwire; i++)
  {
    if (set_pin[i].led_WIRE != 0)
      digitalWrite(set_pin[i].led_WIRE, HIGH);
    if (set_pin[i].led_TP != 0)
      digitalWrite(set_pin[i].led_TP, HIGH);
    if (set_pin[i].led_PJ != 0)
      digitalWrite(set_pin[i].led_PJ, HIGH);
  }
  digitalWrite(Buzzer, HIGH);
  digitalWrite(relay1, HIGH);
  delay(300);
  digitalWrite(relay1, LOW);
  digitalWrite(Buzzer, LOW);
  for (int i = 0; i < Nwire; i++)
  {
    if (set_pin[i].led_WIRE != 0)
      digitalWrite(set_pin[i].led_WIRE, LOW);
    if (set_pin[i].led_TP != 0)
      digitalWrite(set_pin[i].led_TP, LOW);
    if (set_pin[i].led_PJ != 0)
      digitalWrite(set_pin[i].led_PJ, LOW);
  }

  cekstatus = 0;
  lcd.setCursor(0, 0);
  lcd.print("<<  RUNNING!  >>");
  lcd.setCursor(0, 1);
  lcd.print(disp_lcd[cekstatus]);
  start_ = 1;
  digitalWrite(Buzzer, LOW);
  MISSWIRE=false; MISSLOC =false;

  if (set_pin[cekstatus].led_WIRE != 0)
      digitalWrite(set_pin[cekstatus].led_WIRE, HIGH);
    if (set_pin[cekstatus].led_TP != 0)
      digitalWrite(set_pin[cekstatus].led_TP, HIGH);
    if (set_pin[cekstatus].led_PJ != 0)
      digitalWrite(set_pin[cekstatus].led_PJ, HIGH);
}

void Initial() {
  pinMode(Sw1, INPUT_PULLUP);
  pinMode(Sw2, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(resetEsp, OUTPUT);
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  // pinMode(19,OUTPUT);
  //pinMode(40,OUTPUT);

  for (int i = 0; i < Nwire; i++)
  {
    if (set_pin[i].pin_out != 0)
      pinMode(set_pin[i].pin_out, OUTPUT);

    if (set_pin[i].pin_in_WIRE != 0)
      pinMode(set_pin[i].pin_in_WIRE, INPUT_PULLUP);

    if (set_pin[i].pin_in_TP != 0)
      pinMode(set_pin[i].pin_in_TP, INPUT_PULLUP);

    if (set_pin[i].led_WIRE != 0)
      pinMode(set_pin[i].led_WIRE, OUTPUT);

    if (set_pin[i].led_PJ != 0)
      pinMode(set_pin[i].led_PJ, OUTPUT);

    if (set_pin[i].led_TP != 0)
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
    cek_error();
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
    cek_error();
  }

}


void cek_LED() {

  for (int i = 0; i < Nwire; i++)
  {
    if (set_pin[i].led_WIRE != 0)
      digitalWrite(set_pin[i].led_WIRE, HIGH);
    if (set_pin[i].led_TP != 0)
      digitalWrite(set_pin[i].led_TP, HIGH);
    if (set_pin[i].led_PJ != 0)
      digitalWrite(set_pin[i].led_PJ, HIGH);
    delay(200);
    if (set_pin[i].led_WIRE != 0)
      digitalWrite(set_pin[i].led_WIRE, LOW);
    if (set_pin[i].led_TP != 0)
      digitalWrite(set_pin[i].led_TP, LOW);
    if (set_pin[i].led_PJ != 0)
      digitalWrite(set_pin[i].led_PJ, LOW);


  }

  //    for(int i=0; i<Nwire; i++)
  //    {
  //    digitalWrite(set_pin[i].led_WIRE,LOW);
  //    digitalWrite(set_pin[i].led_TP,LOW);
  //    digitalWrite(set_pin[i].led_PJ,LOW);
  //    }

}
