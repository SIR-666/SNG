#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A11, A14); // RX, TX
//#include "step_ec.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);



#define Buzzer A0
#define relay2 50
#define relay1 49

#define btn1 A2
#define btn2 A1
#define Sw1 52 // line 2 pin 52
#define Sw2 51

#define BTN_NEXT 53


int Nwire = 7;


int status_ec = 0;
int cekstatus = 0;
int start_ = 0;
int guide = 0;
int Step = 0;

bool material_wrong = false;
bool WireSupply_wrong = false;
int sisa_mat[5] = {0, 0, 0, 0, 0};
int sisa_wire[8] = {0, 0, 0, 0, 0, 0, 0, 0};
String partnum_mat[5] = {"RMI.WH.02.00000733", "RMI.WH.13.00000148", "RMI.WH.14.00001293", "RMI.WH.14.00001294"};
String rmi_conv[5] = {"7283-2148-30", "7158-3169-40", "TUBE 9x10", "TUBE 6x7"};
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

wire_sup WIRESUPPLY[8] = {
  {"0002", "TRAY 1", 1},
  {"0006", "TRAY 2", 1},
  //  {"0008","TRAY 3",1},
  {"0005", "TRAY 4", 1},
  {"0007", "TRAY 5", 1},
  {"0001", "TRAY 6", 1},
  {"0004", "TRAY 7", 2},
  {"0003", "TRAY 8", 2},
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


String disp_lcd[12] = {"   AMBIL CONN   ", " AMBIL MATERIAL ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", "   AMBIL WIRE   ", " AMBIL MATERIAL ", " AMBIL MATERIAL ", " AMBIL MATERIAL "};
String disp_lcd2[12] = {"   AMBIL CONN   ", " AMBIL MATERIAL ", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", "WIRE TO TP CHECK", " AMBIL MATERIAL ", " AMBIL MATERIAL "};


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

pinset set_pin[12] = {
  {A3, 32, 13, A15, A15, A15, 0},
  {A4, 32, 13, 2, 2, 2, 0},

  {A7, 33, 13, 5, 25, 5, 1},
  {A8, 34, 14, 6, 26, 6, 1},

  {A10, 35, 18, 8, 28, 8, 1}, // LINE 2
  {A13, 36, 22, 11, 31, 11, 1}, // LINE 2
  {A12, 37, 23, 10, 41, 10, 1}, // LINE 2

//  {A10, 36, 18, 8, 28, 8, 1}, //LINE 1
//  {A12, 38, 22, 10, 30, 10, 1}, //LINE 1
//  {A13, 39, 23, 11, 31, 11, 1}, //LINE 1

  {A9, 35, 15, 7, 27, 7, 1}, //not used
  {A5, 37, 19, 9, 29, 9, 1}, //not used
  {A5, 40, 24, 12, 32, 12, 1}, //not used
  {A5, A5, 13, 3, 3, 3, 0}, //not used
  {A6, A6, 13, 4, 4, 4, 0}, //not used
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
  mySerial.begin(9600);
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
    Serial.print(digitalRead(set_pin[i].pin_in_TP));
    digitalWrite((set_pin[i].pin_out), HIGH);
  }
  Serial.print(" | ");
  Serial.print(digitalRead(btn1));
  Serial.print(digitalRead(btn2));
  Serial.print(" | ");
  Serial.print(digitalRead(BTN_NEXT));
  Serial.print(digitalRead(Sw1));

}

void loop() {
   //cek_sens();
   //Serial.println();


  while (sisa_wire[0] == 0 || sisa_wire[1] == 0 || sisa_wire[2] == 0 || sisa_wire[3] == 0 || sisa_wire[4] == 0 || sisa_wire[5] == 0 || sisa_wire[6] == 0)
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
    digitalWrite(set_pin[i].led_WIRE, HIGH);
    digitalWrite(set_pin[i].led_TP, HIGH);
    digitalWrite(set_pin[i].led_PJ, HIGH);
  }
  digitalWrite(Buzzer, HIGH);
  digitalWrite(relay1, HIGH);
  delay(300);
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

  // pinMode(19,OUTPUT);
  //pinMode(40,OUTPUT);

  for (int i = 0; i < (Nwire + 3); i++)
  {
    if (i < Nwire)
    {
      pinMode(set_pin[i].pin_out, OUTPUT);
      pinMode(set_pin[i].pin_in_WIRE, INPUT_PULLUP);
      pinMode(set_pin[i].pin_in_TP, INPUT);
      pinMode(set_pin[i].led_WIRE, OUTPUT);
      pinMode(set_pin[i].led_PJ, OUTPUT);
      pinMode(set_pin[i].led_TP, OUTPUT);
    }
    else
    {
      pinMode(set_pin[i].pin_out, OUTPUT);
    }
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
    digitalWrite(set_pin[i].led_WIRE, HIGH);
    digitalWrite(set_pin[i].led_TP, HIGH);
    digitalWrite(set_pin[i].led_PJ, HIGH);
    delay(200);
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
