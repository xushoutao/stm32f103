#include <stm32f2xx.h>
#include <stdio.h>
#include <math.h>
#include "stm32f2x7_wtd_gps_if.h"
#include "stm32f2x7_wtd_gps.h"
//#include "app_lib.h"

typedef struct{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
}DATE_TIME;

typedef struct{
    double latitude; //����
    double longitude; //γ��
    int latitude_Degree;    //��
    int        latitude_Cent;   //��
    int     latitude_Second; //��
    int longitude_Degree;    //��
    int        longitude_Cent;  //��
    int     longitude_Second; //��
    float     speed; //�ٶ�
    float     direction; //����
    float     height; //���θ߶�
    int satellite;
    uint8_t     NS;
    uint8_t     EW;
    DATE_TIME D;
}GPS_INFO;

OS_SEM_HANDLE *GPS_Sem;
char GPS_Data[80];

float GPS_longitude;	 //GPS����
float GPS_latitude;		 //GPSγ��
double GPS_dwLongitude;
double GPS_dwLatitude;
GPS_INFO GPS;		     //GPS��Ϣ
uint32_t GPS_VALID;

/*
*********************************************************************************************************
*                                                Get_dwLongitude_1()
*
* Description : GPS����ֵ ����λΪ�� 
*
* Argument(s) : none.
*
* Return(s)   : �ȵ����0 - 15λ
*********************************************************************************************************
*/
uint16_t Get_dwLongitude_1(void)
{
	double *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_dwLongitude;
	t_ret = (uint16_t)(*(uint64_t *)t_tmp);

 	return 	(t_ret);

}

/*
*********************************************************************************************************
*                                                Get_dwLongitude_2()
*
* Description : GPS����ֵ ����λΪ�� 
*
* Argument(s) : none.
*
* Return(s)   : �ȵ�16 - 31λ
*********************************************************************************************************
*/
uint16_t Get_dwLongitude_2(void)
{
	double *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_dwLongitude;
	t_ret = (uint16_t)(*(uint64_t *)t_tmp >> 16);

 	return 	(t_ret);
}

/*
*********************************************************************************************************
*                                                Get_dwLongitude_3()
*
* Description : GPS����ֵ ����λΪ�� 
*
* Argument(s) : none.
*
* Return(s)   : �ȵ�32 - 47λ
*********************************************************************************************************
*/
uint16_t Get_dwLongitude_3(void)
{
	double *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_dwLongitude;
	t_ret = (uint16_t)(*(uint64_t *)t_tmp >> 32);

 	return 	(t_ret);
}

/*
*********************************************************************************************************
*                                                Get_dwLongitude_4()
*
* Description : GPS����ֵ ����λΪ�� 
*
* Argument(s) : none.
*
* Return(s)   : �ȵ�48 - 63λ
*********************************************************************************************************
*/
uint16_t Get_dwLongitude_4(void)
{
	double *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_dwLongitude;
	t_ret = (uint16_t)(*(uint64_t *)t_tmp >> 48);

 	return 	(t_ret);
}

/*
*********************************************************************************************************
*                                                Get_dwLatitude_1()
*
* Description : GPSγ��ֵ ����λΪ�� 
*
* Argument(s) : none.
*
* Return(s)   : �ȵ����0 - 15λ
*********************************************************************************************************
*/
uint16_t Get_dwLatitude_1(void)
{
	double *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_dwLatitude;
	t_ret = (uint16_t)(*(uint64_t *)t_tmp);

 	return 	(t_ret);

}

/*
*********************************************************************************************************
*                                                Get_dwLatitude_2()
*
* Description : GPSγ��ֵ ����λΪ�� 
*
* Argument(s) : none.
*
* Return(s)   : �ȵ����16 - 31λ
*********************************************************************************************************
*/
uint16_t Get_dwLatitude_2(void)
{
	double *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_dwLatitude;
	t_ret = (uint16_t)(*(uint64_t *)t_tmp >> 16);

 	return 	(t_ret);

}

/*
*********************************************************************************************************
*                                                Get_dwLatitude_3()
*
* Description : GPSγ��ֵ ����λΪ�� 
*
* Argument(s) : none.
*
* Return(s)   : �ȵ����32 - 47λ
*********************************************************************************************************
*/
uint16_t Get_dwLatitude_3(void)
{
	double *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_dwLatitude;
	t_ret = (uint16_t)(*(uint64_t *)t_tmp >> 32);

 	return 	(t_ret);

}

/*
*********************************************************************************************************
*                                                Get_dwLatitude_4()
*
* Description : GPSγ��ֵ ����λΪ�� 
*
* Argument(s) : none.
*
* Return(s)   : �ȵ����48 - 63λ
*********************************************************************************************************
*/
uint16_t Get_dwLatitude_4(void)
{
	double *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_dwLatitude;
	t_ret = (uint16_t)(*(uint64_t *)t_tmp >> 48);

 	return 	(t_ret);

}

