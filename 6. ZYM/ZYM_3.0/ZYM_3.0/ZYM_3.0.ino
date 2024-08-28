#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A12,A13); // RX, TXmanot difarina
#include "step_ec.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);



#define Buzzer A0
#define relay2 50
#define relay1 49

#define btn1 A2
#define btn2 A1

#define Sw1 5


#define BTN_NEXT 6

#define lock_con 52
#define assy_LS1 50
#define assy_LS2 51

int Nwire=6;


int status_ec = 0;
int cekstatus = 0;
int start_ =0;
int guide = 0;
int Step = 0;
int sisa_mat=0;

String conn_pn="RMI.WH.02.00001748";
String conn_rmi="6188-5467";
String pn_mat="";

int Val_sw1, Val_sw2;
bool f1 = 0, f2 = 0;
bool NEXT_STEP = false;
bool FINISH = false;
bool WIRE_DETECT=false;
bool MISSWIRE = false;
bool MISSLOC = false;
bool material_wrong = false;
bool initial = false;
bool initial_mat=false;
bool empty_mat = false;
bool lock = false;
bool assy = false;
int assy_stats[2] = {0,0};

String disp_lcd[12]={"   AMBIL CONN   ","   AMBIL WIRE   "," AMBIL MATERIAL "," AMBIL MATERIAL ","   AMBIL WIRE   ","   AMBIL WIRE   ","   AMBIL WIRE   ","   AMBIL WIRE   ","   AMBIL WIRE   "," AMBIL MATERIAL "," AMBIL MATERIAL "," AMBIL MATERIAL "};
String disp_lcd2[12]={"   PUSH BUTTON  ","","PUSH BUTTON","PUSH BUTTON","TARIK GOYANG","WIRE TO TP CHECK","WIRE TO TP CHECK","WIRE TO TP CHECK","WIRE TO TP CHECK","WIRE TO TP CHECK"," AMBIL MATERIAL "," AMBIL MATERIAL "};


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

struct pinset{
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
   
   pinset set_pin[11] = {
   {A3,33,13,A15,A15,A15,0},    
   {A7,33,13,5,25,5,1},
   {A8,34,14,6,26,6,1},
   {A9,35,15,7,27,7,1},
   {A10,36,18,8,28,8,1},
   {A11,37,19,9,29,9,1},
   {A12,38,22,10,30,10,1},
   {A13,39,23,11,31,11,1},
   {A14,40,24,12,32,12,1},
   {A4,33,13,2,2,2,0},
   {A5,33,13,3,3,3,0},
   };
   */
   /*
   pinset set_pin[7] = {
   {A3,11,11,8,8,8,0},
   {A4,11,11,7,7,7,0},    
   {A5,11,11,9,9,9,0},
   {A6,11,11,10,10,10,0},
   {12,11,11,3,3,3,0},
   {12,A14,A15,4,3,4,0},
   {12,A14,A15,4,3,4,0},
   };
   */
  
