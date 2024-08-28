void finish()
{
  lcd.setCursor(0, 0);
  lcd.print("<<  FINISH!!  >>");
  lcd.setCursor(0, 1);
  lcd.print("   HARNESS-OK   ");
  digitalWrite(buzzer, HIGH);
  for (int i = 0; i < Nwire; i++)
  {
    digitalWrite(set_pin[i].pin_led, HIGH);
  }
  delay(1000);
  for (int i = 0; i < Nwire; i++)
  {
    digitalWrite(set_pin[i].pin_led, LOW);
  }
  digitalWrite(buzzer, LOW);

  digitalWrite(buzzer, HIGH);
  for (int i = 0; i < Nwire; i++)
  {
    digitalWrite(set_pin[i].pin_led, HIGH);
  }
  delay(500);
  for (int i = 0; i < Nwire; i++)
  {
    digitalWrite(set_pin[i].pin_led, LOW);
  }
  digitalWrite(buzzer, LOW);
  stepNav = 0;
  EEPROM.write(1, stepNav);

  if(partnum == "200C")
  digitalWrite(set_pin[urutan_200C[0]].pin_led, HIGH);
  else
  digitalWrite(set_pin[urutan_100C[0]].pin_led, HIGH);
  
//digitalWrite(set_pin[0].pin_led, HIGH);
  lcd.print("<<  AUTOLIVE  >>");
  lcd.setCursor(0, 1);
  if(partnum == "200C")
  {
    lcd.print("      200C      ");
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print(step_200C[stepNav]); 
  }
  else
  {
    lcd.print("      100C      ");
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print(step_100C[stepNav]); 
  }
}
