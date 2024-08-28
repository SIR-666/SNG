void next_step()
{
  if (partnum == "200C")
  {
    if (stepNav == 2 || stepNav == 3 )
    {
      if (digitalRead(jig_teta) == LOW && nextStep == true)//jig_teta
      {

        delay(100);
        if (digitalRead(jig_teta) == LOW);
        {
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print(step_200C[stepNav]);
        }
        btnPressed = true;

      }
    }
    else if (stepNav == 8 )
    { if (load == 0) {
        digitalWrite(lam1Jig2, HIGH);
        digitalWrite(lam2Jig2, LOW);
      }
      if (digitalRead(switch2) == LOW && nextStep == true) //&& nextStep == true
      {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("  TARIK GOYANG  ");
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        load = 1;
        digitalWrite(lam1Jig2, LOW);
        digitalWrite(lam2Jig2, HIGH);

      }
      delay(300);
      if (digitalRead(switch2) == LOW && load == 1)
      {
        //delay(1000);
        digitalWrite(lam1Jig2, LOW);
        digitalWrite(lam2Jig2, LOW);
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("  TARIK GOYANG  ");
        digitalWrite(buzzer, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        load = 0;
        //delay(100);
        if (digitalRead(jig_teta) == LOW );
        {
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print(step_200C[stepNav]);
        }
        btnPressed = true;

      }
    }
    else if (digitalRead(next_btn) == LOW && nextStep == true)
    {

      delay(100);
      if (digitalRead(next_btn) == LOW);
      {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(step_200C[stepNav]);
      }
      btnPressed = true;

    }

  }
  else
  {
    if (urutan_100C[stepNav] != 0 && urutan_100C[stepNav] != 1 && urutan_100C[stepNav] != 10 && urutan_100C[stepNav] != 6 )

    {
      if (digitalRead(next_btn) == LOW && nextStep == true)
      {

        delay(100);
        if (digitalRead(next_btn) == LOW);
        {
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print(step_100C[stepNav]);
        }
        btnPressed = true;

      }
    }
    else if (digitalRead(jig_teta) == LOW && nextStep == true)
    {

      delay(100);
      if (digitalRead(jig_teta) == LOW);
      {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(step_100C[stepNav]);

      }
      btnPressed = true;

    }
  }

}