/*
*********************************************************************************************************
*                                                Get_GPSVALID()
*
* Description : GPS������Ч��־λ 
*
* Argument(s) : none.
*
* Return(s)   : ASCII��'A'Ϊ��Ч��'V'Ϊ��Ч
*********************************************************************************************************
*/
uint16_t Get_GPSVALID(void)
{
   uint16_t ret;

   ret = GPS_VALID;

   return ret;
}

/*
*********************************************************************************************************
*                                                Get_NSEW()
*
* Description : GPS���������ϱ�γ�ж�λ 
*
* Argument(s) : none.
*
* Return(s)   : ��λΪ����������λΪ�ϱ�γ����ascii��ʾ������'N','E'
*********************************************************************************************************
*/
uint16_t Get_NSEW(void)
{
   uint16_t ret;

   ret = GPS.EW;
   ret <<= 8;
   ret += GPS.NS;

   return ret;
}

/*
*********************************************************************************************************
*                                                Get_Latitude_L()
*
* Description : ��ȡγ��ֵ���ݵ�λ 
*
* Argument(s) : none.
*
* Return(s)   : ����GPS��γ��ֵ��λ
*********************************************************************************************************
*/
uint16_t Get_Latitude_L(void)
{
	float *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_latitude;
	t_ret = (uint16_t)(*(uint32_t *)t_tmp);

 	return 	(t_ret);
}

/*
*********************************************************************************************************
*                                                Get_Latitude_H()
*
* Description : ��ȡγ��ֵ���ݸ�λ 
*
* Argument(s) : none.
*
* Return(s)   : ����GPS��γ��ֵ��λ
*********************************************************************************************************
*/
uint16_t Get_Latitude_H(void)
{
	float *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_latitude;
	t_ret = (uint16_t)(*(uint32_t *)t_tmp >> 16);

 	return 	(t_ret);
}


/*
*********************************************************************************************************
*                                                Get_Longitude_L()
*
* Description : ��ȡ����ֵ���ݵ�λ 
*
* Argument(s) : none.
*
* Return(s)   : ����GPS�ľ���ֵ��λ
*********************************************************************************************************
*/
uint16_t Get_Longitude_L(void)
{
	float *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_longitude;
	t_ret = (uint16_t)(*(uint32_t *)t_tmp);

 	return 	(t_ret);
}

/*
*********************************************************************************************************
*                                                Get_Longitude_H()
*
* Description : ��ȡ����ֵ���ݸ�λ 
*
* Argument(s) : none.
*
* Return(s)   : ����GPS�ľ���ֵ��λ
*********************************************************************************************************
*/
uint16_t Get_Longitude_H(void)
{
	float *t_tmp;
	uint16_t t_ret;

	t_tmp = &GPS_longitude;
	t_ret = (uint16_t)(*(uint32_t *)t_tmp >> 16);

 	return 	(t_ret);
}

int GetComma(char num, char *buf)
{
	int ret = 0;

	while(num)
	{
		if (buf[ret] == ',')
		{
			num --;
			if(num == 0)
			{
			//;	break;
			}
		}
		ret ++;
	}

	return ret;
}

double Get_Double_Number(char *buf)
{
	double ret;
	char i = 0;
	int div = 1;

	while(1)
	{
		if(buf[i] == ',')
		{
			div = i - div;
			ret /= pow(10,div);
			break;
		}
		else if(buf[i] == '.')
		{
			div = i;
		}
		else
		{
			ret += buf[i] - 0x30;
			ret *= 10;
		}
		i ++;
	}

	return ret;
}

unsigned char AscToHex(unsigned char aChar){
    if((aChar>=0x30)&&(aChar<=0x39))
        aChar -= 0x30;
    else if((aChar>=0x41)&&(aChar<=0x46))//��д��ĸ
        aChar -= 0x37;
    else if((aChar>=0x61)&&(aChar<=0x66))//Сд��ĸ
        aChar -= 0x57;
    else aChar = 0xff;
    return aChar; 
} 

