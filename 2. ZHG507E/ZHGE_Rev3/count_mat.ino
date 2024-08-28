void count_mat()
{
  lcd.setCursor(0, 0);
  lcd.print("MATERIAL EMPTY ?");
  lcd.setCursor(0, 1);
  lcd.print("NO           YES");

  //Serial.println(digitalRead(btn1));
  if (digitalRead(btn2) == LOW)
  {
    delay(10);
    //while (digitalRead(btn2) == LOW)
    sisa_mat[0] = EEPROM.read(10);
    sisa_mat[1] = EEPROM.read(20);
    sisa_mat[2] = EEPROM.read(30);
    sisa_mat[3] = EEPROM.read(40);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    String condisp= "Con:"+String(sisa_mat[0])+" Seal:"+String(sisa_mat[1]);
    lcd.setCursor(0, 1);
    lcd.print(condisp);
    initial_mat = true;
    delay(1000);
  }

  if (digitalRead(btn1) == LOW)
  {
    delay(10);
   // while (digitalRead(btn1) == LOW)
    EEPROM.write(20, 0);
    EEPROM.write(10, 0);
    EEPROM.write(30, 0);
    EEPROM.write(40, 0);
    sisa_mat[0] = 0;
    sisa_mat[1] = 0;
    sisa_mat[2] = 0;
    sisa_mat[3] = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" SISA MATERIAL= ");
    lcd.setCursor(8, 1);
    initial_mat = true;
    lcd.print("0");
    delay(1000);
  }  
}
