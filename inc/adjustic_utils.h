/************************************************************
*
* @file:      adjustic_utils.h
* @author:    william
* @email:     china_aisa@live.com
* @version:   v1.0.0
* @date:      03/08/2020
* @brief:     Global utils struct definition
*
************************************************************/

#ifndef __ADJUSTIC_UTILS_H__
#define __ADJUSTIC_UTILS_H__

#include "stm32f0xx.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_tim.h"

// GPIO pin struct
typedef struct {
    GPIO_TypeDef*   port;
    uint16_t        pin;    // In @defgroup GPIO_pins_define of stm32f0xx_gpio.h
} GPIO_PINTypedef;

void utilsTimerInit (TIM_TypeDef* timer, uint32_t PSC, uint32_t ARR, uint8_t IRQChannel, uint8_t IRQChannelPriority);

#endif