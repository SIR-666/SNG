void serialEvent()
{ //  Serial.println("cek");
  while (Serial2.available()) {
    char inChar = (char)Serial2.read();
    //Serial.print(inChar);
    if (inChar == '\n') {
      //datamasuk = inputString.substring(1);
      Serial.println(inputString);
      int len = inputString.length();
      Serial.println(len);
      if ((inputString == "2210247" || inputString == "2112W09") && misswire_rst == false)
      {
        misswire_rst = false;
        Serial.println("OK");
        rst = true;
        noTone(buzzer);
        //digitalWrite
        misswire = false;
        urutan = 0;
        Start_ = false;
        lock = false;
        // lcd.clear();
        misswire = false;
        misslock = false;
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print(" PASANG HARNESS ");
      }

      //DataProcess(inputString);
      inputString = "";
    }
    else {
      inputString += inChar;
    }
  }


}

void run_prog()
{
  if (digitalRead(tgt) == LOW)
  {
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    tarik_goyang = true;
    lcd.clear();
    lcd.setCursor(7, 1);
    lcd.print(step_pin[urutan].Stats);
    lcd.setCursor(0, 0);
    lcd.print(" WIRE TO TP PIN ");
  }
  else if(urutan>=7)
  {
    tarik_goyang = true;
  }

  digitalWrite(step_pin[urutan].pin_out, HIGH);
  digitalWrite(step_pin[urutan].pin_led, HIGH);
  for (int i = 0; i < n_wire; i++)
  {
    if (digitalRead(step_pin[i].pin_in) == HIGH && i == urutan && tarik_goyang == true)
    {
      tarik_goyang = false;
      lcd.clear();
      

      digitalWrite(step_pin[urutan].pin_led, LOW);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      digitalWrite(step_pin[urutan].pin_out, LOW);
      urutan++;

      if(urutan<7)
      {
      lcd.setCursor(0, 0);
      lcd.print("<<TARIK GOYANG>>");
      lcd.setCursor(7, 1);
      lcd.print(step_pin[urutan].Stats);
      }
      else
      {
      lcd.setCursor(7, 1);
      lcd.print(step_pin[urutan].Stats);
      lcd.setCursor(0, 0);
      lcd.print(" WIRE TO TP PIN ");
      }
      
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(1000);
      if (urutan == 10)
      {

        urutan = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("     FINISH     ");
        digitalWrite(buzzer, HIGH);
        digitalWrite(stamp, HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        digitalWrite(stamp, LOW);
        


        lcd.setCursor(0, 0);
        lcd.print("<<TARIK GOYANG>>");
        lcd.setCursor(7, 1);
        lcd.print(step_pin[urutan].Stats);
      }
    }
    else if (digitalRead(step_pin[i].pin_in) == HIGH)
    {
      if ((urutan == 3 && i == 7) || (urutan == 0 && i == 8))
        Serial.println("common");
      else
      {
        misswire = true;
        lcd.setCursor(0, 0);
        lcd.print("   WARNING!!!   ");
        lcd.setCursor(0, 1);
        lcd.print("    MISSWIRE    ");
      }
    }
  }

}
