uint32_t step__ec(int flow, int sw_stat)
{
      int stat_ec=0;
      int detect_wire;
  digitalWrite(set_pin[flow].led_WIRE,HIGH);
  digitalWrite(set_pin[flow].led_TP,HIGH);
  digitalWrite(set_pin[flow].led_PJ,HIGH);
  
  detect_wire = sens_wire_read(flow);
 // Serial.println(detect_wire);
  if(detect_wire>0)
  {
    if((detect_wire-1) == flow)
    {
      digitalWrite(Buzzer,HIGH);
      delay(80);
      digitalWrite(Buzzer,LOW);
    WIRE_DETECT = true;
    //Serial.println("WIRE_DETECT OK");

     if( (flow==4) || (flow==5) )// 2&3
     {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print("   PUSH BUTTON  ");
     }
     else
     {
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      //lcd.print(disp_lcd[cekstatus+1]);
      lcd.print("  TARIK GOYANG  ");
     }
    }
    else if(MISSWIRE==false)
    {
      /*
    Serial.print(detect_wire);  
    Serial.print(" | ");  
    Serial.println(flow);  
    */
    lcd.setCursor(0, 1);
    lcd.print("    MISSWIRE    ");
    EEPROM.write(50, 1);
    Serial.print("MW|MW#");
    MISSWIRE = true;
    }  
  }

/*
  Serial.print(WIRE_DETECT);
  Serial.print(" | ");
  Serial.print(flow);
  Serial.print(" | ");
  Serial.println(Val_sw1);
  */
  
      
      digitalWrite(set_pin[i_TP].pin_out,HIGH);
     // delay(50);
      
      if(WIRE_DETECT==true && sw_stat ==1 && NGstats==false)
      { currentmilis = millis();
        if(currentmilis - prevmilis>10000)
        {
          NGstats = true;  
          currentmilis = millis();
          prevmilis = currentmilis;
          lcd.setCursor(0, 0);
          lcd.print("<<  RUNNING!  >>");
          lcd.setCursor(0, 1);
      //lcd.print(disp_lcd[cekstatus+1]);
          lcd.print("      NG        ");
          Serial.print("TIM|TIM#");
        }  
      }
      else
      {
        currentmilis = millis();
        prevmilis = currentmilis; 
      }
      
      if(((flow==2) || (flow==3)) && sw_stat ==1 && WIRE_DETECT==true) //ganti
      {
        currentmilis = millis();
        prevmilis = currentmilis; 
       // Serial.println("WIRE_LOC OK");
        stat_ec=1;  
        WIRE_DETECT=false;
        digitalWrite(set_pin[flow].led_WIRE,LOW);
        digitalWrite(set_pin[flow].led_TP,LOW);
        digitalWrite(set_pin[flow].led_PJ,LOW);
        Val_sw1=0;
        digitalWrite(set_pin[flow].pin_out,LOW);
        EEPROM.write(1, cekstatus+1);
        digitalWrite(Buzzer,HIGH);
        delay(80);
        digitalWrite(Buzzer,LOW);
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus+1]);
       // lcd.print("   PUSH BUTTON  ");
        return stat_ec;
      }
      else if(digitalRead(set_pin[flow].pin_in_TP)==HIGH && sw_stat ==1 && i_TP == flow && WIRE_DETECT==true)
      {
    //  Serial.println("WIRE_LOC OK");
      stat_ec=1;  
      digitalWrite(set_pin[flow].led_WIRE,LOW);
      digitalWrite(set_pin[flow].led_TP,LOW);
      digitalWrite(set_pin[flow].led_PJ,LOW);
      Val_sw1=0;
      digitalWrite(set_pin[flow].pin_out,LOW);
      EEPROM.write(1, cekstatus+1);
      digitalWrite(Buzzer,HIGH);
      delay(80);
      digitalWrite(Buzzer,LOW);
      WIRE_DETECT=false;
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(disp_lcd[cekstatus+1]);
      //lcd.print("  TARIK GOYANG  ");
      return stat_ec;
      }
      else if(digitalRead(set_pin[flow].pin_in_TP)==HIGH && sw_stat ==1 && i_TP!=flow && MISSLOC==false)
      {
       // Serial.println("MISSLOC");
        Serial.print("ML|ML#");
        /*
        Serial.print(i);
        Serial.print(" | ");  
        Serial.println(flow); 
        */
        digitalWrite(set_pin[i_TP].pin_out,LOW);
        lcd.setCursor(0, 1);
        lcd.print("    MISS-LOC    ");
        MISSLOC = true;
        EEPROM.write(51, 1);
        stat_ec = 0;
        return stat_ec;
        
      }
      
      
      
      //digitalWrite(set_pin[i].pin_out,LOW);
      currentTP=millis();
      if(currentTP - lastTP>=50)
      {
        lastTP=currentTP;
        digitalWrite(set_pin[i_TP].pin_out,LOW);
        i_TP++;
      }

      if(i_TP==Nwire)
      i_TP=0;

  return stat_ec;
  
}

