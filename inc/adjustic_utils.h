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


/************************************************************
*
* Function: utilsTimerInit
* @brief:   Simple function to init a timer with certain update
*           frequency
* @param:   timer, timer instance
* @param:   PSC, prescalar, need to subract 1
* @param:   ARR, auto reload value, need to subtract 1
* @param:   IRQChannel, timer irq channel
* @param:   IRQChannelPriority, priority for the timer update 
*           interrupt, from 0 to 3
* @return:  void
*
************************************************************/

void utilsTimerInit (TIM_TypeDef* timer, uint32_t PSC, uint32_t ARR, uint8_t IRQChannel, uint8_t IRQChannelPriority) {

    // Setting timer config struct
    TIM_TimeBaseInitTypeDef timerInitConfig;
    (&timerInitConfig)->TIM_Prescaler       = PSC;
    (&timerInitConfig)->TIM_CounterMode     = TIM_CounterMode_Up;
    (&timerInitConfig)->TIM_Period          = ARR;
    (&timerInitConfig)->TIM_ClockDivision   = TIM_CKD_DIV1;
    
    // Reinitialize timer
    TIM_DeInit(timer);
    TIM_TimeBaseInit(timer, &timerInitConfig);
    
    // Enable timer update interrupt
    TIM_ITConfig(timer, TIM_IT_Update, ENABLE);

    // Enable timer interrupt in NVIC
    NVIC_InitTypeDef timerIrqInit = {
        .NVIC_IRQChannel            = IRQChannel,
        .NVIC_IRQChannelPriority    = IRQChannelPriority,
        .NVIC_IRQChannelCmd         = ENABLE
    };
    NVIC_Init(&timerIrqInit);

    // Enable timer
    TIM_Cmd(timer, ENABLE);
}

#endif