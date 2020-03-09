/************************************************************
 *
 * @file:		test_stepper.c
 * @author: 	william
 * @email: 		china_aisa@live.com
 * @version: 	v1.0.0
 * @date: 		Mar 8, 2020
 * @brief:		Testing stepper motor library
 *
 ************************************************************/

// testing
#include "stepper.h"
#include "stepper_l293d.h"

Stepper_DriverTypeDef* driver;
L293D_ConfigTypedef _config;
L293D_ConfigTypedef* config = &_config;
Stepper_MotorTypeDef* motor;

void setup();

int test_stepper(void)
{
	Stepper_MotorTypeDef _motor = _MOTOR_28BYJ48;
	motor = &_motor;
	setup();
	for(;;);
}


// Use timer 6 for delay
void TIM6_DAC_IRQHandler() {
	L293D_TIMING_Channel_IRQHandler(motor, (void *) config);
}

void setup() {
	driver = (Stepper_DriverTypeDef*) malloc(sizeof(Stepper_DriverTypeDef));
	driver->init 				= l293dStepperInit;
	driver->stepAngularSpeed 	= l293dStepperStepAngularSpeed;
	driver->stepDegree			= l293dStepperStepbyStep;

	// Configure motor
	motor->STEP_MODE = FULL_STEPPING;
	motor->MAX_SPEED = 240;

	// Initialize stepper motor driver
	l293dStepperStructInit(config);
	// PA0 PA1 PA2 PA3
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	config->phaseAPosPin->port 	= GPIOA;
	config->phaseAPosPin->pin	= GPIO_Pin_0;
	config->phaseANegPin->port 	= GPIOA;
	config->phaseANegPin->pin	= GPIO_Pin_1;
	config->phaseBPosPin->port 	= GPIOA;
	config->phaseBPosPin->pin	= GPIO_Pin_2;
	config->phaseBNegPin->port 	= GPIOA;
	config->phaseBNegPin->pin	= GPIO_Pin_3;

	// Set stepper motor timer
	config->mainTimer = TIM6;
	config->usPerInterrupt = 1000;
	config->MAX_TICKS = FULL_STEPPING_TICKS;

	// Initialize stepper motor
	stepInit(driver, motor, (void *) config);

	// Configure and start timer
	utilsTimerInit(TIM6, 48 - 1, 1000 - 1, TIM6_DAC_IRQn, 2);


}
