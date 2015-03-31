#include "stm32f2xx.h"
#include "stm32f2x7_wtd_humtemp_if.h"
#include "stm32f2x7_wtd_humtemp.h"
#include <stdio.h>
#include "wtdconf.h"

#if TEMP_EN_CONFIG

#define TEMP  1
#define HUM   2
 
uint16_t u16Temperature;
uint16_t u16Humidity;
uint16_t u16savetemp; 
uint16_t u16savehum;


void TempAndHum_Init(void)
{					     

	Drive_HumTemp_Init();

	u16Temperature=0;
	u16Humidity=0;
	u16savetemp=0;
	u16savehum=0;

}
void TempAndHum_proc(void)
{
	Drive_HumTemp_ClearBuffer();
	Drive_HumTemp_woken();
	WriteCommand();
	OS_DELAY_MS(20);
#if 0
	ReadTempAndHum(&u16Temperature,&u16Humidity);
#endif
	TL_ReadTempAndHum(&u16Temperature,&u16Humidity);
	if((u16Temperature!=0)&&(u16Temperature<0x9991))
	{
	u16savetemp=u16Temperature; 
	}
	if((u16Humidity!=0)&&(u16Humidity<0x9991))
	{
    u16savehum=u16Humidity;
	}

	printf("T 0x%x\n",u16Temperature);
	printf("H 0x%x\n",u16Humidity);

}
uint16_t GetTemperature(void)
{  
#if 0
   if((u16Temperature==0)||(u16Temperature>=0x9991)) 
	{
    	return u16savetemp;
	}
   else
    {
       	return u16Temperature;
    }
#endif

	return u16Temperature;
}
uint16_t GetHumidity(void)
{
#if 0
  if((u16Humidity==0)||(u16Humidity>=0x9991)) 
   {
   		return u16savehum;
   }
   else
   {
   		return u16Humidity;
   }
#endif

   return u16Humidity;
}

#endif





















