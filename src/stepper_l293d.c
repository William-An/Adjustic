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

// ************************************************************************
// "Public" function for generic stepper driver
// ************************************************************************

/************************************************************
*
* Function: l293dStepperInit
* @brief:   Init the driver chip for the inputs, check for 
*           port and pin configuration
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef*, pointer
*           to the motor specs
* @param:   Stepper_AdditionalConfigStruct, void*, configuration
*           struct for the l293d, need to cast to L293D_ConfigTypedef
* @return:  whether the initialization if successful
*
************************************************************/

bool l293dStepperInit (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct) {
    // TODO check for ports

    // todo Configure timer as well
    // Assign step function based on step mode of the motor 
    switch (Stepper_MotorStruct->STEP_MODE)
    {
    case WAVE_STEPPING:
        ((L293D_ConfigTypedef *) Stepper_AdditionalConfigStruct)->stepFunc = _l293dWaveStep;
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

void L293D_TIMING_Channel_IRQHandler(Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct) {

}