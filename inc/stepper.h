/************************************************************
 *
 * @file:		stepper.h
 * @author: 	william
 * @email: 		china_aisa@live.com
 * @version: 	v1.0.0
 * @date: 		Mar 7, 2020
 * @brief:		Generic stepper motor control library
 *
 ************************************************************/

#ifndef __STEPPER_H__
#define __STEPPER_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "stm32f0xx.h"
#include "stm32f0xx_gpio.h"

// TODO Add docstring
// TODO Add common motor typedef like 28BYJ

// ************************************************************************
// Stepper motor configuration struct type definition
// ************************************************************************

// Motor Step mode setting
typedef enum {
    WAVE_STEPPING,
    FULL_STEPPING,
    HALF_STEPPING,
    MICRO_STEPPING
} Stepper_StepTypeDef;

// Stepper motor configuration
typedef struct {
    uint16_t            STEPS_PER_REV;  // Steps per revolution, after the gearbox if provided
    uint16_t            MAX_SPEED;      // Maximum speed in RPM for the motor, after the gearbox if provided
    uint32_t            TIM_PER_STEP;   // Time, microsecond, needs to take for the motor to step for one whole step
    Stepper_StepTypeDef STEP_MODE;      // Step mode for the stepper motor
    bool                IS_UNIPOLAR;    // Is the motor unipolar or bipolar
    uint8_t             MOTOR_WIRE;     // Wire for motor, typically 4-wire
} Stepper_MotorTypeDef;

// Bipolar configuration for 28BYJ-48 Stepper motor
Stepper_MotorTypeDef _MOTOR_28BYJ48 = {
    .STEPS_PER_REV  = 513,
    .MAX_SPEED      = 160,          // RPM: 10 ~ 15 at 5V with 1/16 reduction gearbox, thus 160
    .STEP_MODE      = FULL_STEPPING,
    .IS_UNIPOLAR    = false,
    .MOTOR_WIRE     = 4
};

Stepper_MotorTypeDef* MOTOR_28BYJ48 = &_MOTOR_28BYJ48;



// ************************************************************************
// Generic stepper motor driver function and struct definition
// ************************************************************************

/************************************************************
*
* Function: genericStepInit
* @brief:   Init the stepper driver pointer base on the motor
*           specs
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef, motor specs
* @return:  isSuccess, bool, init failed or succeed
*
************************************************************/

typedef bool (*genericStepInit) (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct);

/************************************************************
*
* Function: genericStepbyStep
* @brief:   Step the motor by integer or fraction of steps, 
*           note the pulse width must not less than the time 
*           which the motor needs to rotate one step
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef, motor specs
* @param:   steps, float, steps for motor to step, 
* @return:  void
*
************************************************************/

typedef void (*genericStepbyStep) (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float steps);

/************************************************************
*
* Function: genericStepDegree
* @brief:   Function pointer for stepping by angle (degree)
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef, motor specs
* @param:   deg, float type, positive means rotating to the 
*           clockwise direction facing the motor and negative 
*           value means rotating to the counterclockwise 
*           direction facing the motor.
* @return:  void
*
************************************************************/

typedef void (*genericStepDegree) (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float deg);

/************************************************************
*
* Function: genericStepAngularSpeedd
* @brief:   Function pointer for stepping angular speed (degree/s)
* @param:   Stepper_MotorStruct, Stepper_MotorTypeDef, motor specs
* @param:   degSpeed, float type, unit degree/s, positive 
*           value means rotating to the clockwise direction 
*           facing the motor; negative value means rotating to
*           the counterclockwise direction facing the motor
* @return:  void
*
************************************************************/

typedef void (*genericStepAngularSpeed) (Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct, float degSpeed);

// When using this type, client should assign the specific methods first 
// before calling them

typedef struct {
    genericStepInit init;
    genericStepDegree stepDegree;
    genericStepAngularSpeed stepAngularSpeed;
} Stepper_DriverTypeDef;

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
* @param:   config, uint_8 pointer, config in bytes
* @param:   configSize, size_t, length of config bytes string
* @return:  isSuccess, bool, init failed or succeed
*
************************************************************/

bool stepInit (Stepper_DriverTypeDef * stepperx, Stepper_MotorTypeDef* Stepper_MotorStruct, void* Stepper_AdditionalConfigStruct) {
    // Calculate time for motor to advance one step
    Stepper_MotorStruct->TIM_PER_STEP = round(1000000.0 * 60 / Stepper_MotorStruct->STEPS_PER_REV * Stepper_MotorStruct->MAX_SPEED);
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

#endif
