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
    while (digitalRead(btn2) == LOW)
    sisa_mat = EEPROM.read(10);
    sisa_vt[0] = EEPROM.read(80);
    sisa_vt[1] = EEPROM.read(90);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(8, 1);
    lcd.print(sisa_mat);
    initial_mat = true;
    delay(1000);
  }

  if (digitalRead(btn1) == LOW)
  {
    delay(10);
    while (digitalRead(btn1) == LOW)
    EEPROM.write(10, 0);
    EEPROM.write(80, 0);
    EEPROM.write(90, 0);
    sisa_mat = 0;
    sisa_vt[0]=0;
    sisa_vt[1]=0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" SISA MATERIAL= ");
    lcd.setCursor(8, 1);
    initial_mat = true;
    lcd.print("0");
    delay(1000);
  }  
}
