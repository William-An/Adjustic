/**
  ******************************************************************************
  * @file    main.c
  * @author  Weili An
  * @version v1.0.0
  * @date    Mar. 6th, 2020
  * @brief   Main program for Adjustic, an autonomous self-balanced two wheel robot
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

void main() {
	test_stepper();
	for(;;);
}
