#ifndef __IF_MIANBOARD_H
#define __IF_MIANBOARD_H

//#define SOUND_NO_ERR 		(0)
//#define SOUND_TIMEOUT	 	(1)
#define	POWER_STATE_INIT		(0x0000)
#define POWER_STATE_1S_INIT		(0x0001)
#define	POWER_STATE_AD_INIT		(0x0002)
#define POWER_STATE_NORMAL		(0x0003)
#define POWER_STATE_STOP		(0x0004)
#define POWER_STATE_SAVING		(0x0005)
#define POWER_STATE_SLEEP		(0x0006)
#define POWER_STATE_WAKE		(0x0007)

void Set_TakePicReq(uint16_t val);
void Set_PowerState(uint16_t val);
void Set_ALL(uint16_t val);
void Set_PTZ12V(uint8_t val);
void Set_PTZ5V(uint8_t val);
void Set_Wind12V(uint8_t val);
void Set_Wind5V(uint8_t val);
void Set_Rain12V(uint8_t val);
void Set_Rain5V(uint8_t val);
void Set_Dust12V(uint8_t val);
void Set_Dust5V(uint8_t val);
void Set_HumTemp12V(uint8_t val);
void Set_HumTemp5V(uint8_t val);
void Set_Sound12V(uint8_t val);
void Set_Sound5V(uint8_t val);
void Set_Reseved112V(uint8_t val);
void Set_Reseved15V(uint8_t val);
void Set_Reseved212V(uint8_t val);
void Set_Reseved25V(uint8_t val);
void Set_GPS12V(uint8_t val);
void Set_CS(uint8_t val);
void Set_HMI(uint8_t val);
void Set_HMICount(uint16_t val);
void Set_mainboardPower(uint16_t val);
void Set_5430en(uint16_t val);
void Set_WINDPW(uint8_t val);	  
void Set_RAINPW(uint8_t val);
void Set_DUSTPW(uint8_t val);
void Set_HUMTEMPPW(uint8_t val);
void Set_SOUNDPW(uint8_t val);
void Set_GPSPW(uint8_t val);
void Set_RESERVED1PW(uint8_t val);
void Set_RESERVED2PW(uint8_t val);

#if MAINBOARD_SPORE_EN_CONFIG
void Set_FAN(uint8_t val);
void Set_MOTOR(uint8_t val);
#endif

uint16_t Get_TakePicReq(void);
uint16_t Get_PowerState(void);
uint8_t Get_PTZ12V(void);
uint8_t Get_PTZ5V(void);
uint8_t Get_Wind12V(void);
uint8_t Get_Wind5V(void);
uint8_t Get_Rain12V(void);
uint8_t Get_Rain5V(void);
uint8_t Get_Dust12V(void);
uint8_t Get_Dust5V(void);
uint8_t Get_HumTemp12V(void);
uint8_t Get_HumTemp5V(void);
uint8_t Get_Sound12V(void);
uint8_t Get_Sound5V(void);
uint8_t Get_Reseved112V(void);
uint8_t Get_Reseved15V(void);
uint8_t Get_Reseved212V(void);
uint8_t Get_Reseved25V(void);
uint8_t Get_GPS12V(void);
uint8_t Get_CS(void);
uint8_t Get_HMI(void);
uint16_t Get_HMICount(void);
uint16_t Get_mainboardPower(void);
uint16_t Get_mainboardPower16(void);
uint8_t Get_WINDPW(void);
uint8_t Get_RAINPW(void);
uint8_t Get_DUSTPW(void);
uint8_t Get_HUMTEMPPW(void);
uint8_t Get_SOUNDPW(void);
uint8_t Get_GPSPW(void);
uint8_t Get_RESERVED1PW(void);
uint8_t Get_RESERVED2PW(void);

#if MAINBOARD_SPORE_EN_CONFIG
uint8_t Get_FAN(void);
uint8_t Get_SW1(void);
uint8_t Get_SW2(void);
uint8_t Get_MOTOR(void);
#endif

void mainboard_init(void);
void mainboard_Proc(void);
void mainPower_Proc(void);

extern OS_SEM_HANDLE *AD_Box;
extern OS_SEM_HANDLE *MBUart3_Sem;
//
////#if GSM_EN_CONFIG
//void GSM_SetRecvBuf(const char *Src, const unsigned int size);
//void GSM_Init(void);
//bool GSM_CmdSendEn(void);
//bool GSM_WaitSMSEn(void);
//void GSM_Proc(void);
//
//extern OS_EVENT *GSM_Sem;
//#endif

#endif
