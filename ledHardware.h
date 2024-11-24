#pragma once

/* Steuerleitung */
#define BATTMEAS_PORT PORTB
#define BATTMEAS_PIN  PIN0_bm

#define BATTMEASSETUP BATTMEAS_PORT.DIRSET=BATTMEAS_PIN
#define BATTMEAS_ON   BATTMEAS_PORT.OUTSET=BATTMEAS_PIN
#define BATTMEAS_OFF  BATTMEAS_PORT.OUTCLR=BATTMEAS_PIN
#define BATTMEAS_TOGGLE  BATTMEAS_PORT.OUTTGL=BATTMEAS_PIN


/* LED auf Basisplatine */
#define LEDGRUEN_PORT PORTE
#define LEDGRUEN_PIN  PIN0_bm
#define LEDROT_PORT PORTE
#define LEDROT_PIN  PIN1_bm
#define LEDBLAU_PORT PORTE
#define LEDBLAU_PIN  PIN2_bm

#define LEDGRUENSETUP LEDGRUEN_PORT.DIRSET=LEDGRUEN_PIN
#define LEDGRUEN_ON   LEDGRUEN_PORT.OUTCLR=LEDGRUEN_PIN
#define LEDGRUEN_OFF  LEDGRUEN_PORT.OUTSET=LEDGRUEN_PIN
#define LEDGRUEN_TOGGLE  LEDGRUEN_PORT.OUTTGL=LEDGRUEN_PIN

#define LEDROTSETUP LEDROT_PORT.DIRSET=LEDROT_PIN
#define LEDROT_ON   LEDROT_PORT.OUTCLR=LEDROT_PIN
#define LEDROT_OFF  LEDROT_PORT.OUTSET=LEDROT_PIN
#define LEDROT_TOGGLE  LEDROT_PORT.OUTTGL=LEDROT_PIN

#define LEDBLAUSETUP LEDBLAU_PORT.DIRSET=LEDBLAU_PIN
#define LEDBLAU_ON   LEDBLAU_PORT.OUTCLR=LEDBLAU_PIN
#define LEDBLAU_OFF  LEDBLAU_PORT.OUTSET=LEDBLAU_PIN
#define LEDBLAU_TOGGLE  LEDBLAU_PORT.OUTTGL=LEDBLAU_PIN

/* LEDs auf der Tastatur */
#ifdef TASTATUR
#define LEDGRUEN_TAST_PORT PORTB
#define LEDGRUEN_TAST_PIN  PIN3_bm
#define LEDROT_TAST_PORT PORTB
#define LEDROT_TAST_PIN  PIN2_bm

#define LEDGRUEN_TASTSETUP LEDGRUEN_TAST_PORT.DIRSET=LEDGRUEN_TAST_PIN
#define LEDGRUEN_TAST_ON   LEDGRUEN_TAST_PORT.OUTCLR=LEDGRUEN_TAST_PIN
#define LEDGRUEN_TAST_OFF  LEDGRUEN_TAST_PORT.OUTSET=LEDGRUEN_TAST_PIN
#define LEDGRUEN_TAST_TOGGLE  LEDGRUEN_TAST_PORT.OUTTGL=LEDGRUEN_TAST_PIN

#define LEDROT_TASTSETUP LEDROT_TAST_PORT.DIRSET=LEDROT_TAST_PIN
#define LEDROT_TAST_ON   LEDROT_TAST_PORT.OUTCLR=LEDROT_TAST_PIN
#define LEDROT_TAST_OFF  LEDROT_TAST_PORT.OUTSET=LEDROT_TAST_PIN
#define LEDROT_TAST_TOGGLE  LEDROT_TAST_PORT.OUTTGL=LEDROT_TAST_PIN
#endif // TASTATUR

/* VMEASURE einschalten */
#define VMEASURE_PORT PORTB
#define VMEASURE_PIN  PIN0_bm
#define VMEASURE_TASTSETUP VMEASURE_TAST_PORT.DIRSET=VMEASURE_TAST_PIN
#define VMEASURE_TAST_ON   VMEASURE_TAST_PORT.OUTCLR=VMEASURE_TAST_PIN
#define VMEASURE_TAST_OFF  VMEASURE_TAST_PORT.OUTSET=VMEASURE_TAST_PIN
#define VMEASURE_TAST_TOGGLE  VMEASURE_TAST_PORT.OUTTGL=VMEASURE_TAST_PIN



