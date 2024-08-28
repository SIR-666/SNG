



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
       // wrongwire = false;
          if ( (stepNav >= 2 &&  stepNav <= 7 ) )
          {
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print("  TARIK GOYANG  ");
          } 
        else if ((stepNav <2 || stepNav == 8))
        {
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print("  PRESS PEDAL   ");
        }
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
