#pragma once

#include "External.h"
#include "myConstants.h"

bool checkTastatur();
void TastaturScanner();
uint8_t getKeyPressed(uint8_t row);
void setRTC(uint16_t time);
