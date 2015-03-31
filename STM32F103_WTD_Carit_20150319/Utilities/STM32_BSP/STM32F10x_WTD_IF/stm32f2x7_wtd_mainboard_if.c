#include <stm32f2xx.h>
#include  "wtdconf.h"
#include <stdio.h>
#include "stm32f2x7_wtd_mainboard_if.h"
#include "stm32f2x7_wtd_mainboard.h"
//#include "app_lib.h"

#if MAIN_PWR_EN
//#define WIND12V_POS				(0x0001)		  
//#define RAIN12VP_POS 			(0x0002)
//#define DUST12V_POS				(0x0004)
//#define HUMTEMP5VP_POS 			(0x0008)
//#define SOUND5V_POS				(0x0010)
//#define GPS_POS					(0x0020)
//#define RESERVED112V_POS		(0x0040)
//#define RESERVED212V_POS		(0x0080)

#define WIND12V_POS				BIT(0)		  
#define RAIN12VP_POS 			BIT(1)
#define DUST12V_POS				BIT(2)
#define HUMTEMP5V_POS 			BIT(3)
#define SOUND5V_POS				BIT(4)
#define GPS_POS					BIT(5)
#define RESERVED112V_POS		BIT(6)
#define RESERVED212V_POS		BIT(7)

#define WINDPW_POS				BIT(8)		  
#define RAINPW_POS 				BIT(9)
#define DUSTPW_POS				BIT(10)
#define HUMTEMPPW_POS 			BIT(11)
#define SOUNDPW_POS				BIT(12)
#define GPSPW_POS				BIT(13)
#define RESERVED1PW_POS			BIT(14)
#define RESERVED2PW_POS			BIT(15)


#define PTZ12VP_POS 			(0x0000)
#define PTZ5VP_POS 				(0x0000)
#define WIND5V_POS				(0x0000)
#define RAIN5VP_POS 			(0x0000)
#define DUST5V_POS				(0x0000)
#define HUMTEMP12VP_POS 		(0x0000)
#define SOUND12V_POS			(0x0000)
#define RESERVED15V_POS			(0x0000)
#define RESERVED25V_POS			(0x0000)

#define POWER_TH		(0x0100)

#define HMI_RESETCOUNT_MAX (30000)	   //5mins

#define HMI_POWERCOUNT_MAX	(10)

uint16_t u16_mainboardRelayPos;
uint16_t u16_mainboardRelayPos_old;
uint16_t u16_mainboardHMIPos;
uint16_t u16_mainboardHMIPos_old;
uint16_t u16_HMICount;
uint16_t u16_mainboardPower;
uint16_t u16_mainboardPowerCnt;
uint16_t u16_mainboardPowerSave[HMI_POWERCOUNT_MAX];
uint16_t u16_mainboardState;
uint16_t u16_mainboard5430en;   //5430enable
uint16_t u16_mainboardPwrsw;    //用于判断是否被超越开关打开
uint16_t u16_mainboardtakePic;    //用于判断是否被拍照命令打开

OS_EVENT *AD_Box;
OS_EVENT *MBUart3_Sem;

void Set_TakePicReq(uint16_t val)
{
	if(u16_mainboardState == POWER_STATE_SLEEP)
	{
		u16_mainboardtakePic = val;
	}
}

void Set_PowerState(uint16_t val)
{
 	u16_mainboardState = val;
}

void Set_ALL(uint16_t val)
{
	u16_mainboardRelayPos = val;
}

void Set_PTZ12V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardHMIPos |= CAMERA_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardHMIPos &= ~CAMERA_POS;
 }
 else
 {
	 ;
 }
}

void Set_PTZ5V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= PTZ5VP_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~PTZ5VP_POS;
 }
 else
 {
	 ;
 }
}

void Set_Wind12V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= WIND12V_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~WIND12V_POS;
 }
 else
 {
	 ;
 }
}

void Set_Wind5V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= WIND5V_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~WIND5V_POS;
 }
 else
 {
	 ;
 }
}

void Set_Rain12V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= RAIN12VP_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~RAIN12VP_POS;
 }
 else
 {
	 ;
 }
}

