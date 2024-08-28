uint32_t step__ec(int flow, int sw_stat)
{
  int stat_ec = 0;
  int detect_wire;
  digitalWrite(set_pin[flow].led_WIRE, HIGH);
  digitalWrite(set_pin[flow].led_TP, HIGH);
  digitalWrite(set_pin[flow].led_PJ, HIGH);

  detect_wire = sens_wire_read(flow);
  // Serial.println(detect_wire);
  if (detect_wire > 0)
  {
    if ((detect_wire - 1) == flow)
    {
      digitalWrite(Buzzer, HIGH);
      delay(80);
      digitalWrite(Buzzer, LOW);
      WIRE_DETECT = true;
      //Serial.println("WIRE_DETECT OK");

      if ( (flow == 0) || (flow == 1) )
      {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("   PUSH BUTTON  ");
      }
      else
      {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        //lcd.print(disp_lcd[cekstatus+1]);
        lcd.print("  TARIK GOYANG  ");
      }
    }
    else if (MISSWIRE == false)
    {
      /*
        Serial.print(detect_wire);
        Serial.print(" | ");
        Serial.println(flow);
      */
      Serial.print("MW|MW#");
      lcd.setCursor(0, 1);
      lcd.print("    MISSWIRE    ");
      EEPROM.write(50, 1);
      MISSWIRE = true;
    }
  }

  /*
    Serial.print(WIRE_DETECT);
    Serial.print(" | ");
    Serial.print(flow);
    Serial.print(" | ");
    Serial.println(Val_sw1);
  */

  // for(int i=2; i<(Nwire+3); i++)
  //  {

  digitalWrite(set_pin[i_TP].pin_out, HIGH);
  // delay(50);
  //      Serial.print(currentmilis);
  //      Serial.print(" | ");
  //      Serial.println(prevmilis);
  if (WIRE_DETECT == true && sw_stat == 1 && NGstats == false)
  {
    currentmilis = millis();
    if (currentmilis - prevmilis > 6000)
    {
      NGstats = true;
      currentmilis = millis();
      prevmilis = currentmilis;
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      Serial.print("TIM|TIM#");
      //lcd.print(disp_lcd[cekstatus+1]);
      lcd.print("      NG        ");
    }
  }
  else
  {
    currentmilis = millis();
    prevmilis = currentmilis;
  }


  if (((flow == 0) || (flow == 1)) && sw_stat == 1 && WIRE_DETECT == true) //ganti
  {
    currentmilis = millis();
    prevmilis = currentmilis;
    //  Serial.println("WIRE_LOC OK");
    stat_ec = 1;
    WIRE_DETECT = false;
    digitalWrite(set_pin[flow].led_WIRE, LOW);
    digitalWrite(set_pin[flow].led_TP, LOW);
    digitalWrite(set_pin[flow].led_PJ, LOW);
    Val_sw1 = 0;
    digitalWrite(set_pin[flow].pin_out, LOW);
    EEPROM.write(1, cekstatus + 1);
    digitalWrite(Buzzer, HIGH);
    delay(80);
    digitalWrite(Buzzer, LOW);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd[cekstatus + 1]);
    // lcd.print("   PUSH BUTTON  ");
    return stat_ec;
  }
  else if (digitalRead(set_pin[flow].pin_in_TP) == HIGH && sw_stat == 1 && i_TP == flow && WIRE_DETECT == true)
  {
    currentmilis = millis();
    prevmilis = currentmilis;
    //  Serial.println("WIRE_LOC OK");
    stat_ec = 1;
    digitalWrite(set_pin[flow].led_WIRE, LOW);
    digitalWrite(set_pin[flow].led_TP, LOW);
    digitalWrite(set_pin[flow].led_PJ, LOW);
    Val_sw1 = 0;
    digitalWrite(set_pin[flow].pin_out, LOW);
    EEPROM.write(1, cekstatus + 1);
    digitalWrite(Buzzer, HIGH);
    delay(80);
    digitalWrite(Buzzer, LOW);
    WIRE_DETECT = false;
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd[cekstatus + 1]);
    //lcd.print("  TARIK GOYANG  ");
    return stat_ec;
  }
  else if (digitalRead(set_pin[flow].pin_in_TP) == HIGH && sw_stat == 1 && i_TP != flow && MISSLOC == false)
  {
    Serial.print("ML|ML#");
    /*
      Serial.print(i);
      Serial.print(" | ");
      Serial.println(flow);
    */
    digitalWrite(set_pin[i_TP].pin_out, LOW);
    lcd.setCursor(0, 1);
    lcd.print("    MISS-LOC    ");
    MISSLOC = true;
    EEPROM.write(51, 1);
    stat_ec = 0;
    return stat_ec;

  }




  currentTP = millis();
  if (currentTP - lastTP >= 50)
  {
    lastTP = currentTP;
    digitalWrite(set_pin[i_TP].pin_out, LOW);
    i_TP++;
  }

  if (i_TP == Nwire)
    i_TP = 2;

  return stat_ec;

}

