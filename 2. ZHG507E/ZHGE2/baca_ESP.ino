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
