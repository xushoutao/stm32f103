#ifndef STM32F2X7_WTD_HUMTEMP_IF_H
#define STM32F2X7_WTD_HUMTEMP_IF_H

void TempAndHum_Init(void);
void TempAndHum_proc(void);
uint16_t GetTemperature(void);
uint16_t GetHumidity(void);



#endif
