#ifndef __APP_SHT30_H_
#define __APP_SHT30_H_

#include "stm32f10x_conf.h"

extern float temperature; // temperature [°C]
extern float humidity;    // relative humidity [%RH]

void APP_SHT30_init();
void APP_read_sht30();

#endif
