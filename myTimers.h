/*
 * MyTimer.h
 *
 * Created: 11.02.2016 20:20:03
 *  Author: Christof
 */


#ifndef MYTIMERS_H_
#define MYTIMERS_H_

#include "timer.h"
#include "External.h"
#include "myConstants.h"

#define MYTIMER_NUM	2



enum{TIMER_TASTATUR_SCANNER,TIMER_LED_BLINKEN};

void TastaturScanner(uint8_t test);
void led1Blinken(uint8_t test);

extern volatile TIMER MyTimers[MYTIMER_NUM];

uint8_t getKeyPressed(uint8_t row);

#endif /* MYTIMERS_H_ */