eGPSDataSta GPS_checksum(uint8_t *buf, uint32_t len)
{
	eGPSDataSta ret;
	uint32_t i;
	uint8_t checksum;
	uint8_t checksum_read;

	ret = CHECKSUM_ERR;

	checksum = 0;
	checksum_read = 0xFF;

	for(i = 1;i < len;i++) //��һ��ʼ��������Ϊȥ����һ���ַ���$��
	{
	   if(buf[i] == '*')
	   {
	   	if(i < (len - 2))
		{
			checksum_read = 0;
		    checksum_read += AscToHex(buf[i+1]);
			checksum_read = checksum_read << 4;
			checksum_read += AscToHex(buf[i+2]);
			//printf("\n read out buf[%d] : 0x%x buf[%d] : 0x%x",(i+1),buf[i+1],(i+2),buf[i+2]);
		}
	   	break;
	   }
	   checksum = checksum ^ buf[i];
	}
	//printf("\nchecksum is 0x%x\nchecksum_read is 0x%x",checksum,checksum_read);
	if(checksum == checksum_read)
	{
	   ret = NO_ERROR;
	}
	return ret;

}

int GPS_RMC_Parse(char *line, GPS_INFO *GPS)
{
    uint8_t ch, status, tmp;
    float lati_cent_tmp, lati_second_tmp;
    float long_cent_tmp, long_second_tmp;
    float speed_tmp;
    char *buf = line;


    ch = buf[5];
    status = buf[GetComma(2, buf)];


    if (ch == 'C') //���������ַ���C��($GPRMC)
    {
        if (status == 'A') //���������Ч�������
        {
            GPS->NS = buf[GetComma(4, buf)];
            GPS->EW = buf[GetComma(6, buf)];

			GPS->longitude = Get_Double_Number(&buf[GetComma(5, buf)]);
            GPS->latitude = Get_Double_Number(&buf[GetComma(3, buf)]);

			GPS_longitude =  (float)GPS->longitude;
			GPS_latitude =  (float)GPS->latitude;
            

            GPS->latitude_Degree = (int)GPS->latitude / 100; //����γ��
            lati_cent_tmp = (GPS->latitude - GPS->latitude_Degree * 100);
            GPS->latitude_Cent = (int)lati_cent_tmp;
            lati_second_tmp = (lati_cent_tmp - GPS->latitude_Cent) * 60;
            GPS->latitude_Second = (int)lati_second_tmp;

            GPS->longitude_Degree = (int)GPS->longitude / 100;    //���뾭��
            long_cent_tmp = (GPS->longitude - GPS->longitude_Degree * 100);
            GPS->longitude_Cent = (int)long_cent_tmp;
            long_second_tmp = (long_cent_tmp - GPS->longitude_Cent) * 60;
            GPS->longitude_Second = (int)long_second_tmp;

            //speed_tmp = Get_Float_Number(&buf[GetComma(7, buf)]); //�ٶ�(��λ������/ʱ)
            GPS->speed = speed_tmp * 1.85; //1����=1.85����
            //GPS->direction = Get_Float_Number(&buf[GetComma(8, buf)]); //�Ƕ�            

            GPS->D.hour = (buf[7] - '0') * 10 + (buf[8] - '0');        //ʱ��
            GPS->D.minute = (buf[9] - '0') * 10 + (buf[10] - '0');
            GPS->D.second = (buf[11] - '0') * 10 + (buf[12] - '0');
            tmp = GetComma(9, buf);
            GPS->D.day = (buf[tmp + 0] - '0') * 10 + (buf[tmp + 1] - '0'); //����
            GPS->D.month = (buf[tmp + 2] - '0') * 10 + (buf[tmp + 3] - '0');
            GPS->D.year = (buf[tmp + 4] - '0') * 10 + (buf[tmp + 5] - '0') + 2000;

            //UTC2BTC(&GPS->D);
			GPS_VALID = 'A';

			GPS_dwLongitude = long_cent_tmp;
			GPS_dwLongitude /= 60;
			GPS_dwLongitude += GPS->longitude_Degree;

			GPS_dwLatitude = lati_cent_tmp;
			GPS_dwLatitude /= 60;
			GPS_dwLatitude += GPS->latitude_Degree;
			//Get_Longitude_L();
			//Get_Longitude_H();
			//printf("GPS_dwLongitude : 0x%x\n",GPS_dwLongitude);
			//printf("GPS_dwLatitude : 0x%x\n",GPS_dwLatitude);
            
            return 1;
        }
		else
		{
			GPS_VALID = 'V';
			printf("GPS_INVALID\n");
		}        
    }
	else
	{
	 	printf("No GPRMC\n");
	}
    
    return 0;
}

void if_gps_init(void)
{
	OS_DELAY_MS(5000);
	Driver_GPS_Init();
	GPS_Sem = OS_SEM_CREATE();
}

void if_gps_Proc(void)
{
	uint8_t err;

	OS_SEM_TAKE(GPS_Sem,1000,&err);
	
	if(err == pdTRUE)
	{//�����յ�
	  GPS_RMC_Parse(GPS_Data,&GPS);
	  OS_DELAY_MS(1000);
	}
	else
	{//��ʱ
	    printf("No GPS data\n");
	}
}