void cek_error()
{
  if (MISSLOC == true)
  {
    lcd.setCursor(0, 1);
    lcd.print("    MISS-LOC    ");
  }
  else if (MISSWIRE == true)
  {
    lcd.setCursor(0, 1);
    lcd.print("    MISSWIRE    ");
  }
}

void run_SNG()
{
  if ((cekstatus == 0) || (cekstatus == 1) ) //ganti
  {
    if (digitalRead(BTN_NEXT) == LOW && WIRE_DETECT == true) //digitalRead(BTN_NEXT)==LOW &&
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

      //        if(cekstatus==10)
      //        {
      //        finish_step();
      //        FINISH=false;
      //        cekstatus=0;
      //        Serial.println("FINISH OK");
      //        }
    }
  }
  else if (digitalRead(Sw1) == LOW && WIRE_DETECT == true)
  {
    digitalWrite(Buzzer, HIGH);
    delay(300);
    digitalWrite(Buzzer, LOW);
    while (digitalRead(Sw1) == LOW);
    // Serial.println("TARIK GOYANG");
    //WIRE_DETECT=false;
    Val_sw1 = 1;
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd2[cekstatus + 1]);

  }
  else if (digitalRead(Sw1) == LOW && WIRE_DETECT == false && NGstats == false)
  {
    Serial.print("TIM|TIM#");
    NGstats = true;
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    //lcd.print(disp_lcd[cekstatus+1]);
    lcd.print("      NG        ");
    delay(1000);
  }
  // Serial.println(cekstatus);

  if (MISSWIRE == false && MISSLOC == false && material_wrong == false && NGstats == false)
    cekstatus = cekstatus + step__ec(cekstatus, Val_sw1);

  if (cekstatus == Nwire)
  {
    //cekstatus++;
    finish_step();
    cekstatus = 0;
    Serial.print("FS|FS#");
    sisa_mat[0] = sisa_mat[0] - 1;
    EEPROM.write(10, sisa_mat[0]);

    sisa_mat[1] = sisa_mat[1] - 1;
    EEPROM.write(20, sisa_mat[1]);

    sisa_mat[2] = sisa_mat[2] - 1;
    EEPROM.write(30, sisa_mat[2]);

    sisa_mat[3] = sisa_mat[3] - 1;
    EEPROM.write(40, sisa_mat[3]);

    for (int i = 0; i < Nwire; i++)
    {
      sisa_wire[i] = sisa_wire[i] - 1;
      EEPROM.write(100 + i, sisa_wire[i]);
    }
    //  Serial.println("lock_conn OK");

    FINISH = false;
  }



  if (MISSWIRE == true || MISSLOC == true || material_wrong == true || NGstats == true)
  {
    analogWrite(Buzzer, 500);


    // misswire=0;
  }

}
