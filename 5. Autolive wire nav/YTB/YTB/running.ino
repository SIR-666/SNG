void partnum1() //200C
{
   
  for (int i = 0; i < Nwire-1; i++)
  {
    if (digitalRead(set_pin[urutan_200C[i]].pin_sens) == LOW)
    {
      delay(100);
      //while (digitalRead(set_pin[urutan_200C[i]].pin_sens) == LOW);
      analogWrite(buzzer, 250);
      delay(300);
      analogWrite(buzzer, 0);
        
      Serial.print(i);
      Serial.print(" | ");
      Serial.println(stepNav);
      if (i == stepNav)
      {
        
  nextStep = true;
        Serial.println("OK");
        EEPROM.write(1, stepNav);
        //wrongwire = false;
      }
      else
      {
        Serial.println("NG");
        wrongwire = true;
        digitalWrite(6,LOW);
        delay(500);
        digitalWrite(6,HIGH);
        lcd.setCursor(0, 0);
        lcd.print("<<  WARNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("   WRONG-WIRE   ");
      }
    }
  }

  
  
   if(nextStep == true && btnPressed == true)
   {
        digitalWrite(set_pin[urutan_200C[stepNav]].pin_led, LOW);
        stepNav++;
         
        if (stepNav < Nwire-1)
          digitalWrite(set_pin[urutan_200C[stepNav]].pin_led, HIGH);
          
        analogWrite(buzzer, 400);
        delay(300);
        analogWrite(buzzer, 0);

        if (stepNav == Nwire-1)
        {
          finish();
        }
        nextStep = false;
        btnPressed = false;     
   }
}


void partnum2() //100C
{
   

  for (int i = 0; i < Nwire2; i++)
  {
    if (digitalRead(set_pin[urutan_100C[i]].pin_sens) == LOW)
    {
      delay(100);
      //while (digitalRead(set_pin[urutan_100C[i]].pin_sens) == LOW);
      analogWrite(buzzer, 250);
      delay(300);
      analogWrite(buzzer, 0);
      
      Serial.print(i);
      Serial.print(" | ");
      Serial.println(stepNav);
      if (i == stepNav)
      {
        
  nextStep = true;
        Serial.println("OK");
        EEPROM.write(1, stepNav);
        //wrongwire = false;
      }
      else
      {
        Serial.println("NG");
        wrongwire = true;
        digitalWrite(6,LOW);
        delay(500);
        digitalWrite(6,HIGH);
        lcd.setCursor(0, 0);
        lcd.print("<<  WARNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("   WRONG-WIRE   ");
      }
    }
  }


  
   if(nextStep == true && btnPressed == true)
   {
        digitalWrite(set_pin[urutan_100C[stepNav]].pin_led, LOW);
        stepNav++;
         
        if (stepNav < Nwire2)
          digitalWrite(set_pin[urutan_100C[stepNav]].pin_led, HIGH);
          
        analogWrite(buzzer, 400);
        delay(300);
        analogWrite(buzzer, 0);

        if (stepNav == Nwire2)
        {
          finish();
        }
        nextStep = false;
        btnPressed = false;     
   }
}


void partnum_YTB() //YTB
{
   

  for (int i = 0; i < NwireYTB; i++)
  {
    if (digitalRead(set_pin[urutan_YTB[i]].pin_sens) == LOW)
    {
      delay(100);
      //while (digitalRead(set_pin[urutan_100C[i]].pin_sens) == LOW);
      analogWrite(buzzer, 250);
      delay(300);
      analogWrite(buzzer, 0);

      
      Serial.print(i);
      Serial.print(" | ");
      Serial.println(stepNav);
      
      if (i == stepNav)
      {
        if(stepNav == 2 || stepNav ==3)
        {
         lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print("<<TARIK GOYANG>>"); 
         }
         else
         {
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print("<<PUSH  BUTTON>>");
         }
        
        nextStep = true;
        Serial.println("OK");
        EEPROM.write(1, stepNav);
        //wrongwire = false;
      }
      else
      {
        Serial.println("NG");
        wrongwire = true;
        digitalWrite(6,LOW);
        delay(500);
        digitalWrite(6,HIGH);
        lcd.setCursor(0, 0);
        lcd.print("<<  WARNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("   WRONG!!!!!   ");
      }
    }
   
  }

  if(stepNav==3)
    {
      nextStep = true;
      Serial.println("OK");
      EEPROM.write(1, stepNav);  
      /*
      lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print("<<TARIK GOYANG>>"); 
          */
    }
  
   if(nextStep == true && btnPressed == true)
   {
        digitalWrite(set_pin[urutan_YTB[stepNav]].pin_led, LOW);
        stepNav++;
         
        if (stepNav < NwireYTB)
          digitalWrite(set_pin[urutan_YTB[stepNav]].pin_led, HIGH);
          
        analogWrite(buzzer, 400);
        delay(300);
        analogWrite(buzzer, 0);

        if (stepNav == NwireYTB)
        {
          finish();
        }
        nextStep = false;
        btnPressed = false;     
   }
}



void running_program() {
  for (int i = 0; i < Nwire; i++)
  {
    if (digitalRead(set_pin[i].pin_sens) == LOW)
    {
      delay(100);
      analogWrite(buzzer, 400);
      delay(300);
      analogWrite(buzzer, 0);
      //while (digitalRead(set_pin[i].pin_sens) == LOW);

      Serial.print(i);
      Serial.print(" | ");
      Serial.println(stepNav);
      if (i == stepNav)
      {

        next = true;
        wrongwire = false;
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("  PRESS BUTTON  ");



      }
      else
      {
        Serial.println("NG");
        wrongwire = true;
        digitalWrite(6, LOW);
        delay(500);
        digitalWrite(6, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("<<  WARNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("   WRONG-WIRE   ");
      }
    }
  }
}
