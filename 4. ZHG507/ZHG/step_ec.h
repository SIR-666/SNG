#ifndef step_ec_h
#define step_ec_h

#include <Arduino.h>
#include "PCF8575.h"

class run_ec {
  private:
    int ledPin;
    int status_ec=0;
    unsigned char ledState;
    struct pinset{
      int pin_in;
      int pin_out;
      const int led1;
      const int led2;
      const int nav;
      int numstep;
      };

   pinset set_pin[7] = {
   {4,19,P13,P7,P8,1},
   {4,17,P13,P6,P8,1},
   {6,15,P14,P5,P0,1},
   {12,3,P15,0,P9,2},
   {10,5,P6,P1,P10,2},
   {16,7,P5,P2,P11,2},
   {18,9,P7,P3,P12,2},
   };
  public:
    /*
    LED(int pin);
    void turnON();
    void turnOFF();
    int getState();
    */
    uint32_t step__ec(int flow, int step_);
};

#endif
