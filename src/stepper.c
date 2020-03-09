/************************************************************
*
* @file:      stepper.c
* @author:    william
* @email:     china_aisa@live.com
* @version:   v1.0.0
* @date:      03/08/2020
* @brief:     Stepper motor configuration declaration
*
************************************************************/

// todo update docstring 

#include "stepper.h"

// Bipolar configuration for 28BYJ-48 Stepper motor
extern Stepper_MotorTypeDef _MOTOR_28BYJ48 = {
    .STEPS_PER_REV  = 513,
    .MAX_SPEED      = 240,          // RPM: 10 ~ 15 at 5V with 1/16 reduction gearbox, thus 160
    .STEP_MODE      = FULL_STEPPING,
    .IS_UNIPOLAR    = false,
    .MOTOR_WIRE     = 4
};

extern Stepper_MotorTypeDef _STEPPERONLINE_NEMA_17_59NCM = {
    .STEPS_PER_REV  = 200,  // 1.8 degree per step
    .MAX_SPEED      = 600,
    .STEP_MODE      = HALF_STEPPING,
    .IS_UNIPOLAR    = false,
    .MOTOR_WIRE     = 4
};

extern Stepper_MotorTypeDef* MOTOR_28BYJ48 = &_MOTOR_28BYJ48;

// ************************************************************************
// Generic stepper motor API
// ************************************************************************

/************************************************************
*
* Function: stepInit
* @brief:   Generic init fuction of the stepper driver
* @param:   stepperx, Stepper_DriverTypeDef, type of stepper motor 
*           Driver
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef, motor specs
* @return:  isSuccess, bool, init failed or succeed
*
************************************************************/

bool stepInit (Stepper_DriverTypeDef * stepperx, Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct) {
    // Calculate time for motor to advance one step
    Stepper_MotorStruct->TIM_PER_STEP = 10000000 * 60 / (Stepper_MotorStruct->STEPS_PER_REV * Stepper_MotorStruct->MAX_SPEED);
    return stepperx->init(Stepper_MotorStruct, Stepper_AdditionalConfigStruct);
}

/************************************************************
*
* Function: stepDegree
* @brief:   Generic function for stepping by angle (degree)
* @param:   stepperx, Stepper_DriverTypeDef, type of stepper motor 
*           driver
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef, motor specs
* @param:   deg, float type, positive means rotating to the 
*           clockwise direction facing the motor and negative 
*           value means rotating to the counterclockwise 
*           direction facing the motor.
* @return:  void
*
************************************************************/

void stepDegree (Stepper_DriverTypeDef * Stepperx, Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float degree) {
    Stepperx->stepDegree(Stepper_MotorStruct, Stepper_AdditionalConfigStruct, degree);
}

/************************************************************
*
* Function: stepAngularSpeed
* @brief:   Generic function for stepping angular speed (degree/s)
* @param:   stepperx, Stepper_DriverTypeDef, type of stepper motor 
            driver
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef, motor specs
* @param:   degSpeed, float type, unit degree/s, positive 
*           value means rotating to the clockwise direction 
*           facing the motor; negative value means rotating to
*           the counterclockwise direction facing the motor
* @return:  void
*
************************************************************/

void stepAngularSpeed (Stepper_DriverTypeDef * stepperx, Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float degSpeed) {
    stepperx->stepDegree(Stepper_MotorStruct, Stepper_AdditionalConfigStruct, degSpeed);
}

/************************************************************
*
* Function: stepIRQHandler
* @brief:   generic function to advance steps
* @param:   function parameter name, type, and short explanation
* @return:  void
*
************************************************************/

void stepIRQHandler (Stepper_DriverTypeDef * stepperx, Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct) {
    stepperx->stepIRQHandler(Stepper_MotorStruct, Stepper_AdditionalConfigStruct);
}
