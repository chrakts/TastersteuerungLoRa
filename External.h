#pragma once

#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "timer.h"
#include "myConstants.h"
#include "secrets.h"
#include "tasterHardware.h"
#include "ledHardware.h"
#include "SPI.h"
#include "LoRa.h"
#include "Cmulti2Buffer_v02.h"
#include "ComReceiver.h"


extern const char *Node;

enum{TS_INACTIVE, TS_ROW1, TS_ROW2, TS_ROW3, TS_STOP1, TS_STOP2};

extern volatile uint8_t TS_Status;
extern volatile uint8_t keyPressed;
extern uint16_t actReportBetweenBlocks;
extern uint16_t actReportBetweenSensors;
extern uint16_t actWaitAfterLastSensor;

extern volatile uint8_t statusReport;
extern volatile bool sendStatusReport;

extern volatile char strStatusNachtabsenkung[5];
extern volatile bool statusNachtabsenkung;


//class Communication;   // Forward declaration
//class ComReceiver;
extern Serial debug;
extern Communication cmulti;
extern ComReceiver cnetRec;
extern CRC_Calc crcGlobal;

class LoRaClass;
extern LoRaClass LoRa;

extern uint8_t key[];
extern char LoraCmultiBuffer[];
extern Cmulti2Buffer_v02 loraCmulti;
