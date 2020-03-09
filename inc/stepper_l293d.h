/************************************************************
*
* @file:      stepper_l293d.h
* @author:    william
* @email:     china_aisa@live.com
* @version:   v1.0.0
* @date:      03/08/2020
* @brief:     Stepper driver library using L293D chip (http://www.ti.com/lit/ds/symlink/l293.pdf)
*
************************************************************/

#ifndef __STEPPER_L293D_H__
#define __STEPPER_L293D_H__

#include "stepper.h"            // Include generic stepper control library
#include "adjustic_utils.h"     // Utils types def
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_tim.h"

// ************************************************************************
// L293D configuration struct and functions definition and declaration
// ************************************************************************

#define PIN_COUNT 4 // Only 4 wire configuration stepper motor supported

// TODO Predefine CCR value array for each type of stepping?
// TODO Add microstepping pwm CCR value sequence or generate during initialization

// Additional configuration struct for driver chip

typedef void (*_L293D_stepFunction) (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);

// Config struct
// TODO For Microstepping control, also need an additional PWM timer?
// Or add a PWM control library to project
// todo add steps left for irq to know how many steps it will need to step;
typedef struct {
    GPIO_PINTypedef*    phaseAPosPin;
    GPIO_PINTypedef*    phaseANegPin;
    GPIO_PINTypedef*    phaseBPosPin;
    GPIO_PINTypedef*    phaseBNegPin;
    _L293D_stepFunction stepFunc;
    TIM_TypeDef*        mainTimer;      // Main Timer for stepper motor tick control
    uint32_t            sinceLast;      // Interupt count since last tick, 
    uint16_t            usPerInterrupt; // Specify the time in microsecond between two main timer update interrupt to enable flexible interrupting
    uint8_t             currentTick;    // current tick for stepping (4 ticks for full stepping, 8 for half, etc.) or ticks per step
    uint16_t            usPerTick;      // Time in microsecond for each tick
    uint8_t             MAX_TICKS;      // Maximum ticks for stepping, can use the L293D_TicksPerStepTypedef value
    float               speedRatio;     // Ratio with regard to maximum speed, ranging from 0.0 to 1.0
} L293D_ConfigTypedef;

typedef enum {
    FULL_STEPPING_TICKS = 4,
    HALF_STEPPING_TICKS = 8
} L293D_TicksPerStepTypedef;

// "public" function declaration
void l293dStepperStructInit (L293D_ConfigTypedef* Stepper_AdditionalConfigStruct);

void l293dStepperStructDeInit (L293D_ConfigTypedef* Stepper_AdditionalConfigStruct);

bool l293dStepperInit (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);
void l293dStepperStepbyStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float steps);
void l293dStepperStepDegree (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float deg);
void l293dStepperStepAngularSpeed (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float degSpeed);

// helpful private functions
// like wavestep, half step, full step, micro step
// with the ability to adjust pulseWidthRatio with the pulse width needed to achieve maximum speed to provide speed control
void _l293dWaveStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);
void _l293dFullStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);
void _l293dHalfStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);

// TODO Microstepping needs more reading
// TODO Add enum type to specify stepping fraction?
void _l293dMicroStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);

// Put this in the corresponding timer irq to handle the timing of the stepper motor control
void l293DStepperIRQHandler(Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);

#endif
