#ifndef __STM32F2X7_WTD_GPS_IF_H
#define __STM32F2X7_WTD_GPS_IF_H

#include "wtdconf.h"

typedef enum
{
  NO_ERROR,
  CHECKSUM_ERR
}eGPSDataSta;

void if_gps_init(void);
void if_gps_Proc(void);
extern OS_SEM_HANDLE *GPS_Sem;
extern char GPS_Data[];

uint16_t Get_GPSVALID(void);
uint16_t Get_NSEW(void);
uint16_t Get_Latitude_L(void);
uint16_t Get_Latitude_H(void);
uint16_t Get_Longitude_L(void);
uint16_t Get_Longitude_H(void);

uint16_t Get_dwLongitude_1(void);
uint16_t Get_dwLongitude_2(void);
uint16_t Get_dwLongitude_3(void);
uint16_t Get_dwLongitude_4(void);
uint16_t Get_dwLatitude_1(void);
uint16_t Get_dwLatitude_2(void);
uint16_t Get_dwLatitude_3(void);
uint16_t Get_dwLatitude_4(void);

eGPSDataSta GPS_checksum(uint8_t *buf, uint32_t len);

#endif
