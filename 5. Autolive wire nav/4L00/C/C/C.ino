#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


#define jig_TG 22
#define buzzer A0

const int led_TG = 6;
const int pinled_TG[led_TG] = {32,33,34,35,36,37}; 
int count_TG = 0;


void setup() {
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

  for (int i = 0; i < led_TG; i++)
  { pinMode(jig_TG, INPUT_PULLUP);
    pinMode(pinled_TG[i], OUTPUT);
  }
  pinMode(buzzer,OUTPUT);

  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<  RUNNING!  >>");
  lcd.setCursor(0, 1);
  lcd.print("  TARIK G0YANG  ");
  digitalWrite(pinled_TG[0],HIGH);

}

void loop() {

  if(digitalRead(jig_TG)==LOW)
  {
    digitalWrite(pinled_TG[count_TG],LOW);
   count_TG++;
   lcd.setCursor(8, 1);
  lcd.print("                ");
   digitalWrite(pinled_TG[count_TG],HIGH);
  lcd.setCursor(0, 0);
  lcd.print("  TARIK G0YANG  ");
  lcd.setCursor(8, 1);
  lcd.print(count_TG);

  if(count_TG==6)
  {
    count_TG=0;
    finish();
   }
   delay(500);
   while(digitalRead(jig_TG)==LOW);
  Serial.print("  TARIK G0YANG  ");
    Serial.print(count_TG);
    Serial.println(" kali ");
  }
  
  /*
  for (int i = 0; i < led_TG; i++)
   digitalRead(pinled_TG);
   
  if (digitalRead(jig_TG)==HIGH){
    digitalWrite(pinled_TG,HIGH);
  }
  else {
    digitalWrite(pinled_TG,LOW);
    count_TG++;
    count_TG++;
  }
    Serial.print("  TARIK G0YANG  ");
    Serial.print(count_TG);
    Serial.println(" kali ");
    
  if (count_TG>=4){
   digitalWrite(pinled_TG, LOW);
   }
   */
}
  
      
     
        
