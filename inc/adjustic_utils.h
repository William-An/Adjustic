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

// GPIO pin struct
typedef struct {
    GPIO_TypeDef*   port;
    uint16_t        pin;
} GPIO_PINTypedef;

#endif