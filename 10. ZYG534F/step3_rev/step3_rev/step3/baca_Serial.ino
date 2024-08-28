
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
      sm.remove(sm.length() - 1, 2);
      // Serial.println (sm);
      // Serial.println (sm.length());
      Serial.println(sm);

      for (int i = 0 ; i < 9; i++)
      {
        if (sm == idname[i])  {

          // misswire_rst = false;
          Serial.println("OK");
          //rst = true;
          noTone(buzzer);
          //digitalWrite
          misswire = false;
          //urutan = 0;
          //Start_ = false;
          //lock = false;
          // lcd.clear();
          //misswire = false;
          //misslock = false;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("<<TARIK GOYANG>>");
          lcd.setCursor(0, 1);
          lcd.print("                ");
          return sm = "";
          // lcd.setCursor(2, 0);
          //lcd.print(" PASANG HARNESS ");

        }
      }
      //inputString = "";
      sm = "";
    }
    else
    {
      //inputString += inChar;
      sm += in_;
      //  Serial.println (sm);
    }

  }
}
