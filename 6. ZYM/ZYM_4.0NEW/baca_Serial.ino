void baca_scanner()
{
    if (mySerial.available()) {
    char data = mySerial.read(); // Membaca data dari scanner

    if (data == '\n') {
      Serial.println(pn_mat); // Menambahkan baris baru di Serial Monitor
      String datasplit = splitValue(pn_mat,'|',1);
      if(datasplit==conn_pn)
      {
        material_wrong = false; 
        sisa_mat += 100; 
        EEPROM.write(10, sisa_mat);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SUPPLY - MATERIAL");
        lcd.setCursor(0, 1);
        lcd.print(conn_rmi);

        delay(1000);
        
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus]);
      }
      else if(datasplit==VT_PN[0])
      {
        material_wrong = false; 
        sisa_vt[0] += 100; 
        EEPROM.write(80, sisa_vt[0]);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SUPPLY - MATERIAL");
        lcd.setCursor(0, 1);
        lcd.print(VT_RMI[0]);

        delay(1000);
        
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus]);
      }
      else if(datasplit==VT_PN[1])
      {
        material_wrong = false; 
        sisa_vt[1] += 100; 
        EEPROM.write(90, sisa_vt[1]);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SUPPLY - MATERIAL");
        lcd.setCursor(0, 1);
        lcd.print(VT_RMI[1]);

        delay(1000);
        
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus]);
      }
      else
      {
        material_wrong = true; 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WRONG - MATERIAL");
        lcd.setCursor(0, 1);
        lcd.print(pn_mat);
      }
      
      pn_mat="";
    } else {
      pn_mat+=data;
      //Serial.print(data); // Menampilkan karakter dari scanner di Serial Monitor
    }
  }
}


void baca_esp() {
  if (Serial2.available() > 0)
  {
    char in_ = Serial2.read();
    //Serial.println(String(Serial2.read()));
    //char sn=in;
    //char sm = "";
    Serial.print(in_);
  
    if (in_ == '\n' )
    {
      //Serial.println (sm.length());
      //int lengtstring = sm.length();
      sm.remove(sm.length()-1,2);
     // Serial.println (sm);
     // Serial.println (sm.length());
    Serial.println(sm);

      for (int i = 0 ; i < 9; i++)
      {
        if (sm == idname[i])  {
        
        MISSWIRE = false;
        MISSLOC = false;
        material_wrong = false;
        EEPROM.write(50, 0);
        EEPROM.write(51, 0);
        noTone(Buzzer);
        Serial.println (sm);
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("                ");

        /*
        for(int i=0; i<Nwire; i++)
        {
        
        digitalWrite(set_pin[i].pin_led,LOW);
        if(set_pin[i].led_TG!=0)
        digitalWrite(set_pin[i].led_TG,LOW);
        }
        */
        CUR_T_STEP= millis();
        PREV_T_STEP = CUR_T_STEP;
        //EEPROM.write(1, 0);
        //stepNav = 0;
        //digitalWrite(set_pin[0].pin_led, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        initial = true;
        lcd.print(disp_lcd[cekstatus]);
        
        return sm="";

        

        
        }
        else{
          Serial.println("gabisa");
        }
      }
      sm = "";
    }
    else
    {
      sm += in_;
      //  Serial.println (sm);
    }

  }
}