void Set_Rain5V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= RAIN5VP_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~RAIN5VP_POS;
 }
 else
 {
	 ;
 }
}

void Set_Dust12V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= DUST12V_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~DUST12V_POS;
 }
 else
 {
	 ;
 }
}

void Set_Dust5V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= DUST5V_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~DUST5V_POS;
 }
 else
 {
	 ;
 }
}

void Set_HumTemp12V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= HUMTEMP12VP_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~HUMTEMP12VP_POS;
 }
 else
 {
	 ;
 }
}

void Set_HumTemp5V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= HUMTEMP5V_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~HUMTEMP5V_POS;
 }
 else
 {
	 ;
 }
}

void Set_Sound12V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= SOUND12V_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~SOUND12V_POS;
 }
 else
 {
	 ;
 }
}

void Set_Sound5V(uint8_t val)
{
 if(val == 0x01)
 {
	 u16_mainboardRelayPos |= SOUND5V_POS;
 }
 else if(val == 0x00)
 {
	 u16_mainboardRelayPos &= ~SOUND5V_POS;
 }
 else
 {
	 ;
 }
}

void Set_Reseved112V(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= RESERVED112V_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~RESERVED112V_POS;
	}
	else
	{
		;
	}
}

void Set_Reseved15V(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= RESERVED15V_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~RESERVED15V_POS;
	}
	else
	{
		;
	}
}

void Set_Reseved212V(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= RESERVED212V_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~RESERVED212V_POS;
	}
	else
	{
		;
	}
}

void Set_Reseved25V(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= RESERVED25V_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~RESERVED25V_POS;
	}
	else
	{
		;
	}
}

void Set_GPS12V(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= GPS_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~GPS_POS;
	}
	else
	{
		;
	}
}

void Set_CS(uint8_t val)
{//加热棒
   	if(val == 0x01)
	{
		u16_mainboardHMIPos |= CS_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardHMIPos &= ~CS_POS;
	}
	else
	{
		;
	}
}

void Set_WINDPW(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= WINDPW_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~WINDPW_POS;
	}
	else
	{
		;
	}
}
		  
void Set_RAINPW(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= RAINPW_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~RAINPW_POS;
	}
	else
	{
		;
	}
}

void Set_DUSTPW(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= DUSTPW_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~DUSTPW_POS;
	}
	else
	{
		;
	}
}

void Set_HUMTEMPPW(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= HUMTEMPPW_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~HUMTEMPPW_POS;
	}
	else
	{
		;
	}
}

void Set_SOUNDPW(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= SOUNDPW_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~SOUNDPW_POS;
	}
	else
	{
		;
	}
}

void Set_GPSPW(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= GPSPW_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~GPSPW_POS;
	}
	else
	{
		;
	}
}

void Set_RESERVED1PW(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= RESERVED1PW_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~RESERVED1PW_POS;
	}
	else
	{
		;
	}
}

void Set_RESERVED2PW(uint8_t val)
{
	if(val == 0x01)
	{
		u16_mainboardRelayPos |= RESERVED2PW_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardRelayPos &= ~RESERVED2PW_POS;
	}
	else
	{
		;
	}
}

void Set_HMI(uint8_t val)
{
   	if(val == 0x01)
	{
		u16_mainboardHMIPos |= HMI_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardHMIPos &= ~HMI_POS;
	}
	else
	{
		;
	}
}

void Set_FAN(uint8_t val)
{
#if MAINBOARD_SPORE_EN_CONFIG
   	if(val == 0x01)
	{
		u16_mainboardHMIPos |= FAN_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardHMIPos &= ~FAN_POS;
	}
	else
	{
		;
	}
#endif
}

void Set_MOTOR(uint8_t val)
{
#if MAINBOARD_SPORE_EN_CONFIG
   	if(val == 0x01)
	{
		u16_mainboardHMIPos |= MOTOR_POS;
	}
	else if(val == 0x00)
	{
		u16_mainboardHMIPos &= ~MOTOR_POS;
	}
	else
	{
		;
	}
#endif
}

void Set_HMICount(uint16_t val)
{
	 u16_HMICount = val;
}

void Set_5430en(uint16_t val)
{
 	u16_mainboard5430en = val;
}

