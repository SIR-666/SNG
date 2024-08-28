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
  digitalWrite(set_pin[0].pin_led, HIGH);
  lcd.print("<<    4L00    >>");
  lcd.setCursor(0, 1);
  lcd.print("<<  RUNNING!  >>");
}
