# Adjustic

This is the git repository for the Spring 2020 ECE 362 mini project.  

A self-balanced two wheel robot using:

* STM32F051R8T6
* [MPU9250](https://invensense.tdk.com/products/motion-tracking/9-axis/mpu-9250/) Nine-Axis acclerator, gyroscope, and compass
* [L293D](https://www.st.com/en/motor-drivers/l293d.html) Four channel motor driver
* Stepper motors
* [NRF24L01](https://www.sparkfun.com/datasheets/Components/nRF24L01_prelim_prod_spec_1_2.pdf) 2.4GHz Transceiver

Project Architecture
![Design Structure](./docs/images/structure.png)

## Materials to Learn

* DMA
  * For automatically loading data from sensors and peripherals to memory
  * Textbook chapter 19
* I2C Protocol
  * For communication with acclerator and gyroscope (MPU 9250)
  * Textbook chapter 22.2
* Stepper Motor control
  * Textbook chapter 16
* PID Controller
  * [wiki page](https://en.wikipedia.org/wiki/PID_controller)
* SPI Protocol
  * For wireless controller
  * Textbook chapter 22.3

## TODO

* [ ] Robot component and subsystem architecture design
  * Protocols
  * Interrupts selection
  * Communication Packet design
  * Detailed Program Flowchart/outline
* [ ] Develop schedule and task assignment