void Set_mainboardPower(uint16_t val)
{
	uint16_t i;
	uint32_t total;
	uint16_t tmp;

	total = 0x00000000;

	if(u16_mainboardPowerCnt < 0xFFFF)
	{
		u16_mainboardPowerCnt ++;
	}

	if(u16_mainboardPowerCnt >= HMI_POWERCOUNT_MAX)
	{
	   u16_mainboardPowerCnt = 0x0000;
	}


	u16_mainboardPowerSave[u16_mainboardPowerCnt] = val;

	for(i = 0; i < HMI_POWERCOUNT_MAX ; i ++)
	{
		total += u16_mainboardPowerSave[i];
	}

	total /= HMI_POWERCOUNT_MAX;
	//printf("total is %d\r\n",total);

	u16_mainboardPower = total;
	//printf("Power is %d\r\n",u16_mainboardPower);
	//printf("Power is %d\n",Get_mainboardPower());
	tmp = INT162BCD(u16_mainboardPower);
	//printf("Power BCD is 0x%x\r\n",tmp);

	if((Get_PowerState() == POWER_STATE_1S_INIT) && (tmp > POWER_TH))
	{
	    //可能的第一次HMI启动的位置
		//Driver_HMIPORT_Init();
		Set_PowerState(POWER_STATE_NORMAL);
		Set_HMI(0x00); //启动人机界面
	}
}

uint16_t Get_TakePicReq(void)
{
	return u16_mainboardtakePic;
}

uint16_t Get_PowerState(void)
{
 	return u16_mainboardState;
}

