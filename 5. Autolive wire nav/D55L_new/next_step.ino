void next_step()
{
  if(partnum == "200C")
  {
    if(stepNav==2 || stepNav==3 )
    {
      if (digitalRead(next_btn) == LOW && nextStep == true) 
      {
  
      delay(100);
      if(digitalRead(next_btn)==LOW);
      {
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(step_200C[stepNav]);
      }
      btnPressed = true;
  
      }
    }
    else
    if (digitalRead(jig_teta) == LOW && nextStep == true) 
      {
  
      delay(100);
      if(digitalRead(jig_teta)==LOW);
      {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(step_200C[stepNav]);
      }
      btnPressed = true;
  
      }
     
  }
  else
  {
    if(urutan_100C[stepNav] != 0 && urutan_100C[stepNav] != 1 && urutan_100C[stepNav] != 10 && urutan_100C[stepNav] != 6 )
   
    {
      if (digitalRead(next_btn) == LOW && nextStep == true) 
      {
  
      delay(100);
      if(digitalRead(next_btn)==LOW);
      {
       lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(step_100C[stepNav]); 
      }
      btnPressed = true;
  
      }
    }
    else
    if (digitalRead(jig_teta) == LOW && nextStep == true) 
      {
  
      delay(100);
      if(digitalRead(jig_teta)==LOW);
      {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(step_100C[stepNav]);
        
      }
      btnPressed = true;
  
      } 
  }
   
}
