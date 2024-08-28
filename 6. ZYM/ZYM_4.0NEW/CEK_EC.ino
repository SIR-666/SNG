uint32_t step__ec(int flow, int sw_stat)
{
  int stat_ec = 0;
  int detect_wire;
  digitalWrite(set_pin[flow].led_WIRE, HIGH);
  digitalWrite(set_pin[flow].led_TP, HIGH);
  digitalWrite(set_pin[flow].led_PJ, HIGH);

  detect_wire = sens_wire_read(flow);
  // Serial.println(detect_wire);
  if ((flow == 4 || flow == 5) && WIRE_DETECT == false)
  {
    WIRE_DETECT = true;
    Serial.println("WIRE_DETECT OK");
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    //lcd.print(disp_lcd[cekstatus+1]);
    lcd.print("  TARIK GOYANG  ");
  }
  else if (detect_wire > 0)
  {
    if ((detect_wire - 1) == flow)
    {
      digitalWrite(Buzzer, HIGH);
      delay(80);
      digitalWrite(Buzzer, LOW);
      WIRE_DETECT = true;
      Serial.println("WIRE_DETECT OK");

      if ( (flow < 4) )
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
    else
    {
      Serial.print(detect_wire);
      Serial.print(" | ");
      Serial.println(flow);
      lcd.setCursor(0, 1);
      lcd.print("    MISSWIRE    ");
      MISSWIRE = true;
      EEPROM.write(0, 1);
    }
  }

  Serial.print(WIRE_DETECT);
  Serial.print(" | ");
  Serial.print(flow);
  Serial.print(" | ");
  Serial.println(Val_sw1);
  for (int i = 0; i < Nwire; i++)
  {

    digitalWrite(set_pin[i].pin_out, LOW);
    // delay(50);



    if (((flow < 4)) && sw_stat == 1 && WIRE_DETECT == true) //ganti
    {
      Serial.println("WIRE_LOC OK");
      stat_ec = 1;
      WIRE_DETECT = false;
      digitalWrite(set_pin[flow].led_WIRE, LOW);
      digitalWrite(set_pin[flow].led_TP, LOW);
      digitalWrite(set_pin[flow].led_PJ, LOW);
      Val_sw1 = 0;
      digitalWrite(set_pin[flow].pin_out, HIGH);
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
    else if (digitalRead(set_pin[flow].pin_in_TP) == LOW && sw_stat == 1 && i == flow && WIRE_DETECT == true)
    {
      Serial.println("WIRE_LOC OK");
      stat_ec = 1;
      digitalWrite(set_pin[flow].led_WIRE, LOW);
      digitalWrite(set_pin[flow].led_TP, LOW);
      digitalWrite(set_pin[flow].led_PJ, LOW);
      Val_sw1 = 0;
      digitalWrite(set_pin[flow].pin_out, HIGH);
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
    else if (digitalRead(set_pin[flow].pin_in_TP) == LOW && sw_stat == 1 && i != flow)
    {
      Serial.println("MISSLOC");
      Serial.print(i);
      Serial.print(" | ");
      Serial.println(flow);
      digitalWrite(set_pin[i].pin_out, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("    MISS-LOC    ");
      MISSLOC = true;
      EEPROM.write(0, 1);
      stat_ec = 0;
      return stat_ec;

    }
    else if (flow == 4 && sw_stat == 1 && WIRE_DETECT == true)
    {
      Serial.println("WIRE_LOC OK");
      stat_ec = 1;
      WIRE_DETECT = false;
      digitalWrite(set_pin[flow].led_WIRE, LOW);
      digitalWrite(set_pin[flow].led_TP, LOW);
      digitalWrite(set_pin[flow].led_PJ, LOW);
      Val_sw1 = 0;
      digitalWrite(set_pin[flow].pin_out, HIGH);
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
    else if (sw_stat == 1 && WIRE_DETECT == true && (cekstatus <= Nwire))
    {
      Serial.print(CUR_T_STEP);
      Serial.print("  ");
      Serial.println(PREV_T_STEP);
      CUR_T_STEP = millis();
      if (CUR_T_STEP - PREV_T_STEP >= 15000)
      {

        Serial.println("MISSLOC");
        Serial.print(i);
        Serial.print(" | ");
        Serial.println(flow);
        digitalWrite(set_pin[i].pin_out, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("       NG       ");
        MISSLOC = true;
        EEPROM.write(0, 1);
        stat_ec = 0;
        PREV_T_STEP = CUR_T_STEP;
        return stat_ec;
      }

    }
    else if (cekstatus <= Nwire)
    {
      //        Serial.print(CUR_T_STEP);
      //        Serial.print("  ");
      //        Serial.println(PREV_T_STEP);
      CUR_T_STEP = millis();
      PREV_T_STEP = CUR_T_STEP;
    }





    digitalWrite(set_pin[i].pin_out, HIGH);
  }

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
  if ((cekstatus < 4)) //ganti
  {
    if (digitalRead(BTN_NEXT) == LOW && WIRE_DETECT == true)
    {
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(disp_lcd[cekstatus]);
      digitalWrite(Buzzer, HIGH);
      delay(200);
      digitalWrite(Buzzer, LOW);
      while (digitalRead(BTN_NEXT) == LOW);
      Serial.println("PUSH BUTTON");
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
  else
  {
    if (digitalRead(Sw1) == LOW && WIRE_DETECT == true)
    {
      digitalWrite(Buzzer, HIGH);
      delay(300);
      digitalWrite(Buzzer, LOW);
      while (digitalRead(Sw1) == LOW);
      Serial.println("TARIK GOYANG");
      //WIRE_DETECT=false;
      Val_sw1 = 1;
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(disp_lcd2[cekstatus + 1]);

    }
  }

  //Serial.println(cekstatus);

  if (MISSWIRE == false && MISSLOC == false && material_wrong == false)
  {
    cekstatus = cekstatus + step__ec(cekstatus, Val_sw1);

    if (cekstatus == Nwire)
    {
      cekstatus++;
      FINISH = true;
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(" CEK LOCK CONN :");

      Serial.println("FINISH OK");
      CUR_T_STEP = millis();
      PREV_T_STEP = CUR_T_STEP;

    }

    if (FINISH == true)
    {

      Serial.println("locki conn");
      if (digitalRead(lock_con) == LOW)
      {
        delay(50);
        //    if(digitalRead(lock_con)==LOW)
        //   {
        //
        delay(1000);
        digitalWrite(Buzzer, HIGH);
        digitalWrite(relay1, HIGH);
        delay(100);
        digitalWrite(relay1, LOW);
        digitalWrite(Buzzer, LOW);
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("ASSEMBLY PROCESS");

        Serial.println("lock_conn OK");
        lock = true;
        FINISH = false;
        //  }
      }
      else
      {
        CUR_T_STEP = millis();
        if (CUR_T_STEP - PREV_T_STEP >= 15000)
        {

          Serial.println("MISSLOC");
          //          Serial.print(i);
          //          Serial.print(" | ");
          //          Serial.println(flow);
          // digitalWrite(set_pin[i].pin_out,HIGH);
          lcd.setCursor(0, 1);
          lcd.print("       NG       ");
          MISSLOC = true;
          EEPROM.write(0, 1);
          //          stat_ec = 0;
          PREV_T_STEP = CUR_T_STEP;
          //return stat_ec;
        }
      }
    }

    if (lock == true)
    {
      if (digitalRead(assy_LS1) == LOW)
      {
        delay(50);
        if (digitalRead(assy_LS1) == LOW)
        {
          Serial.println("LS Assy 1");
          // finish_step();
          // sisa_mat=sisa_mat-1;
          // EEPROM.write(10, sisa_mat);
          //   cekstatus=0;
          //lock = true;
          // FINISH = false;
          assy_stats[0] = 1;
        }
      }

      if (digitalRead(assy_LS2) == LOW)
      {
        delay(50);
        if (digitalRead(assy_LS2) == LOW)
        {
          Serial.println("LS Assy 2");
          // finish_step();
          // sisa_mat=sisa_mat-1;
          // EEPROM.write(10, sisa_mat);
          //   cekstatus=0;
          //lock = true;
          // FINISH = false;
          assy_stats[1] = 1;
        }
      }

      if (assy_stats[0] == 1 && assy_stats[1] == 1)
      {
        finish_step();
        Serial.println("ASSY FINISH");
        sisa_mat = sisa_mat - 1;
        EEPROM.write(10, sisa_mat);
        cekstatus = 0;
        lock = false;
        assy_stats[1] = 0;
        assy_stats[0] = 0;

      }

    }

  }
  if (MISSWIRE == true || MISSLOC == true || material_wrong == true )
  {
    analogWrite(Buzzer, 500);
    // misswire=0;
  }

}
