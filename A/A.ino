#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define btn1 50
#define btn2 51

#define buzzer 53
#define next_btn 44 //ganti pedal
#define jig_TG 45

bool initial = false;
bool next = false;
int Nwire = 9; //dibuah jika wire kebanyakan/kurang

bool wrongwire = false;
int stepNav = 0;

String disp_lcd[11]={"   AMBIL CONN   "," AMBIL MATERIAL ","   AMBIL WIRE   ","   AMBIL WIRE   ","   AMBIL WIRE   ","   AMBIL WIRE   ","   AMBIL WIRE   ","   AMBIL WIRE   "," AMBIL MATERIAL ",};

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
  const int pin_PAD;
  const int pin_out;
  const int pin_led;
  const int led_TG;
  const int led_PJ;
};

pinset set_pin[11] = {
  {2, 14, 28, A0, A0, A0},
  {3, 15, 29, A1, A1, A1},
  {4, 18, 30, A2, A2, A2},
  {5, 19, 31, A3, A3, A3},
  {6, 22, 32, A4, A4, A4},
  {7, 23, 33, A5, A5, A5},
  {8, 24, 34, A6, A6, A6},
  {9, 25, 35, A7, A7, A7},
  {10, 26, 36, A8, A8, A8},
  {11, 27, 37, A9, A9, A9},
  //{24,12, 25, 0},

};

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
    pinMode(set_pin[i].pin_PAD,INPUT);    
    pinMode(set_pin[i].led_TG, OUTPUT);
    pinMode(set_pin[i].pin_out, OUTPUT);
    pinMode(set_pin[i].led_PJ, OUTPUT);
  }
  
    //tes LED
    for(int i=0; i<Nwire; i++)
    {
    digitalWrite(set_pin[i].pin_led,HIGH);
    if(i>=2 && i<=7)
    {
      digitalWrite(set_pin[i].led_TG,HIGH);
    }
    delay(500);
    digitalWrite(set_pin[i].pin_led,LOW);
    if(set_pin[i].led_TG!=0)
    digitalWrite(set_pin[i].led_TG,LOW);
    }
    digitalWrite(buzzer,LOW);


  
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(next_btn , INPUT_PULLUP);
  pinMode(jig_TG,INPUT_PULLUP);

  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<    4L00    >>");
  lcd.setCursor(0, 1);
  lcd.print("<<  RUNNING!  >>");

  //uncomment
  while (initial == false)
  {
    select_history();
  }



}

void loop(){
//  digitalRead(set_pin[1].pin_sens);
//  Serial.print(digitalRead(set_pin[stepNav].pin_sens));
//  delay (1000);
//  Serial.print(" Y ");
//  Serial.println(digitalRead(set_pin[1].pin_sens));
//}



  //-----------main program----------//
  if (digitalRead(jig_TG) == LOW && next == true && (stepNav <2 || stepNav == 8)) {
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    
    digitalWrite(set_pin[stepNav].pin_led, LOW);
    //if(set_pin[stepNav].led_TG!=0);
    digitalWrite(set_pin[stepNav].led_TG, LOW);
    stepNav++;
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd[stepNav]);
    next = false;
    Serial.println("OK");
    EEPROM.write(1, stepNav);

    if (stepNav < Nwire){
      if(set_pin[stepNav].led_TG!=0)
      digitalWrite(set_pin[stepNav].led_TG, HIGH);
      
      digitalWrite(set_pin[stepNav].pin_led, HIGH);






      
    }
    analogWrite(buzzer, 400);
    delay(300);
    analogWrite(buzzer, 0);
    
    if (stepNav == Nwire)
    {
      finish();
    }

      
  }

  
  if (digitalRead(next_btn) == LOW && next == true && ( (stepNav >= 2 &&  stepNav <= 7 ) )) {
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");

    digitalWrite(set_pin[stepNav].pin_led, LOW);
   // if(set_pin[stepNav].led_TG!=0);
    digitalWrite(set_pin[stepNav].led_TG, LOW);
    stepNav++;
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd[stepNav]);
    next = false;
    Serial.println("OK");
    EEPROM.write(1, stepNav);

    if (stepNav < Nwire)
    {
      if(set_pin[stepNav].led_TG!=0)
      digitalWrite(set_pin[stepNav].led_TG, HIGH);
      
      digitalWrite(set_pin[stepNav].pin_led, HIGH);
    }
    analogWrite(buzzer, 400);
    delay(300);
    analogWrite(buzzer, 0);

      
  }

  baca_nano();

  // if (next == true) {
  running_program();
  //}

  if (wrongwire == true)
  {
    analogWrite(buzzer, 300);
  }

  //-----------main program----------//
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
    lcd.print(disp_lcd[stepNav]);
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
    lcd.print(disp_lcd[stepNav]);
  }

}
//edited
