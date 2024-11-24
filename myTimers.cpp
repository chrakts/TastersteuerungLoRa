#include "myTimers.h"
#include "ledHardware.h"

// 1:  9.9  ms
// 2:  19.8 ms
// 5:  49.4 ms
//10:  99.0 ms
//101: 1000 ms

#define NUM_ROWS 3

volatile TIMER MyTimers[MYTIMER_NUM]= {	{TM_STOP,RESTART_YES,7,0,TastaturScanner},
                                        {TM_STOP,RESTART_YES,10,0,led1Blinken}
};

void led1Blinken(uint8_t test)
{
	LEDROT_TAST_TOGGLE;
}

void TastaturScanner(uint8_t test)
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
      MyTimers[TIMER_TASTATUR_SCANNER].state = TM_STOP;
      TS_Status = TS_INACTIVE;
      keyPressed = tempKey;
      LEDGRUEN_TAST_OFF;
      LEDROT_TAST_OFF;
      COLUMN_PORT.INTFLAGS = PORT_INT0IF_bm;
      COLUMN_PORT.INTCTRL  = PORT_INT0LVL_MED_gc;
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


