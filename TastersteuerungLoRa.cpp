#include "TastersteuerungLoRa.h"
#include "CmultiAddresses.h"

void setup()
{
  init_clock(SYSCLK,PLL,true,CLOCK_CALIBRATION);
	PORTA_DIRSET = 0x00;
	PORTA_OUTSET = 0xff;
	PORTB_DIRSET = 0b00001101;
	PORTD_DIRSET = 0b10111100;
	PORTE_DIRSET = PIN0_bm | PIN1_bm | PIN2_bm;
	PORTE_OUTSET = 0b00001111;
	ROW1SETUP;
	ROW2SETUP;
	ROW3SETUP;
	COL1SETUP;
	COL2SETUP;
	COL3SETUP;
	COL4SETUP;
	COL5SETUP;
  LEDGRUEN_TAST_OFF;
  LEDROT_TAST_OFF;
	//COLUMN_PORT.INT0MASK = 0b11010101;
	//COLUMN_PORT.INTCTRL  = PORT_INT0LVL_MED_gc;

	LEDBLAU_OFF; LEDROT_OFF; LEDGRUEN_OFF;
  BATTMEASSETUP; BATTMEAS_OFF;
  // Lora-Modul aufsetzen
  while (!LoRa.begin(868E6))
  {
    LEDROT_TOGGLE;
    _delay_ms(100);
  }

  LoRa.setTxPower(14, PA_OUTPUT_RFO_PIN);
  loraCmulti.setChecksum();
  //LoRa.onReceive(onReceive);
  LoRa_rxMode();


  // RTC aufsetzen
  CLK.RTCCTRL = CLK_RTCSRC_ULP_gc | CLK_RTCEN_bm; // 1kHz ULP
  setRTC(0);

  PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
	sei();

}

int main(void)
{
	setup();
  uint8_t i;
  uint8_t columnsList[] = COLUMNS_LIST;
	LEDGRUEN_OFF; LEDROT_OFF; LEDBLAU_OFF;
	ROW1_OFF; ROW2_OFF; ROW3_OFF;
	//init_mytimer();

	for(i=0;i<20;i++)
	{
		LEDGRUEN_TOGGLE;
		_delay_ms(50);
	}

	while (1)
	{
    if(keyPressed<255)
    {
      uint8_t key = keyPressed % 5;
      uint8_t column = (keyPressed - key) / 5;

      char keyFunction, keyJob;
      keyFunction = 'F';
#ifdef INVERT_ROWS
      key = 4-key;
#endif // INVERT_ROWS

      column = columnsList[column];
      switch(key)
      {
        case 0:   // down
          keyJob = 'B';
        break;
        case 1:   // fix1
          keyJob = 'b';
        break;
        case 2:   // stop
          keyFunction = 'R';
          keyJob = 'S';
        break;
        case 3:   // fix2
          keyJob = 'a';
        break;
        case 4:   // up
          keyJob = 'T';
        break;
      }

      loraCmulti.sendCommand(TARGET,keyFunction,'0'+column,keyJob);
      sendViaRelay(loraCmulti.get());
      processRelaisInfos(&cmulti);
      loraCmulti.broadcastDouble(doSpannungsMessung(),'S','1','U');
      sendViaRelay(loraCmulti.get());
      keyPressed = 255;
    }

    if( (processRelaisInfos(&cmulti)) && (TS_Status == TS_INACTIVE) && (((~COLUMN_PORT.IN) & 0b11010101)  == 0))
    {
      LEDBLAU_OFF;
      LEDGRUEN_OFF;
      BATTMEAS_OFF;
      //CLK.RTCCTRL = 0;    // myTimer abschalten
      LoRa.sleep();
      set_sleep_mode(SLEEP_MODE_PWR_SAVE);
      sleep_enable();
      sleep_cpu();
      sleep_disable();
      if(checkTastatur())
      {
        LoRa.onReceive(onReceive);
        LoRa_rxMode();
        LoRa_txMode();
        LEDBLAU_ON;
        BATTMEAS_ON;

      }
    }
	}
}

/*
ISR(PORTC_INT0_vect)
{
  if(TS_Status == TS_INACTIVE)
  {
    COLUMN_PORT.INTCTRL  = 0;
    ROW2_ON;
    ROW3_ON;
    MyTimers[TIMER_TASTATUR_SCANNER].state = TM_START;
    TS_Status++;
  }
}*/
