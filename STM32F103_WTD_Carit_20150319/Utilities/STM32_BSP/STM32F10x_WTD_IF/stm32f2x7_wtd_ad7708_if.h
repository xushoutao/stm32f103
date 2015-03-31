#ifndef __STM32F2X7_WTD_7708_H
#define __STM32F2X7_WTD_7708_H

#include "stm32f2xx.h"

#define NORMAL_WORK		(0)
#define ZERO_CALIBER	(1)

#if WIND_SENSOR

void if_ad7708_init(void);
void if_ad7708_proc(void);
void if_ad7708_proc_ch2(void);
uint16_t Get_WindD(void);
uint16_t Get_WindS(void);
uint16_t Get_WindDOffset(void);
uint16_t Get_WindSOffset(void);
uint16_t Get_WindDStatus(void);
uint16_t Get_WindSStatus(void);
void Set_WindDOffset(uint16_t t);
void Set_WindSOffset(uint16_t t);
void Set_WindDStatus(uint16_t t);
void Set_WindSStatus(uint16_t t);

#endif

#endif
