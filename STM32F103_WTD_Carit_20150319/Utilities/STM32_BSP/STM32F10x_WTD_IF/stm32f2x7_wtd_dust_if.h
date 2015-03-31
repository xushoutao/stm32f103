#ifndef __STM32F2X7_WTD_DUST_IF_H
#define __STM32F2X7_WTD_DUST_IF_H

#include "FreeRTOS.h"
/* Add WTD config includes */
#include "wtdconf.h"

#if DUST_EN

void if_dust_init(void);
void if_dust_proc(void);

#endif /* #if DUST */

#endif
