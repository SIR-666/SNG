void baca_nano() {
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
        
        wrongwire = false;
        noTone(buzzer);
        Serial.println (sm);
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("                ");
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
