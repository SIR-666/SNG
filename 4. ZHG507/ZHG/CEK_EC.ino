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

     if( (flow==0)  )
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
    else
    {
    Serial.print(detect_wire);  
    Serial.print(" | ");  
    Serial.println(flow);  
    lcd.setCursor(0, 1);
    lcd.print("    MISSWIRE    ");
    EEPROM.write(50, 1);
    MISSWIRE = true;
    }  
  }

  Serial.print(WIRE_DETECT);
  Serial.print(" | ");
  Serial.print(flow);
  Serial.print(" | ");
  Serial.println(Val_sw1);
  for(int i=1; i<Nwire+2; i++)
  {
      
      digitalWrite(set_pin[i].pin_out,HIGH);
     // delay(50);
      
      
      
      if(((flow==0)) && sw_stat ==1 && WIRE_DETECT==true) //ganti
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
      else if(digitalRead(set_pin[flow].pin_in_TP)==HIGH && sw_stat ==1 && i == flow && WIRE_DETECT==true)
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
      else if(digitalRead(set_pin[flow].pin_in_TP)==HIGH && sw_stat ==1 && i!=flow)
      {
        Serial.println("MISSLOC");
        Serial.print(i);
        Serial.print(" | ");  
        Serial.println(flow); 
        digitalWrite(set_pin[i].pin_out,LOW);
        lcd.setCursor(0, 1);
        lcd.print("    MISS-LOC    ");
        EEPROM.write(51, 1);
        MISSLOC = true;
        stat_ec = 0;
        return stat_ec;
        
      }
      
      
      
      digitalWrite(set_pin[i].pin_out,LOW);
  }

  return stat_ec;
  
}

void cek_error()
{
  if(MISSLOC==true)
  {
    lcd.setCursor(0, 1);
    lcd.print("    MISS-LOC    ");  
  }
  else if(MISSWIRE==true)
  {
    lcd.setCursor(0, 1);
    lcd.print("    MISSWIRE    ");  
  }  
}

void run_SNG()
{
    if((cekstatus==0) ) //ganti
    {
      if(digitalRead(BTN_NEXT)==LOW && WIRE_DETECT==true)
      {
        lcd.setCursor(0, 0);
        lcd.print("<<  RUNNING!  >>");
        lcd.setCursor(0, 1);
        lcd.print(disp_lcd[cekstatus]);
        digitalWrite(Buzzer,HIGH);
        delay(300);
        digitalWrite(Buzzer,LOW);
        while(digitalRead(BTN_NEXT)==LOW);  
        Serial.println("PUSH BUTTON");
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
    
    if(cekstatus==Nwire)
    {
      finish_step();
      FINISH=false;
      cekstatus=0;
      Serial.println("FINISH OK");
      sisa_mat[0]=sisa_mat[0]-1;
      EEPROM.write(10, sisa_mat[0]);
    }

      if(MISSWIRE==true || MISSLOC == true)
      {
          analogWrite(Buzzer,500);
         // misswire=0;
      }

}
