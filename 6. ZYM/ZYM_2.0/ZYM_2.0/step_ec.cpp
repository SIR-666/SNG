#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "step_ec.h"
#include "PCF8575.h"
PCF8575 Sensor1 (0x24);
PCF8575 LED_P1 (0x21);
PCF8575 LED_T1 (0x20);


uint32_t run_ec::step__ec(int flow, int step_)
{
      
  
  digitalWrite(set_pin[flow].pin_out,HIGH);
  LED_P1.digitalWrite(set_pin[flow].led1,LOW);
  LED_P1.digitalWrite(set_pin[flow].nav,LOW);
  LED_T1.digitalWrite(set_pin[flow].led2, LOW);

  if(digitalRead(set_pin[flow].pin_in)==HIGH)
  status_ec = flow + 1;
  else
  status_ec = 0;

  return status_ec;
  
}
