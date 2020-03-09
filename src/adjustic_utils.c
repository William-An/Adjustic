/************************************************************
*
* @file:      adjustic_utils.c
* @author:    william
* @email:     china_aisa@live.com
* @version:   v1.0.0
* @date:      03/08/2020
* @brief:     utils function source code
*
************************************************************/

#include "adjustic_utils.h"

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