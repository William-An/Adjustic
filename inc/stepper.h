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

// TODO Add docstring

// Motor Step mode setting
typedef enum {
    WAVE_STEPPING,
    FULL_STEPPING,
    HALF_STEPPING,
    MICRO_STEPPING
} Stepper_StepTypeDef;

// Stepper motor configuration
typedef struct {
    uint16_t            STEP_PER_REV;   // Steps per revolution
    Stepper_StepTypeDef STEP_MODE;      // Step mode for the stepper motor
    uint8_t             MOTOR_WIRE;     // Wire for motor, typically 4-wire
    bool                IS_UNIPOLAR;    // Is the motor unipolar or bipolar
} Stepper_MotorTypeDef;

/************************************************************
*
* Function: genericStepInit
* @brief:   Init the stepper driver pointer base on the motor
*           specs
* @param:   motorType, Stepper_MotorTypeDef, motor specs
* @return:  isSuccess, bool, init failed or succeed
*
************************************************************/

typedef bool (*genericStepInit) (Stepper_MotorTypeDef* motorType);

/************************************************************
*
* Function: genericStepbyStep
* @brief:   Step the motor by integer or fraction of steps
* @param:   motorType, Stepper_MotorTypeDef, motor specs
* @param:   steps, float, steps for motor to step, 
* @return:  void
*
************************************************************/

typedef void (*genericStepbyStep) (Stepper_MotorTypeDef* motorType, float steps);

/************************************************************
*
* Function: genericStepDegree
* @brief:   Function pointer for stepping by angle (degree)
* @param:   motorType, Stepper_MotorTypeDef, motor specs
* @param:   deg, float type, positive means rotating to the 
*           clockwise direction facing the motor and negative 
*           value means rotating to the counterclockwise 
*           direction facing the motor.
* @return:  void
*
************************************************************/

typedef void (*genericStepDegree) (Stepper_MotorTypeDef* motorType, float deg);

/************************************************************
*
* Function: genericStepAngularSpeedd
* @brief:   Function pointer for stepping angular speed (degree/s)
* @param:   motorType, Stepper_MotorTypeDef, motor specs
* @param:   degSpeed, float type, unit degree/s, positive 
*           value means rotating to the clockwise direction 
*           facing the motor; negative value means rotating to
*           the counterclockwise direction facing the motor
* @return:  void
*
************************************************************/

typedef void (*genericStepAngularSpeed) (Stepper_MotorTypeDef* motorType, float degSpeed);

// When using this type, client should assign the specific methods first 
// before calling them

typedef struct {
    genericStepInit init;
    genericStepDegree stepDegree;
    genericStepAngularSpeed stepAngularSpeed;
} Stepper_DriverTypeDef;

/************************************************************
*
* Function: stepInit
* @brief:   Generic init fuction of the stepper driver
* @param:   stepperx, Stepper_DriverTypeDef, type of stepper motor 
*           Driver
* @param:   motorType, Stepper_MotorTypeDef, motor specs
* @param:   config, uint_8 pointer, config in bytes
* @param:   configSize, size_t, length of config bytes string
* @return:  isSuccess, bool, init failed or succeed
*
************************************************************/

bool stepInit (Stepper_DriverTypeDef * stepperx, Stepper_MotorTypeDef* motorType) {
    return stepperx->init(motorType);
}

/************************************************************
*
* Function: stepDegree
* @brief:   Generic function for stepping by angle (degree)
* @param:   stepperx, Stepper_DriverTypeDef, type of stepper motor 
*           driver
* @param:   motorType, Stepper_MotorTypeDef, motor specs
* @param:   deg, float type, positive means rotating to the 
*           clockwise direction facing the motor and negative 
*           value means rotating to the counterclockwise 
*           direction facing the motor.
* @return:  void
*
************************************************************/

void stepDegree (Stepper_DriverTypeDef * Stepperx, Stepper_MotorTypeDef* motorType, float degree) {
    Stepperx->stepDegree(motorType, degree);
}

/************************************************************
*
* Function: stepAngularSpeed
* @brief:   Generic function for stepping angular speed (degree/s)
* @param:   stepperx, Stepper_DriverTypeDef, type of stepper motor 
            driver
* @param:   motorType, Stepper_MotorTypeDef, motor specs
* @param:   degSpeed, float type, unit degree/s, positive 
*           value means rotating to the clockwise direction 
*           facing the motor; negative value means rotating to
*           the counterclockwise direction facing the motor
* @return:  void
*
************************************************************/

void stepAngularSpeed (Stepper_DriverTypeDef * stepperx, Stepper_MotorTypeDef* motorType, float degSpeed) {
    stepperx->stepDegree(motorType, degSpeed);
}

#endif
