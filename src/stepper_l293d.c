/************************************************************
*
* @file:      stepper_l293d.c
* @author:    william
* @email:     china_aisa@live.com
* @version:   v1.0.0
* @date:      03/08/2020
* @brief:     Source code for stepper motor driver using l293d
*
************************************************************/

#include "stepper_l293d.h"

// TODO Complete the function definition
// TODO Motor control need to be concurrent to minimize the cpu
// TODO Cost on delaying
// TODO Thus require an way to set the timer channel and automate the stepping process
// TODO Client should only need to issue command and not waiting for the process to be completed
// TODO Kind of like DMA
// TODO Quantized the timing: full stepping takes four ticks for a period, half takes 8, 1/4 takes 16 ticks, use this to control the motor
// TODO Use timer to manage ticks

// TODO Move speed ratio to config struct? so that the irq can access it for timing


// ************************************************************************
// "Public" function for generic stepper driver
// ************************************************************************

/************************************************************
*
* Function: l293dStepperInit
* @brief:   Init the driver chip for the inputs, check for 
*           port and pin configuration. This function assume
*           you have already enable the RCC clock for the gpio
*           pins and have a running timer that provide constant
*           update interrupt
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef*, pointer
*           to the motor specs
* @param:   Stepper_AdditionalConfigStruct, void*, configuration
*           struct for the l293d, need to cast to L293D_ConfigTypedef
* @return:  whether the initialization if successful
*
************************************************************/

bool l293dStepperInit (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct) {
    // NOTE: Client should enable the RCC clocks for the ports and timer prior to calling the init function
    // Perform a loose check just in case
    // Check if any of the GPIO port is enabled
    uint32_t ahbTestMask = RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIODEN | RCC_AHBENR_GPIOFEN;
    if ((RCC->AHBENR & ahbTestMask) == 0)
        return false;
    
    // Check if any of the timer is enabled
    uint32_t apb1TestMask = RCC_APB1ENR_TIM14EN | RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM6EN;
    uint32_t apb2TestMask = RCC_APB2ENR_TIM15EN | RCC_APB2ENR_TIM16EN | RCC_APB2ENR_TIM17EN | RCC_APB2ENR_TIM1EN;
    if ((RCC->APB1ENR & apb1TestMask) == 0 && (RCC->APB2ENR) & apb2TestMask == 0)
        return false;

    // Preparing the configuration struct
    L293D_ConfigTypedef* config = (L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct;

    // Set ticks time
    switch (Stepper_MotorStruct->STEP_MODE) {
        case WAVE_STEPPING:
        case FULL_STEPPING:
        default:
            config->usPerTick = Stepper_MotorStruct->TIM_PER_STEP / config->MAX_TICKS;
            break;
        case HALF_STEPPING:
            config->usPerTick = Stepper_MotorStruct->TIM_PER_STEP / config->MAX_TICKS;
            break;
        case MICRO_STEPPING:
            // todo add ticks per step
            break;
    }
    
    GPIO_PINTypedef* controlPins[PIN_COUNT] = {
        config->phaseAPosPin, 
        config->phaseANegPin,
        config->phaseBPosPin,
        config->phaseBNegPin
    };

    // Configuring pin mode
    // output, low speed, push-pull, no pull resistor
    GPIO_InitTypeDef pinInitConfig[PIN_COUNT];
    for (int i = 0; i < PIN_COUNT; i++) {
        (&pinInitConfig[i])->GPIO_Pin   = (controlPins[i])->pin;
        (&pinInitConfig[i])->GPIO_Mode  = GPIO_Mode_OUT;
        (&pinInitConfig[i])->GPIO_Speed = GPIO_Speed_Level_1;   // Since Stepper motor is a relatively slow device
        (&pinInitConfig[i])->GPIO_OType = GPIO_OType_PP;
        (&pinInitConfig[i])->GPIO_PuPd  = GPIO_PuPd_NOPULL;
    }

    // Initialize control pins
    for (int i = 0; i < PIN_COUNT; i++) {
        GPIO_Init(controlPins[i]->port, (&pinInitConfig[i]));
    }

    // Assign step function based on step mode of the motor 
    switch (Stepper_MotorStruct->STEP_MODE)
    {
    case WAVE_STEPPING:
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->stepFunc = _l293dWaveStep;
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->MAX_TICKS = 4;
        break;
    case FULL_STEPPING:
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->stepFunc = _l293dFullStep;
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->MAX_TICKS = 4;
        break;
    case HALF_STEPPING:
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->stepFunc = _l293dHalfStep;
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->MAX_TICKS = 8;
        break;
    // TODO Breakdown to 1/4, 1/8, 1/16 or add configuration?
    case MICRO_STEPPING:
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->stepFunc = _l293dMicroStep;
        break;
    default:
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->stepFunc = _l293dFullStep;
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->MAX_TICKS = 4;
        break;
    }

    return true;
}

/************************************************************
*
* Function: l293dStepperStepbyStep
* @brief:   Advance number of steps in maximum speed
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef*, pointer
*           to the motor specs
* @param:   Stepper_AdditionalConfigStruct, void*, configuration
*           struct for the l293d, need to cast to L293D_ConfigTypedef
* @param:   steps, float, steps need to advance, positive for
*           clockwise advance, negative for counterclockwise advance
* @return:  void
*
************************************************************/

void l293dStepperStepbyStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float steps) {

}

/************************************************************
*
* Function: l293dStepperStepDegree
* @brief:   Advance a certain degree in maximum speed
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef*, pointer
*           to the motor specs
* @param:   Stepper_AdditionalConfigStruct, void*, configuration
*           struct for the l293d, need to cast to L293D_ConfigTypedef
* @param:   deg, float, degree need to advance, positive for
*           clockwise advance, negative for counterclockwise advance
* @return:  void
*
************************************************************/

void l293dStepperStepDegree (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float deg) {

}

/************************************************************
*
* Function: l293dStepperStepAngularSpeed
* @brief:   Advance in controllable speed
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef*, pointer
*           to the motor specs
* @param:   Stepper_AdditionalConfigStruct, void*, configuration
*           struct for the l293d, need to cast to L293D_ConfigTypedef
* @param:   degSpeed, float, degree/second need to advance, positive for
*           clockwise advance, negative for counterclockwise advance
* @return:  void
*
************************************************************/

void l293dStepperStepAngularSpeed (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float degSpeed) {

}

// ************************************************************************
// "Private" helper function
// ************************************************************************

void _l293dWaveStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float speedRatio) {

}

void _l293dFullStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float speedRatio) {

}

void _l293dHalfStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float speedRatio) {

}

// TODO
void _l293dMicroStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct) {

}

// ************************************************************************
// Timer interrupt handler function to control the timing and stepping
// ************************************************************************

// TODO Need to handle the case when CRR is set to 0 while the counter value is also 0, happens every 43000 seconds if using a 32-bit counter
void L293D_TIMING_Channel_IRQHandler(Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct) {
    // Advance one tick if timing has matched

}