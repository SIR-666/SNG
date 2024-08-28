#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define btn1 51
#define btn2 50

#define buzzer 53
#define next_btn 31 //ganti pedal
#define jig_TG1 49
#define jig_TG2 30

bool initial = false;
bool next = false;
int Nwire = 8; //dibuah jika wire kebanyakan/kurang
bool wrongwire = false;
int stepNav = 0;
int count_TG2= 0;

String disp_lcd[11]={" AMBIL MATERIAL ","   AMBIL WIRE   ","   AMBIL WIRE   "," AMBIL MATERIAL ","  TARIK GOYANG  ","  TARIK GOYANG  ","  TARIK GOYANG  ","   AMBIL WIRE   "};
//edited
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
  const int led_TG;
};

pinset set_pin[13] = {
  {22, 23, 0},
  {24, 25, 10},
  {26, 27, 9},
  {28, 29, 0},
 // {30, 31},
 {0, 0, 44},
 {0, 0, 45},
  {0, 0, 46},
  {32, 33, 47},
  {34, 35, 0},
  {36, 37, 0},
  {38, 39, 0},
  {40, 41, 0},
  {42, 43, 0},
 // {45, 44},
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

  for (int i = 0; i < 12; i++)
  { pinMode(set_pin[i].pin_sens, INPUT_PULLUP);
    pinMode(set_pin[i].pin_led, OUTPUT);
    if(set_pin[i].led_TG!=0)
    pinMode(set_pin[i].led_TG, OUTPUT);
   
    
  }
  
  
    //tes LED
    for(int i=0; i<Nwire; i++)
    {
    digitalWrite(set_pin[i].pin_led,HIGH);
    if(set_pin[i].led_TG!=0)
    digitalWrite(set_pin[i].led_TG,HIGH);
    delay(500);
    if(set_pin[i].led_TG!=0)
    digitalWrite(set_pin[i].led_TG,LOW);
    digitalWrite(set_pin[i].pin_led,LOW);
    }
    digitalWrite(buzzer,LOW);


  
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(jig_TG1, INPUT_PULLUP);
  pinMode(jig_TG2, INPUT_PULLUP);
  pinMode(next_btn , INPUT_PULLUP);

  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<   ZYG089   >>");
  lcd.setCursor(0, 1);
  lcd.print("<<  RUNNING!  >>");

  ////uncomment
  
  while (initial == false)
  {
    select_history();
  }
  



}

void loop() {
 /*for(int i=0; i<12; i++)
  digitalWrite(set_pin[i].pin_led, HIGH);
  delay(1000);*/
// put your main code here, to run repeatedly:
//  Serial.print(digitalRead(set_pin[stepNav].pin_sens));
//  Serial.print(" | ");
//  Serial.println(digitalRead(set_pin[5].pin_sens));
//}
//------------main program------------//
 Serial.print (next);
 Serial.print (" | ");
 Serial.print (digitalRead(next_btn));
 Serial.print (" | ");
 Serial.println (stepNav);
 
 
    if (digitalRead(jig_TG2)== LOW && next == true && ((stepNav >=4 ))){
      delay(100);
      count_TG2++;
      lcd.setCursor(0, 1);
      lcd.print("                ");
     // if(count_TG2!=3)
     // {
      lcd.setCursor(0, 0);
      lcd.print("<<TARIK GOYANG>>");
      lcd.setCursor(8, 1);
      lcd.print(count_TG2);
      //}
      if(count_TG2==3)
      {
      lcd.setCursor(0, 0);
      lcd.print("   AMBIL WIRE   ");
      lcd.setCursor(0, 1);
      lcd.print("                ");  
      }

     
      
      if((set_pin[stepNav].pin_led!=0))
      digitalWrite(set_pin[stepNav].pin_led, LOW);

      if((set_pin[stepNav].led_TG!=0))
      digitalWrite(set_pin[stepNav].led_TG, LOW);  
      stepNav++;

      
      
      if(stepNav==7)      
      next = false;
      Serial.println("OK");
      EEPROM.write(1, stepNav);
      
     
      if (stepNav < Nwire){
         if((set_pin[stepNav].pin_led!=0))
          {
          digitalWrite(set_pin[stepNav].pin_led, HIGH);
          
          } 
    
          if((set_pin[stepNav].led_TG!=0));
          digitalWrite(set_pin[stepNav].led_TG, HIGH);  
      }
    
      
         
      
      analogWrite(buzzer, 400);
      delay(300);
      analogWrite(buzzer, 0);
      while(digitalRead(jig_TG2)==LOW); 
      if (stepNav == Nwire)
      {
        finish();
      }
    }

    
    if (digitalRead(jig_TG1) == LOW && next == true && ((stepNav == 1 || stepNav == 2))){
      delay(100);
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
  
  
      digitalWrite(set_pin[stepNav].pin_led, LOW);
      digitalWrite(set_pin[stepNav].led_TG, LOW);
      stepNav++;
      lcd.setCursor(0, 1);
      lcd.print(disp_lcd[stepNav]);
      next = false;
      Serial.println("OK");
      EEPROM.write(1, stepNav);
  
      if (stepNav < Nwire){
       if(set_pin[stepNav].led_TG!=0);
       digitalWrite(set_pin[stepNav].led_TG, HIGH);
       digitalWrite(set_pin[stepNav].pin_led, HIGH);
      analogWrite(buzzer, 400);
      delay(300);
      analogWrite(buzzer, 0);
     }
    }
     
    if (digitalRead(next_btn) == LOW && next == true && (( stepNav ==0 || stepNav == 3))){
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");


    digitalWrite(set_pin[stepNav].pin_led, LOW);
    stepNav++;
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd[stepNav]);
    next = false;
    Serial.println("OK");
    EEPROM.write(1, stepNav);

      if (stepNav < Nwire)
      {
        if(set_pin[stepNav].pin_led!=0 && stepNav != 1)
        digitalWrite(set_pin[stepNav].pin_led, HIGH);
        else if(stepNav == 1)
        {
         // next = true;
          digitalWrite(set_pin[stepNav].pin_led, HIGH);
          digitalWrite(set_pin[stepNav].led_TG, HIGH);
        }
        else
        {
           next = true;
           digitalWrite(set_pin[stepNav].led_TG, HIGH);
        }
      }
    analogWrite(buzzer, 400);
    delay(300);
    analogWrite(buzzer, 0);
    }
    
 
    
  
  
  baca_nano();

 //  if (next == true) {
  running_program();
  //}

  if (wrongwire == true)
  {
    analogWrite(buzzer, 300);
  }
  
}

//------------main program----------//

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
    initial = true;
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd[stepNav]);
  }

}
//edited
