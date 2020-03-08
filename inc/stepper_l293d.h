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

#include "stepper.h"    // Include generic stepper control library

// "public" function declaration
bool l293dStepperInit (Stepper_InitTypeDef* Stepper_InitStruct);
void l293dStepperStepbyStep (Stepper_InitTypeDef* Stepper_InitStruct, float steps);
void l293dStepperStepbyAngle (Stepper_InitTypeDef* Stepper_InitStruct, float deg);
void l293dStepperStepbyAngle (Stepper_InitTypeDef* Stepper_InitStruct, float degSpeed);

// todo add some helpful private functions to be implemented
// like wavestep, half step, full step, micro step


#endif
