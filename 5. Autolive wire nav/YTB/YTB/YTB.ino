#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define btn1 A1
#define btn2 A2

#define buzzer A0
#define jig_teta A11
#define next_btn A12


String partnum = "YTB";

bool initial = false;
bool next = false;

//dibuah jika wire kebanyakan/kurang
int Nwire = 11; //200C
int Nwire2 = 6; //100C
int NwireYTB = 6; //YTB

bool btnPressed=false;
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

pinset set_pin[10] = {
  {10, 10},
  {A5, A9},
  {A6, A10},
  {A3, A7},
  {30, A13},
  {A4, A8},
  {A14, A15},
  
  
  
  
  
  
  //{30, 31},
  //{32, 33},
  //{34, 35},
  //{36, 37},
  //{38, 39},
  //{40, 41},
  //{42, 43},
  //{45, 44},
};

int urutan_200C[11] = {8,9,0,1,4,7,2,5,10,6};
int urutan_100C[10] = {8,9,0,1,3,7};
int urutan_YTB[10] = {1,2,3,4,5,6};
String step_YTB[11] = {"   AMBIL WIRE   "," AMBIL MATERIAL "," AMBIL MATERIAL "," AMBIL MATERIAL "," AMBIL MATERIAL "," AMBIL MATERIAL "," AMBIL MATERIAL "};


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
  

  for (int i = 0; i < NwireYTB; i++)
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

    for(int i=0; i<=10; i++)
  {
    digitalWrite(set_pin[urutan_200C[i]].pin_led,HIGH);
    delay(200);
    digitalWrite(set_pin[urutan_200C[i]].pin_led,LOW);
    delay(200);
  }

  for(int i=0; i<=5; i++)
  {
    digitalWrite(set_pin[urutan_100C[i]].pin_led,HIGH);
    delay(200);
    digitalWrite(set_pin[urutan_100C[i]].pin_led,LOW);
    delay(200);
  }
  
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(jig_teta , INPUT_PULLUP);
  pinMode(next_btn , INPUT_PULLUP);

  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<  AUTOLIVE  >>");
  lcd.setCursor(0, 1);
  lcd.print("<<  RUNNING!  >>");

  //uncomment
   /*
   while(sel_partnumb == false)
   {
     select_partnumb();
   }   
   */

   while (initial == false)
    {
      select_history();
    }
stepNav=0;


}

void trial()
{
    for(int i=0; i<NwireYTB; i++)
  {
  Serial.print(digitalRead(set_pin[urutan_YTB[i]].pin_sens));
  Serial.print(" | ");
  }
  // Serial.print(digitalRead(set_pin[stepNav].pin_sens));
   Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

//trial();
   //Serial.println(digitalRead(45));
  
 
  next_step();
  baca_nano();

/*
  if(partnum == "200C")
  {
  partnum1();
  
  }
  else if("100C")
  {
  partnum2();
  }
  else
  */
  partnum_YTB();

  // if (next == true) {
//  running_program();
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

    if(partnum == "200C")
    digitalWrite(set_pin[urutan_200C[stepNav]].pin_led, HIGH);
    else if(partnum == "100C")
    digitalWrite(set_pin[urutan_100C[0]].pin_led, HIGH);
    else
    digitalWrite(set_pin[urutan_YTB[0]].pin_led, HIGH);
        
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    if(partnum == "200C")
    lcd.print("      200C      ");
    else if(partnum == "100C")
    lcd.print("      100C      ");
    else
    {
    lcd.print("     -YTB-      ");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print(step_YTB[stepNav]);
    
    }
    initial = true;
  }

  if (digitalRead(btn2) == LOW)
  {
    delay(10);
    while (digitalRead(btn2) == LOW)
      EEPROM.write(1, 0);
    stepNav = 0;

    if(partnum == "200C")
    digitalWrite(set_pin[urutan_200C[0]].pin_led, HIGH);
    else if(partnum == "100C")
    digitalWrite(set_pin[urutan_100C[0]].pin_led, HIGH);
    else
    digitalWrite(set_pin[urutan_YTB[0]].pin_led, HIGH);
    
    
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    initial = true;

    lcd.print("     -YTB-      ");
    delay(1000);
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print(step_YTB[stepNav]);
  }

}


//---------------------------- select part numb
void select_partnumb()
{
  lcd.setCursor(0, 0);
  lcd.print("SELECT PARTNUMB:");
  lcd.setCursor(0, 1);
  lcd.print("100C/200C    YTB");

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
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("   AMBIL WIRE   ");
  }

  if (digitalRead(btn2) == LOW)
  {
    delay(10);
    while (digitalRead(btn2) == LOW)
    partnum = "YTB";
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    sel_partnumb = true;
    lcd.print("     -YTB-      ");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("   AMBIL WIRE   ");
  }

}
//---------------------------- select part numb
//edited
