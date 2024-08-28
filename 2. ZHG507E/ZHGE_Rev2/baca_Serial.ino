void baca_scanner()
{
    if (mySerial.available()) {
    char data = mySerial.read(); // Membaca data dari scanner

    if (data == '\n') {
      Serial.println(pn_mat); // Menambahkan baris baru di Serial Monitor
      String datasplit = splitValue(pn_mat,'|',1);
      if(datasplit==partnum_mat[0])
      {
        material_wrong = false; 
        sisa_mat[0] += 200; 
        EEPROM.write(10, sisa_mat[0]);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SUPPLY  MATERIAL");
        lcd.setCursor(0, 1);
        lcd.print(rmi_conv[0]);

        delay(1000);
        
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus]);
      }
      else if(datasplit==partnum_mat[1])
      {
        material_wrong = false; 
        sisa_mat[1] += 200; 
        EEPROM.write(20, sisa_mat[1]);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SUPPLY  MATERIAL");
        lcd.setCursor(0, 1);
        lcd.print(rmi_conv[1]);

        delay(1000);
        
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus]);
      }
      else if(datasplit==partnum_mat[2])
      {
        material_wrong = false; 
        sisa_mat[2] += 200; 
        EEPROM.write(30, sisa_mat[2]);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SUPPLY  MATERIAL");
        lcd.setCursor(0, 1);
        lcd.print(rmi_conv[2]);

        delay(1000);
        
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus]);
      }
      else if(datasplit==partnum_mat[3])
      {
        material_wrong = false; 
        sisa_mat[3] += 200; 
        EEPROM.write(40, sisa_mat[3]);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SUPPLY  MATERIAL");
        lcd.setCursor(0, 1);
        lcd.print(rmi_conv[3]);

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

void scan_tray()
{
    if (mySerial.available()) {
    char data = mySerial.read(); // Membaca data dari scanner

    if (data == '\n') {
      Serial.println(tray_pos); // Menambahkan baris baru di Serial Monitor
      String datasplit = splitValue(tray_pos,'|',1);
      int count_comp=0;
      for(int i=0; i<Nwire; i++)
      {
      if(datasplit==WIRESUPPLY[i].wire_tray)
      {
        count_comp++;
        tray_scan_stats[i]=true;
        tray_scan=true;
        //material_wrong = false; 
        //sisa_mat[0] += 200; 
        //EEPROM.write(10, sisa_mat[0]);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  POSISI  TRAY  ");
        lcd.setCursor(0, 1);
        lcd.print(WIRESUPPLY[i].wire_tray);

        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" SCAN WIP WIRE: ");
        lcd.setCursor(0, 1);
        lcd.print("                ");

      }
      
      
      }
      
      if(count_comp==0)
      {
       material_wrong = true; 
        count_comp=0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("   SCAN TRAY   ");
        lcd.setCursor(0, 1);
        lcd.print("  WRONG - TRAY  ");  
      }
      count_comp=0;
      tray_pos="";
    } else {
      tray_pos+=data;
      //Serial.print(data); // Menampilkan karakter dari scanner di Serial Monitor
    }
  }
}

void wire_scann()
{
    if (mySerial.available()) {
    char data = mySerial.read(); // Membaca data dari scanner

    if (data == '\n') {
      Serial.println(wire_skema); // Menambahkan baris baru di Serial Monitor
      String datasplit = splitValue(wire_skema,'.',1);

      for(int i=0; i<Nwire; i++)
      {
          if(tray_scan_stats[i]==true)
          {
            if(datasplit==WIRESUPPLY[i].wire_skm)
            {
              tray_scan=false;
              tray_scan_stats[i]=false;
              material_wrong = false; 
              sisa_wire[i] += 200; 
              EEPROM.write(200+i, sisa_wire[i]);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("  SUPPLY  WIRE  ");
              lcd.setCursor(0, 1);
              lcd.print(WIRESUPPLY[i].wire_skm);
      
              delay(1000);

              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("   SCAN TRAY   ");
              lcd.setCursor(0, 1);
              lcd.print("                ");
              break;
            }
            else
            {
              material_wrong = true; 
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("  WRONG - WIRE  ");
              lcd.setCursor(0, 1);
              lcd.print(WIRESUPPLY[i].wire_skm);
              delay(1000);
              break;
            }
            
          }
      }
      
      
      wire_skema="";
    } else {
      wire_skema+=data;
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
        if(MISSLOC == true)
        {
          cekstatus=0;  
          for (int i = 0; i < Nwire; i++)
          {
            digitalWrite(set_pin[i].led_WIRE, LOW);
            digitalWrite(set_pin[i].led_TP, LOW);
            digitalWrite(set_pin[i].led_PJ, LOW);
          }
          cekstatus=0; 
          WIRE_DETECT=false;
          Val_sw1 =0;
          digitalWrite(set_pin[0].led_WIRE, HIGH);
        }
        
        NGstats = false;
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
        currentmilis = millis();
        prevmilis = currentmilis; 
        /*
        for(int i=0; i<Nwire; i++)
        {
        
        digitalWrite(set_pin[i].pin_led,LOW);
        if(set_pin[i].led_TG!=0)
        digitalWrite(set_pin[i].led_TG,LOW);
        }
        */
        
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
          //Serial.println("gabisa");
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