uint8_t Get_PTZ12V(void)
{
	if(u16_mainboardHMIPos & PTZ12VP_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_PTZ5V(void)
{
	if(u16_mainboardHMIPos & PTZ5VP_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Wind12V(void)
{
	if(u16_mainboardRelayPos & WIND12V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Wind5V(void)
{
	if(u16_mainboardRelayPos & WIND5V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Rain12V(void)
{
	if(u16_mainboardRelayPos & RAIN12VP_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Rain5V(void)
{
	if(u16_mainboardRelayPos & RAIN5VP_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Dust12V(void)
{
	if(u16_mainboardRelayPos & DUST12V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Dust5V(void)
{
	if(u16_mainboardRelayPos & DUST5V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_HumTemp12V(void)
{
	if(u16_mainboardRelayPos & HUMTEMP12VP_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_HumTemp5V(void)
{
	if(u16_mainboardRelayPos & HUMTEMP5V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Sound12V(void)
{
	if(u16_mainboardRelayPos & SOUND12V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Sound5V(void)
{
	if(u16_mainboardRelayPos & SOUND5V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Reseved112V(void)
{
	if(u16_mainboardRelayPos & RESERVED112V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Reseved15V(void)
{
	if(u16_mainboardRelayPos & RESERVED15V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Reseved212V(void)
{
	if(u16_mainboardRelayPos & RESERVED212V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_Reseved25V(void)
{
	if(u16_mainboardRelayPos & RESERVED25V_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_GPS12V(void)
{
	if(u16_mainboardRelayPos & GPS_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_WINDPW(void)
{	
	if(u16_mainboardRelayPos & WINDPW_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}
		  
uint8_t Get_RAINPW(void)
{
	if(u16_mainboardRelayPos & RAINPW_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_DUSTPW(void)
{
	if(u16_mainboardRelayPos & DUSTPW_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_HUMTEMPPW(void)
{
	if(u16_mainboardRelayPos & HUMTEMPPW_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_SOUNDPW(void)
{
	if(u16_mainboardRelayPos & SOUNDPW_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_GPSPW(void)
{
	if(u16_mainboardRelayPos & GPSPW_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_RESERVED1PW(void)
{
	if(u16_mainboardRelayPos & RESERVED1PW_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_RESERVED2PW(void)
{
	if(u16_mainboardRelayPos & RESERVED2PW_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_CS(void)
{
	if(u16_mainboardHMIPos & CS_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_HMI(void)
{
	if(u16_mainboardHMIPos & HMI_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

uint8_t Get_FAN(void)
{
#if MAINBOARD_SPORE_EN_CONFIG
	if(u16_mainboardHMIPos & FAN_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
#else
	return 0x00;
#endif
}

uint8_t Get_MOTOR(void)
{
#if MAINBOARD_SPORE_EN_CONFIG
	if(u16_mainboardHMIPos & MOTOR_POS)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
#else
	return 0x00;
#endif
}

#if MAINBOARD_SPORE_EN_CONFIG
uint8_t Get_SW1(void)
{
	uint8_t ret;
	
	ret = Driver_Get_SW1();
	
	return ret;
}

uint8_t Get_SW2(void)
{
	uint8_t ret;
	
	ret = Driver_Get_SW2();
	
	return ret;
}
#endif

uint16_t Get_HMICount(void)
{
	 return u16_HMICount;
}

uint16_t Get_mainboardPower(void)
{
	uint16_t ret;

	ret = INT162BCD(u16_mainboardPower);

	return ret;
}

uint16_t Get_mainboardPower16(void)
{
	uint16_t ret;

	ret = u16_mainboardPower;
	
	return ret;
}
//void Set_MainboardRelayPos(uint16_t u16_mainboardPos)
//{
//	u16_mainboardRelayPos = u16_mainboardPos;
//}
//
//uint16_t Get_MainboardRelayPos(void)
//{
//	uint16_t ret;
//
//	ret = u16_mainboardRelayPos;
//
//	return ret;
//}

void mainboard_init(void)
{
	uint16_t i;

	//u16_mainboardRelayPos = 0xFFFF;
	u16_mainboardRelayPos = 0x0004;
	u16_mainboardRelayPos_old = 0x0000;
	u16_mainboardHMIPos = 0x0000;
	u16_mainboardHMIPos_old = 0x0000;

	u16_mainboardState = POWER_STATE_INIT;

	u16_HMICount = 0x0000;
	u16_mainboard5430en = 0x0000;

	u16_mainboardPower = 0x0000;
	u16_mainboardtakePic = 0;

	u16_mainboardPowerCnt = 0x0000;
	for(i =0; i <= HMI_POWERCOUNT_MAX; i ++)
	{
	 	u16_mainboardPowerSave[i] = 0x0000;
	}

	u16_mainboardPwrsw = 0; //默认不是被超越开关打开

	AD_Box = OSSemCreate(0);
	MBUart3_Sem = OSSemCreate(0);

	Driver_Mainboard_Init();
	
	//Driver_Mainboard_RelayRun(0xFFFE);
	
#if !MAINBOARD_SPORE_EN_CONFIG
	Set_ALL(0xFFFE);  //关闭所有外设电源
	Set_HMI(0x01);	  //关闭HMI，云台，风扇
	Set_CS(0x01);	  //加热棒
	Set_PTZ12V(0x01);
	Set_FAN(0x01);
	Set_MOTOR(0x00);  //关闭电机板
	Driver_Mainboard_RelayRun(u16_mainboardRelayPos); 
	Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
	OSTimeDlyHMSM(0, 0, 0, 600);
	Set_ALL(0x0000);	 //打开所有外设电源
	Driver_Mainboard_RelayRun(u16_mainboardRelayPos); 
	Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
	OSTimeDlyHMSM(0, 0, 0, 400);
	Set_CS(0x00);
	Set_PTZ12V(0x00);       //打开云台
	Driver_Mainboard_RelayRun(u16_mainboardRelayPos); 
	Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
	OSTimeDlyHMSM(0, 0, 0, 300);
	Set_PowerState(POWER_STATE_1S_INIT);
	Set_FAN(0x00);		   //打开风扇
	//Set_HMI(0x00);	   // 人机界面不能打开，需要等待电压达到稳定值再打开
	Set_MOTOR(0x01);       //电机板
	Driver_Mainboard_RelayRun(u16_mainboardRelayPos); 
	Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
#else
	Set_ALL(0xFFFE);  //关闭所有外设电源
	Set_HMI(0x01);	  //关闭HMI，云台，风扇
	Set_CS(0x01);	  //加热棒
	Set_PTZ12V(0x01);
	Set_FAN(0x00);
	Set_MOTOR(0x00);  //关闭电机板
	Driver_Mainboard_RelayRun(u16_mainboardRelayPos); 
	Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
	u16_mainboardState = POWER_STATE_SAVING;  //进入待机状态
#endif
	
}

void mainboard_Proc(void)
{
	if(u16_HMICount < 0xFFFF)
	{//中断喂狗，判定是否人机界面在通信
	 	u16_HMICount ++;
	}
	else
	{
		u16_HMICount = 0x0000;
	}

	if(Get_PowerState() == POWER_STATE_STOP )
	{
		Set_HMI(0x01);
		u16_HMICount = 0xFFFF;
		if(Get_mainboardPower() > POWER_TH)
		{ 
		  Set_PowerState(POWER_STATE_NORMAL);
		  Set_HMI(0x00);
		  u16_HMICount = 0x0000;
		}
	}
 #if MAINBOARD_SPORE_EN_CONFIG
	if(Get_PowerState() == POWER_STATE_SAVING)
	{//做进入休眠准备
	   	Set_ALL(0xFFFE);
		Set_HMI(0x01);
		Set_CS(0x01);
		Set_PTZ12V(0x01);
		Set_MOTOR(0x00);
		Set_FAN(0x00);
	    Set_PowerState(POWER_STATE_SLEEP);
	    u16_HMICount = 0x0000;
	}


	if(Get_PowerState() == POWER_STATE_SLEEP)
	{
		//正在休眠，关HMI喂狗
		u16_HMICount = 0x0000;
		if(Driver_Get_PWRSW() == 1) //被打开
		{
			u16_mainboardPwrsw = 1;         //记录这次是被超越开关打开
			Set_PowerState(POWER_STATE_WAKE);
		}

	}

	if(Get_PowerState() == POWER_STATE_NORMAL)
	{
		if((u16_mainboardPwrsw == 1)&&(Driver_Get_PWRSW() == 0))
		{
			u16_mainboardPwrsw = 0;
			Set_PowerState(POWER_STATE_SAVING);
		}
	}

	if(Get_PowerState() == POWER_STATE_WAKE)
	{
		Set_ALL(0x0000);
		Driver_Mainboard_RelayRun(u16_mainboardRelayPos); 
		Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
		OSTimeDlyHMSM(0, 0, 0, 400);
		Set_CS(0x00);
		if(u16_mainboardtakePic != 0)
		{
			Set_PTZ12V(0x00);		//开云台电源
		}
		Driver_Mainboard_RelayRun(u16_mainboardRelayPos); 
		Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
		OSTimeDlyHMSM(0, 0, 0, 300);
		Set_PowerState(POWER_STATE_1S_INIT);
		Set_FAN(0x01);   
		Set_MOTOR(0x01);
		//人机界面启动需要等待电源稳定
		Driver_Mainboard_RelayRun(u16_mainboardRelayPos); 
		Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
	}
 #endif


	if(u16_HMICount == HMI_RESETCOUNT_MAX)
	{
		 Set_HMI(0x01);
		 Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
		 OSTimeDlyHMSM(0, 0, 2, 0);
		 GPIO_ResetBits(GPIOA,GPIO_Pin_8);		//5430 disable
		 Set_HMI(0x00);
		 Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
	}

	if(u16_mainboard5430en != 0x0000)
	{
	   GPIO_ResetBits(GPIOA,GPIO_Pin_8);		//5430 disable  
	}  			

	if(u16_mainboardRelayPos_old == u16_mainboardRelayPos)
	{
		;
	}
	else
	{
		Driver_Mainboard_RelayRun(u16_mainboardRelayPos);
		u16_mainboardRelayPos_old = u16_mainboardRelayPos;
	}

	if(u16_mainboardHMIPos_old == u16_mainboardHMIPos)
	{
		;
	}
	else
	{							
		Driver_Mainboard_HMIRun(u16_mainboardHMIPos);
		u16_mainboardHMIPos_old = u16_mainboardHMIPos;
	}
}

void mainPower_Proc(void)
{
	INT8U err;

	ADC_SoftwareStartInjectedConvCmd(ADC1,ENABLE);
	OSSemPend(AD_Box,2,&err);

}

#endif	  /* MAIN_PWR_EN */

