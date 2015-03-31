#ifndef __STM32F2X7_WTD_BD_IF_H
#define __STM32F2X7_WTD_BD_IF_H

#include "FreeRTOS.h"
/* Add WTD config includes */
#include "wtdconf.h"

#if BD_EN

void if_bd_init(void);
void if_bd_proc(void);

#endif /* #if DUST */

#endif
