/*
ROW1 ... ROW3 sind die aktiven Kanäle, COL1 .... COL5 sind die Sensoren
Eine Reihe wird aktiviert, indem sie auf Null gesetzt wird -> ROWx_OFF
In der Spalte COLx liegt dann ein Null-Pegel an
*/

#include "TastaturScanner.h"
#include "ledHardware.h"

#define NUM_ROWS 3 0b00101010

bool checkTastatur()
{
  if(((~COLUMN_PORT.IN) & 0b11010101)  > 0) // wenn überhaupt eine Taste gedrückt ist ...
  {
    if(TS_Status == TS_INACTIVE) // ... und bisher keine gedrückt war
    {
      ROW2_ON;
      ROW3_ON;
      keyPressed = 255;
      TS_Status++;
      return(true);
    }
    else
      return(false);
  }
  else
    return(false);

}

void TastaturScanner()
{
  static uint8_t tempKey;
  switch(TS_Status)
  {
    case TS_ROW1:
      tempKey = getKeyPressed(0);
      ROW1_ON;
      ROW2_OFF;
      if (tempKey != 255)
      {
        TS_Status = TS_STOP1;
        LEDGRUEN_TAST_ON;
      }
      else
        TS_Status++;
    break;
    case TS_ROW2:
      tempKey = getKeyPressed(1);
      ROW2_ON;
      ROW3_OFF;
      if (tempKey != 255)
      {
        TS_Status = TS_STOP1;
        LEDROT_TAST_ON;
      }
      else
        TS_Status++;
    break;
    case TS_ROW3:
      tempKey = getKeyPressed(2);
      LEDROT_TAST_ON;
      LEDGRUEN_TAST_ON;
      TS_Status++;
    break;
    case TS_STOP1:
      ROW1_OFF;
      ROW2_OFF;
      keyPressed = tempKey;
      TS_Status++;
    break;
    case TS_STOP2:
      //MyTimers[TIMER_TASTATUR_SCANNER].state = TM_STOP;
      TS_Status = TS_INACTIVE;
      keyPressed = tempKey;
      LEDGRUEN_TAST_OFF;
      LEDROT_TAST_OFF;
      //COLUMN_PORT.INTFLAGS = PORT_INT0IF_bm;
      //COLUMN_PORT.INTCTRL  = PORT_INT0LVL_MED_gc;
    break;
  }
}


uint8_t getKeyPressed(uint8_t row)
{
uint8_t key;
  key = ~COLUMN_PORT.IN;
  if((key & 128) > 0)
    return(row*5);
  if((key & 64) > 0)
    return(row*5+1);
  if((key & 16) > 0)
    return(row*5+2);
  if((key & 4) > 0)
    return(row*5+3);
  if((key & 1) > 0)
    return(row*5+4);
  return(255);
}

void setRTC(uint16_t time)
{
  RTC.INTCTRL = 0;
  RTC.CTRL = 0;
  while(RTC.STATUS & RTC_SYNCBUSY_bm)
  {
    ;
  }
  RTC.PER = time;
  RTC.CNTL = 0;
  RTC.CNTH = 0;
  RTC.CTRL = RTC_PRESCALER_DIV64_gc;
  RTC.INTCTRL = RTC_OVFINTLVL_HI_gc;
}

ISR ( RTC_OVF_vect )
{
 if(TS_Status != TS_INACTIVE)
  TastaturScanner();
}


