/*
 * gpio.h
 *
 * Header file for the FRDM_KL26Z LEDs and push-button switch SW1
 *
 * Pins Used
 * ---------
 * Blue LED		PTD5
 * Red LED		PTE29
 * Green LED	PTE31
 * SW1			PTC5
 *
 *  Created on: 23 Sep 2015
 *      Author: nokeeffe
 *      V0.1
 */

#ifndef FRDM_KL26Z_GPIO_H_
#define FRDM_KL26Z_GPIO_H_

#include "fsl_device_registers.h"

//Port Clock Enable for SIM_SCGC5 register
#define PORTE_CLK_ENABLE_MASK 0x2000		//bit 13
#define PORTD_CLK_ENABLE_MASK 0x1000		//bit 12
#define PORTC_CLK_ENABLE_MASK 0x0800		//bit 11

//PCR register masks
#define GPIO_MUX_MASK 0x100u			//Mux field = 001 for GPIO
#define PULLUP_ENABLED_MASK 0x3		//Enable pullup resistor
#define PULLDOWN_ENABLED_MASK 0x2	//Enable pullup resistor
#define LOW_LEVEL_INTERRUPT_MASK	0x8u << 16
#define RISING_EDGE_INTERRUPT_MASK 0x9u <<16
#define FALLNG_EDGE_INTERRUPT_MASK 0xAu <<16
#define EITHER_EDGE_INTERRUPT_MASK 0xBu <<16
#define HIGH_LEVEL_INTERRUPT_MASK 0xCu <<16

//LED and Switch Masks
#define BLUE_LED_MASK 0x20			//pin 5
#define RED_LED_MASK 0x20000000		//pin 29
#define GREEN_LED_MASK 0x80000000	//pin 31
#define SW1_MASK 0x8				//pin 3

//LED macros
#define BLUE_LED_ON() GPIOD_PCOR |= BLUE_LED_MASK
#define RED_LED_ON() GPIOE_PCOR |= RED_LED_MASK
#define GREEN_LED_ON() GPIOE_PCOR |= GREEN_LED_MASK
#define BLUE_LED_OFF() GPIOD_PSOR |= BLUE_LED_MASK
#define RED_LED_OFF() GPIOE_PSOR |= RED_LED_MASK
#define GREEN_LED_OFF() GPIOE_PSOR |= GREEN_LED_MASK

//LED Codes
//#define BLUE 0
#define BLUE 0
#define RED 1
#define GREEN 2
#define ALL 3
#define ON 4
#define OFF 5
#define TOGGLE 6

//Switch codes
#define PULLUP 0
#define PULLDOWN 1
#define LOW_LEVEL 2
#define RISING_EDGE 3
#define FALLING_EDGE 4
#define EITHER_EDGE 5
#define HIGH_LEVEL 6


//GPIO LED and Switch Function Prototypes
void FRDM_KL26Z_LEDs_Configure();
void LED_set(int LED_code, int setting);
void FRDM_KL26Z_SW1_Configure(int pull_resistor, int interrupt_option);
char SW1_read();


#endif /* FRDM_KL26Z_GPIO_H_ */
