void jig_gonogo()
{
  if (NG_VT) {
    return;
  }

  if ((cekstatus == 3) && WIRE_DETECT == true)
  {
    if (digitalRead(sensJig1) == HIGH && digitalRead(sensJig2) == HIGH && digitalRead(sensJig3) == LOW)
    {
      int longdetect = 0;
      while ((digitalRead(sensJig1) == HIGH && digitalRead(sensJig2) == HIGH && digitalRead(sensJig3) == LOW))
      {
        if (digitalRead(sensJig1) == HIGH && digitalRead(sensJig2) == HIGH && digitalRead(sensJig3) == HIGH)
          longdetect = 0;
        //        lcd.clear();
        //        lcd.setCursor(0, 0);
        //        lcd.print("<<  RUNNING!  >>");
        //        lcd.setCursor(0, 1);
        //        lcd.print("<<   VT NG.   >>");
        longdetect++;
        delay(10);
        if (longdetect > 10)
        {
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print(disp_lcd[cekstatus]);
          digitalWrite(Buzzer, HIGH);
          delay(300);
          digitalWrite(Buzzer, LOW);
          while (digitalRead(BTN_NEXT) == LOW);
          // Serial.println("PUSH BUTTON");
          //WIRE_DETECT=false;
          Val_sw1 = 1;

          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print(disp_lcd[cekstatus + 1]);
          longdetect = 0;
        }
      }

    }
    if (digitalRead(sensJig1) == HIGH && digitalRead(sensJig2) == LOW && digitalRead(sensJig3) == LOW)
    {
      int longdetect = 0;
      while ((digitalRead(sensJig1) == HIGH && digitalRead(sensJig2) == LOW && digitalRead(sensJig3) == LOW))
      {
        if (digitalRead(sensJig1) == HIGH && digitalRead(sensJig2) == HIGH && digitalRead(sensJig3) == HIGH)
          longdetect = 0;
        //        lcd.clear();
        //        lcd.setCursor(0, 0);
        //        lcd.print("<<  RUNNING!  >>");
        //        lcd.setCursor(0, 1);
        //        lcd.print("<<   VT NG.   >>");
        longdetect++;
        delay(10);
        if (longdetect > 10)
        {

          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print("<<   VT NG.   >>");
          NG_VT = true;
          digitalWrite(Buzzer, HIGH);
        }
      }

    }
    if (digitalRead(sensJig1) == HIGH && digitalRead(sensJig2) == HIGH && digitalRead(sensJig3) == HIGH)
    {
      int longdetect = 0;
      while ((digitalRead(sensJig1) == HIGH && digitalRead(sensJig2) == HIGH && digitalRead(sensJig3) == HIGH))
      {
        longdetect++;
        delay(10);
        if (longdetect > 50)
        {
          NG_VT = true;
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print("<<   VT NG.   >>");
          digitalWrite(Buzzer, HIGH);
        }
      }

    }


  }
}
