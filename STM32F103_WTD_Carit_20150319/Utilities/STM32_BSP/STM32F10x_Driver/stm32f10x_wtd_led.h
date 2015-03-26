/****************************************Copyright (c)**************************************************
**                             
**                          company:  Witium Intelligent System Co., Ltd.
**				      �Ϻ��Զ�����ϵͳ���޹�˾   
**                          netaddr:  www.witium.com                  
**                          TEL:      086-21-37774020
**			    FAX:      086-21-37774010
**			    Writer:   Mond Xu    
**                          mobile:   18916777010
**                          email:    mond.xu@witium.com
**
**--------------File Info-------------------------------------------------------------------------------
** File Name:                     stm32f10x_wtd_led.h
** Last modified Date:      2014.08.08
** Last Version:                 v1.0
** Description:                  LED����ͷ�ļ�
** 
**------------------------------------------------------------------------------------------------------
** Created by:                   Carit.Zhu
** Create date:                 2014.08.08
** Version:                         V1.0
** Description:             
**
**------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Description:             
**
********************************************************************************************************/
  
#ifndef __STM32F10X_WTD_LED_H__
#define __STM32F10X_WTD_LED_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
  �û���� 
*********************************************************************************************************/

/*********************************************************************************************************
  End of user's settings �û��趨����
*********************************************************************************************************/ 
#if DRIVER_LED_EN > 0                            
#endif
  
  
/*********************************************************************************************************
** Function name:         	   
** Descriptions:                        
** input parameters:      
**                                  
**                        
** output parameters:     ��      
** Returned value:        �� 
** Created By:            mond.xu
** Created date:          2008.12.14
**--------------------------------------------------------------------------------------------------------
** Modified by:           mond.xu  
** Modified date:         2008.12.17
** Descriptions:                     
**--------------------------------------------------------------------------------------------------------
** Modified by:           mond.xu  
** Modified date:         2008.12.27
** Descriptions:         
**------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#if (DRIVER_LED_EN > 0)
	extern void Driver_LedInit(void);
#endif

/*********************************************************************************************************
** Function name:           
** Descriptions:                       
** Input:                   
**                          
**                          
**                          
** output parameters:       ��      
** Returned value:          �� 
** Created By:              mond.xu
** Created date:            2008.12.14
**--------------------------------------------------------------------------------------------------------
** Modified by:             mond.xu
** Modified date:           2008.12.17
** Descriptions:           
**--------------------------------------------------------------------------------------------------------
** Modified by:             mond.xu
** Modified date:           2008.12.27
** Descriptions:            
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#if (DRIVER_LED_EN > 0)
	extern void Driver_LedSToPCtrl(uint16_t usLedState);
#endif

#ifdef __cplusplus
    }
#endif

#endif /* __STM32F10X_WTD_LED_H__ */
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/