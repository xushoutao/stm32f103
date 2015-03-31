#include <stm32f10x.h>
#include <stdio.h>
#include "math.h"
#include "stm32f2x7_wtd_ad7708.h"
#include "stm32f2x7_wtd_ad7708_if.h"
#include "stm32f2x7_wtd_eeprom.h"
#include "common.h"
#include "wtdconf.h"

#if WIND_SENSOR

uint16_t u16_WindD;
uint16_t u16_WindS;
uint16_t u16_WindDOffset;
uint16_t u16_WindSOffset;
uint16_t u16_WindDStatus;
uint16_t u16_WindSStatus;

uint16_t Get_WindD(void)
{
	uint16_t t_bcdret;
	t_bcdret = INT162BCD(u16_WindD + u16_WindDOffset);
	//t_bcdret += u16_WindDOffset;	   //去掉，考虑到BCD码相加要进位

	if(t_bcdret >= 0x8000)
	{
	   t_bcdret = 0x0000;
	}

 	return 	(t_bcdret);
}

uint16_t Get_WindS(void)
{
	uint16_t t_bcdret;
	t_bcdret = INT162BCD(u16_WindS + u16_WindSOffset);
	//t_bcdret += u16_WindSOffset;		//去掉，考虑到BCD码相加要进位

	if(t_bcdret >= 0x8000)
	{
	   t_bcdret = 0x0000;
	}

 	return 	(t_bcdret);
}
uint16_t Get_WindDOffset(void)
{
 	return 	u16_WindDOffset;
}
uint16_t Get_WindSOffset(void)
{
 	return 	u16_WindSOffset;
}
uint16_t Get_WindDStatus(void)
{
 	return 	u16_WindDStatus;
}
uint16_t Get_WindSStatus(void)
{
 	return 	u16_WindSStatus;
}

void Set_WindDOffset(uint16_t t)
{
	uint8_t windl,windh;
 	u16_WindDOffset = t;
	windl = (uint8_t)t;
	windh = (uint8_t)(t >> 8);
	E2P_WriteBKUP(E2P_WDL,windl);
	E2P_WriteBKUP(E2P_WDH,windh);
}

void Set_WindSOffset(uint16_t t)
{
	uint8_t winsl,winsh;
 	u16_WindSOffset = t;
	winsl = (uint8_t)t;
	winsh = (uint8_t)(t >> 8);
	E2P_WriteBKUP(E2P_WSL,winsl);
	E2P_WriteBKUP(E2P_WSH,winsh);
}

void Set_WindDStatus(uint16_t t)
{
 	u16_WindDStatus = t;
}

void Set_WindSStatus(uint16_t t)
{
 	u16_WindSStatus = t;
}

void if_ad7708_init(void)
{
//	st7705cf0.u8cf = 0x44;
//	st7705cf1.u8cf = 0x44;
	//Driver_ad7705_init(st7705cf0,st7705cf1);
	u8 t = 0x00;
	u16_WindD = 0x0000;
	u16_WindS = 0x0000;

	Driver_ad7708_init(0,0);

	//u16_WindDOffset = 0x0000;
	//u16_WindSOffset = 0x0000;
	E2P_ReadBKUP(E2P_WDH,&t);
    u16_WindDOffset = t; 
	u16_WindDOffset <<= 8;
	E2P_ReadBKUP(E2P_WDL,&t);
	u16_WindDOffset += t;
	E2P_ReadBKUP(E2P_WSH,&t);
	u16_WindSOffset = t;
	u16_WindSOffset <<= 8;
	E2P_ReadBKUP(E2P_WSL,&t);
	u16_WindSOffset += t;
	u16_WindDStatus = NORMAL_WORK;
	u16_WindSStatus = NORMAL_WORK;
}

void if_ad7708_proc(void)
{// 风向
   float fTemper;
   uint16_t temp,t;
   uint8_t windl,windh;

   if(Driver_ad7708_IsReady()==AD7708_IS_READY)
   {
	   		printf("CH1: ");
       		temp = Driver_ad7708_RdWord(AD7708_CHANNEL_1,0);
			fTemper = temp;
			fTemper *= 2.49;
			fTemper /= 65535;

			fTemper	= 360.0/1.6*(fTemper - 0.4);

			u16_WindD = fTemper*10;
			//f_printf(fTemper, 4);
			printf("windD is %d\n",u16_WindD);
   }
//   else
//       {
//       		printf("CH1: Not Ready\n");
//       }
//
//	if(u16_WindDStatus == ZERO_CALIBER)
//	{
//		//u16_WindDOffset = u16_WindD - 0x291F;		 // - 0x291F是4ma * 100欧的等效值
//		u16_WindD = 121;
//		u16_WindDOffset = u16_WindD; //INT162BCD(u16_WindD);
//		u16_WindDOffset = 0x0000 - u16_WindDOffset;
//	 	u16_WindDStatus	= NORMAL_WORK;
//		t = u16_WindDOffset;
//		windl = (uint8_t)t;
//		windh = (uint8_t)(t >> 8);
//		AT24C02_WriteByte(E2P_WDL,windl);
//		AT24C02_WriteByte(E2P_WDH,windh);
//	}
//	else
//	{
//		u16_WindDStatus	= NORMAL_WORK;
//	}
}

void if_ad7708_proc_ch2(void)
{// 风速
//   float fTemper;
//   uint16_t temp,t;
//   uint8_t winsl,winsh;
//
//	if(Driver_ad7708_IsReady()==AD7708_IS_READY)
//	{
//		printf("CH2: ");
//		//temp = Driver_ad7705_RdWord(AD7705_CHANNEL_2);
//		fTemper = temp;
//		fTemper *= 2.49;
//		fTemper /= 65535;
//	
//		fTemper	= 50.0/1.6*(fTemper - 0.4);
//	
//		u16_WindS = fTemper*100;
//		//f_printf(fTemper, 4);
//		printf("windS is %d\n",u16_WindS);
//		//f_printf(fTemper, 4);
//	}
//	else
//	{
//			printf("CH2: Not Ready\n");
//	}
//
//	if(u16_WindSStatus == ZERO_CALIBER)
//	{
//		//u16_WindSOffset = u16_WindS - 0x291F;	  // - 0x291F是4ma * 100欧的等效值
//	 	//u16_WindSStatus	= NORMAL_WORK;
//		//u16_WindSOffset = INT162BCD(u16_WindS);
//		u16_WindSOffset = u16_WindS;
//		u16_WindSOffset = 0x0000 - u16_WindSOffset;
//		u16_WindSStatus	= NORMAL_WORK;
//		t = u16_WindDOffset;
//		winsl = (uint8_t)t;
//		winsh = (uint8_t)(t >> 8);
//		AT24C02_WriteByte(E2P_WSL,winsl);
//		AT24C02_WriteByte(E2P_WSH,winsh);
//	}
//	else
//	{
//	 	u16_WindSStatus	= NORMAL_WORK;
//	}
}

#endif