   pinset set_pin[7] = {
   {A7,11,11,7,7,7,0},    
   {A8,11,11,8,8,8,0},
   {A9,11,11,9,9,9,0},
   {A10,11,11,10,10,10,0},
   {11,11,11,3,3,3,0},
   {11,A14,A15,4,3,4,0},
   {11,A14,A15,4,3,4,0},
   };
   


int sens_wire_read(int flow)
{
  int detect_sens=0;
  for(int i=0; i<Nwire; i++)
  {
      if(digitalRead(set_pin[i].pin_in_WIRE)==LOW)
      {
        detect_sens=i+1;
        
      }
  }
  if(detect_sens>0)
  return detect_sens;
  else
  return 0;
}



void setup() {
  Serial.begin(9600);
  Serial2.begin(115200);
  mySerial.begin(9600);
  lcd.begin();
  EEPROM.write(50, 0);
        EEPROM.write(51, 0);
  Initial();
  Serial.println("Ready");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<    READY   >>");
   lcd.setCursor(0, 1);
  lcd.print("<<   ZHG507   >>");
  start_ =1;
  //uncomment

   while(initial_mat==false)
  {
    count_mat();
  }
  
  while (initial == false)
  {
    select_history();
  }
  
  if(sisa_mat==0)
  lcd.clear();
}



void cek_sens()
{
  for(int i=0; i<Nwire; i++)
  {
 Serial.print(digitalRead(set_pin[i].pin_in_WIRE));
  //Serial.print(digitalRead(set_pin[i].pin_in_TP));
  digitalWrite((set_pin[i].pin_out),LOW);
  }
  Serial.print(" | ");
  Serial.print(digitalRead(btn1));
  Serial.print(digitalRead(btn2));
  Serial.print(" | ");
  Serial.print(digitalRead(BTN_NEXT));
  Serial.print(digitalRead(Sw1));
  Serial.print(" | ");
  Serial.print(digitalRead(lock_con));
  Serial.print(" | ");
  Serial.print(digitalRead(assy_LS1));
  Serial.print(digitalRead(assy_LS2));
  
}

void loop() {
  //cek_sens();
  //Serial.println();
 
 if(sisa_mat==0)
 {
 empty_mat = true;
 lcd.setCursor(0, 0);
 lcd.print("SUPPLY-MATERIAL");
 lcd.setCursor(8, 1);
 lcd.print(sisa_mat);

 //delay(1000);

 }
 else
 empty_mat = false;
 
  baca_scanner();
  baca_esp();
  //Run();

  if(empty_mat==false);
  run_SNG();
 
//digitalWrite(A15,HIGH);
 
  
}




void finish_step()
{
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("   HARNESS  OK   ");
  for(int i=0; i<Nwire; i++)
  {
    digitalWrite(set_pin[i].led_WIRE,HIGH);
    digitalWrite(set_pin[i].led_TP,HIGH);
    digitalWrite(set_pin[i].led_PJ,HIGH);
    
  }
  digitalWrite(Buzzer,HIGH);
 // digitalWrite(relay1,HIGH);
  delay(1000);
//  digitalWrite(relay1,LOW);
  digitalWrite(Buzzer,LOW);
    for(int i=0; i<Nwire; i++)
  {
    digitalWrite(set_pin[i].led_WIRE,LOW);
    digitalWrite(set_pin[i].led_TP,LOW);
    digitalWrite(set_pin[i].led_PJ,LOW);
  }
  
    cekstatus = 0;
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd[cekstatus]);
    start_ =1;
}

void Initial() {
  pinMode(Sw1, INPUT_PULLUP);
//  pinMode(Sw2, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(BTN_NEXT,INPUT_PULLUP);
  pinMode(btn1,INPUT_PULLUP);
  pinMode(btn2,INPUT_PULLUP);
  pinMode(lock_con,INPUT_PULLUP);
  pinMode(assy_LS1,INPUT_PULLUP);
  pinMode(assy_LS2,INPUT_PULLUP);
 // pinMode(19,OUTPUT);
  //pinMode(40,OUTPUT);

  for(int i=0; i<Nwire; i++)
  {
    pinMode(set_pin[i].pin_out,OUTPUT);
    pinMode(set_pin[i].pin_in_WIRE,INPUT_PULLUP);
    pinMode(set_pin[i].pin_in_TP,INPUT_PULLUP);
    pinMode(set_pin[i].led_WIRE,OUTPUT);
    pinMode(set_pin[i].led_PJ,OUTPUT);
    pinMode(set_pin[i].led_TP,OUTPUT);
  }


  digitalWrite(Buzzer,LOW);
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
    digitalWrite(set_pin[cekstatus].led_WIRE,HIGH);
    digitalWrite(set_pin[cekstatus].led_TP,HIGH);
    digitalWrite(set_pin[cekstatus].led_PJ,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd[cekstatus]);
    cek_error();
    initial = true;
  }

  if (digitalRead(btn2) == LOW)
  {
    delay(10);
    while (digitalRead(btn2) == LOW)
    EEPROM.write(1, 0);
    cekstatus = 0;
    MISSWIRE = EEPROM.read(50);
    MISSLOC = EEPROM.read(51);
    digitalWrite(set_pin[0].led_WIRE,HIGH);
    digitalWrite(set_pin[0].led_TP,HIGH);
    digitalWrite(set_pin[0].led_PJ,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    initial = true;
    lcd.print(disp_lcd[cekstatus]);
    cek_error();
  }

}


void cek_LED() {
  
    for(int i=0; i<Nwire; i++)
    {
    digitalWrite(set_pin[i].led_WIRE,HIGH);
    digitalWrite(set_pin[i].led_TP,HIGH);
    digitalWrite(set_pin[i].led_PJ,HIGH);
    delay(200);
    digitalWrite(set_pin[i].led_WIRE,LOW);
    digitalWrite(set_pin[i].led_TP,LOW);
    digitalWrite(set_pin[i].led_PJ,LOW);
    }
    
//    for(int i=0; i<Nwire; i++)
//    {
//    digitalWrite(set_pin[i].led_WIRE,LOW);
//    digitalWrite(set_pin[i].led_TP,LOW);
//    digitalWrite(set_pin[i].led_PJ,LOW);
//    }
  
}
