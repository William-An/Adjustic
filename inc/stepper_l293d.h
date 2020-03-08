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

// Additional configuration struct for driver chip
// Pins for the control circuit
typedef struct {
    GPIO_PINTypedef* phaseAPosPin;
    GPIO_PINTypedef* phaseANegPin;
    GPIO_PINTypedef* phaseBPosPin;
    GPIO_PINTypedef* phaseBNegPin;
} L293D_ConfigTypedef;

// "public" function declaration
bool l293dStepperInit (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);
void l293dStepperStepbyStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float steps);
void l293dStepperStepDegree (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float deg);
void l293dStepperStepAngularSpeed (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float degSpeed);

// helpful private functions
// like wavestep, half step, full step, micro step
// with the ability to adjust pulseWidthRatio with the pulse width needed to achieve maximum speed to provide speed control
void _l293dWaveStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float pulseWidthRatio);
void _l293dFullStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float pulseWidthRatio);
void _l293dHalfStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float pulseWidthRatio);

// TODO Microstepping needs more reading
void _l293dMicroStep (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);


#endif
