#ifndef __STM32F2X7_WTD_NOISE_IF_H
#define __STM32F2X7_WTD_NOISE_IF_H

#include "FreeRTOS.h"
/* Add WTD config includes */
#include "wtdconf.h"

#if NOISE_EN

void if_noise_init(void);
void if_noise_proc(void);

#endif /* #if DUST */

#endif
