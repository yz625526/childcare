#ifndef __APP_GPS_H_
#define __APP_GPS_H_

#include "stm32f10x_conf.h"

void GPS_APP_init();
void GPS_read();


void ParseGps();
void printGpsBuffer();

#endif
