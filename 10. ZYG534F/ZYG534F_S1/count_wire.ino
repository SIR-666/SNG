
void count_wire()
{
  lcd.setCursor(0, 0);
  lcd.print("  WIRE EMPTY ?  ");
  lcd.setCursor(0, 1);
  lcd.print("NO           YES");

  //Serial.println(digitalRead(btn1));
  if (digitalRead(btn2) == LOW)
  {
    delay(10);
   // while (digitalRead(btn2) == LOW)
    sisa_wire[0] = EEPROM.read(100);
    sisa_wire[1] = EEPROM.read(101);
    sisa_wire[2] = EEPROM.read(102);
    sisa_wire[3] = EEPROM.read(103);
    sisa_wire[4] = EEPROM.read(104);
    sisa_wire[5] = EEPROM.read(105);
    sisa_wire[6] = EEPROM.read(106);
    sisa_wire[7] = EEPROM.read(107);
    sisa_wire[8] = EEPROM.read(108);
    sisa_wire[9] = EEPROM.read(109);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    //String condisp= "Con:"+String(sisa_mat[0])+" Seal:"+String(sisa_mat[1]);
    lcd.setCursor(0, 1);
    lcd.print(" WIRE AVAILABLE ");
    initial_wire = true;
    delay(1000);
  }

  if (digitalRead(btn1) == LOW)
  {
    delay(10);
  //  while (digitalRead(btn1) == LOW)
    EEPROM.write(100, 0);
    EEPROM.write(101, 0);
    EEPROM.write(102, 0);
    EEPROM.write(103, 0);
    EEPROM.write(104, 0);
    EEPROM.write(105, 0);
    EEPROM.write(106, 0);
    EEPROM.write(107, 0);
    EEPROM.write(108, 0);
    sisa_wire[0] = 0;
    sisa_wire[1] = 0;
    sisa_wire[2] = 0;
    sisa_wire[3] = 0;
    sisa_wire[4] = 0;
    sisa_wire[5] = 0;
    sisa_wire[6] = 0;
    sisa_wire[7] = 0;
    sisa_wire[8] = 0;
    sisa_wire[9] = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   SISA WIRE=   ");
    lcd.setCursor(0, 1);
    initial_wire = true;
    lcd.print("       0        ");
    delay(1000);
  }  
}
