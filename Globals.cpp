/*
 * Globals.cpp
 */

#define EXTERNALS_H_

#include "TastersteuerungLoRa.h"
#include "CmultiAddresses.h"
#include "../Secrets/secrets.h"
#include "loraCmulti.h"


const char *Node = NODE_STRING;

volatile uint8_t TS_Status = TS_INACTIVE;
volatile uint8_t keyPressed = 255;

volatile char strStatusNachtabsenkung[5];
volatile bool statusNachtabsenkung;

uint16_t actReportBetweenBlocks  = REPORT_BETWEEN_BLOCKS;
uint16_t actReportBetweenSensors = REPORT_BETWEEN_SENSORS;
uint16_t actWaitAfterLastSensor  = WAIT_AFTER_LAST_SENSOR;

volatile uint8_t statusReport = FIRSTREPORT;
volatile bool    sendStatusReport = true;

ComReceiver cmultiRec(&cmulti,Node,cnetCommands,NUM_COMMANDS,information,NUM_INFORMATION,"W1",sendViaRelay);


SPI mySPI(0);
LoRaClass LoRa(&mySPI);

Communication cmulti(0,Node,5,false);

