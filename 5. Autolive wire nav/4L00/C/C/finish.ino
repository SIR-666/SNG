void finish()
{
  lcd.setCursor(0, 0);
  lcd.print("<<  FINISH!!  >>");
  lcd.setCursor(0, 1);
  lcd.print("   HARNESS-OK   ");
  digitalWrite(buzzer, HIGH);
  for(int i=0; i<6; i++)
  {
  digitalWrite(pinled_TG[i],HIGH);  
  }
  delay(1000);
  digitalWrite(buzzer, LOW);

  for(int i=0; i<6; i++)
  {
  digitalWrite(pinled_TG[i],LOW);  
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<<  RUNNING!  >>");
  lcd.setCursor(0, 1);
  lcd.print("  TARIK G0YANG  ");
  digitalWrite(pinled_TG[0],HIGH);
}