void run_SNG()
{
    if((cekstatus==2) || (cekstatus==3)) //ganti
    {
      if( WIRE_DETECT==true)//digitalRead(BTN_NEXT)==LOW &&
      {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus]);
        digitalWrite(Buzzer,HIGH);
        delay(300);
        digitalWrite(Buzzer,LOW);
        while(digitalRead(BTN_NEXT)==LOW);  
       // Serial.println("PUSH BUTTON");
        //WIRE_DETECT=false;
        Val_sw1 = 1;
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus+1]);

//        if(cekstatus==10)
//        {
//        finish_step();
//        FINISH=false;
//        cekstatus=0;
//        Serial.println("FINISH OK");  
//        }
      }
    }
    else if(digitalRead(Sw1)==LOW && WIRE_DETECT==true)
      {
      digitalWrite(Buzzer,HIGH);
      delay(300);
      digitalWrite(Buzzer,LOW);
      while(digitalRead(Sw1)==LOW);  
      //Serial.println("TARIK GOYANG");
      //WIRE_DETECT=false;
      Val_sw1 = 1;
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(disp_lcd2[cekstatus+1]);
      
      }
    else if(digitalRead(Sw1)==LOW && WIRE_DETECT==false && NGstats==false)
    {
      NGstats = true;  
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      //lcd.print(disp_lcd[cekstatus+1]);
      lcd.print("      NG        ");
      Serial.print("TIM|TIM#");
    }
   // Serial.println(cekstatus);
    
    if(MISSWIRE == false && MISSLOC == false && NGstats == false)
    cekstatus =cekstatus + step__ec(cekstatus, Val_sw1);
    
    if(cekstatus==Nwire)
    {
      cekstatus++;
      FINISH=true;
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(" CEK LOCK CONN :");
        
      Serial.println("FINISH OK");
      CUR_T_STEP= millis();
      PREV_T_STEP = CUR_T_STEP;
    }

    if(FINISH==true)
      {
        
       // Serial.println("lock conn");
        if(digitalRead(lock_con)==LOW && NGstats==false)
        {
          Serial.print("FS|FS#");
          delay(50);
        //    if(digitalRead(lock_con)==LOW)
         //   {
                
                finish_step();
                cekstatus=0;
                EEPROM.write(1, 0);
                cekstatus = 0;
               // Serial.println("FINISH OK");  
                
                FINISH = false;
          //  }
        }
        else if(CUR_T_STEP-PREV_T_STEP>=10000 && NGstats==false)
        {
          CUR_T_STEP = millis();
          {
            
            Serial.print("TIM|TIM#");
  //          Serial.print(i);
  //          Serial.print(" | ");  
  //          Serial.println(flow); 
           // digitalWrite(set_pin[i].pin_out,HIGH);
            lcd.setCursor(0, 1);
            lcd.print("       NG       ");
            NGstats = true;
            //EEPROM.write(0, 1);
  //          stat_ec = 0;
            PREV_T_STEP = CUR_T_STEP;
            //return stat_ec;
          } 
        }  
      }

      if(MISSWIRE==true || MISSLOC == true || NGstats == true)
      {
          analogWrite(Buzzer,500);
         // misswire=0;
      }

}
