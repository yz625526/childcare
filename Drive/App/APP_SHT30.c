#include "APP_SHT30.h"
#include "SHT30.h"

float temperature; // temperature [°C]
float humidity;    // relative humidity [%RH]

void APP_SHT30_init()
{
    SHT3X_Init(0x44);
}

void APP_read_sht30()
{
}