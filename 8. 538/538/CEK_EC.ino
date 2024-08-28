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
    Serial.println("WIRE_DETECT OK");

      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      //lcd.print(disp_lcd[cekstatus+1]);
      lcd.print("  TARIK GOYANG  ");
     
    }
    else //if(((detect_wire-1)!=6 && flow!=7) && ((detect_wire-1)!=7 && flow!=6))
    {
    Serial.print(detect_wire);  
    Serial.print(" | ");  
    Serial.println(flow);  
    lcd.setCursor(0, 1);
    lcd.print("    MISSWIRE    ");
    MISSWIRE = true;
    }  
  }
  else if(flow==7 && WIRE_DETECT==false)
  {
    Serial.println("WIRE_DETECT OK");

      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      //lcd.print(disp_lcd[cekstatus+1]);
      lcd.print("  TARIK GOYANG  ");
      WIRE_DETECT = true;
  }

  Serial.print(WIRE_DETECT);
  Serial.print(" | ");
  Serial.print(flow);
  Serial.print(" | ");
  Serial.println(Val_sw1);
  for(int i=0; i<Nwire; i++)
  {
      
      digitalWrite(set_pin[i].pin_out,HIGH);
     // delay(50);
      
      
      /*
      if(((flow==0) || (flow==9) || (flow==10)) && sw_stat ==1 && WIRE_DETECT==true) //ganti
      {
        Serial.println("WIRE_LOC OK");
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
      else 
      */
      if(digitalRead(set_pin[flow].pin_in_TP)==HIGH && sw_stat ==1 && i == flow && WIRE_DETECT==true)
      {
      Serial.println("WIRE_LOC OK");
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
      else if(digitalRead(set_pin[flow].pin_in_TP)==HIGH && sw_stat ==1 && i!=flow && ((i!=6 && flow!=7) && (i!=7 && flow!=6)) )
      {
       if((i!=6 && flow!=7) && (i!=7 && flow!=6))
       {
        Serial.println("MISSLOC");
        Serial.print(i);
        Serial.print(" | ");  
        Serial.println(flow); 
        digitalWrite(set_pin[i].pin_out,LOW);
        lcd.setCursor(0, 1);
        lcd.print("    MISS-LOC    ");
        MISSLOC = true;
        stat_ec = 0;
        return stat_ec;
       }
        
        
      }
      
      
      
      digitalWrite(set_pin[i].pin_out,LOW);
  }

  return stat_ec;
  
}

void run_SNG()
{
    if((cekstatus<=4)) //ganti
    {
      if(digitalRead(Sw2)==LOW && WIRE_DETECT==true)
      {
        
      
        digitalWrite(Buzzer,HIGH);
        delay(300);
        digitalWrite(Buzzer,LOW);
        while(digitalRead(BTN_NEXT)==LOW);  
        Serial.println("TARIK GOYANG");
        //WIRE_DETECT=false;
        Val_sw1 = 1;

        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd2[cekstatus+1]);

//        if(cekstatus==10)
//        {
//        finish_step();
//        FINISH=false;
//        cekstatus=0;
//        Serial.println("FINISH OK");  
//        }
      }
    }
    else if(cekstatus==7 && WIRE_DETECT==true)
    {
    Val_sw1 = 1;
    lcd.setCursor(0, 0);
    lcd.print("<<  RUNNING!  >>");
    lcd.setCursor(0, 1);
    lcd.print(disp_lcd2[cekstatus+1]);
    }
    else
    {
      if(digitalRead(Sw1)==LOW && WIRE_DETECT==true)
      {
      digitalWrite(Buzzer,HIGH);
      delay(300);
      digitalWrite(Buzzer,LOW);
      while(digitalRead(Sw1)==LOW);  
      Serial.println("TARIK GOYANG");
      //WIRE_DETECT=false;
      Val_sw1 = 1;
      lcd.setCursor(0, 0);
      lcd.print("<<  RUNNING!  >>");
      lcd.setCursor(0, 1);
      lcd.print(disp_lcd2[cekstatus+1]);
      
      }
      }
   // Serial.println(cekstatus);
    
    if(MISSWIRE == false && MISSLOC == false)
    cekstatus =cekstatus + step__ec(cekstatus, Val_sw1);

    if(cekstatus==5 && stamp_ok==false)
    {
    stamp_ok=true;  
    digitalWrite(Buzzer,HIGH);
      digitalWrite(relay2,HIGH);
      delay(300);
      digitalWrite(relay2,LOW);
      digitalWrite(Buzzer,LOW);
    }


    
    if(cekstatus==Nwire)
    {
      stamp_ok=false;  
      finish_step();
      FINISH=false;
      cekstatus=0;
      Serial.println("FINISH OK");
    }

      if(MISSWIRE==true || MISSLOC == true)
      {
          analogWrite(Buzzer,500);
         // misswire=0;
      }

}