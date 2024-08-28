void next_step()
{
  
    if((stepNav != 2) &&  (stepNav != 3))
    {
      if (digitalRead(next_btn) == LOW && nextStep == true) 
      {
        
        delay(100);
        if(digitalRead(next_btn)==LOW)
        {
        btnPressed = true;

        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(step_YTB[stepNav+1]);
        }
  
      }
    }
    else if (digitalRead(jig_teta) == LOW && nextStep == true) 
      {
  
      delay(100);
      if(digitalRead(jig_teta)==LOW)
      {
      btnPressed = true;
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(step_YTB[stepNav+1]);

      if(stepNav==2)
        {
          delay(300);     
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
          lcd.print("<<TARIK GOYANG>>"); 
          
          }
      }

      
  
      } 
      
  
   
}
