/*
 * gpio.c
 *
 *  Created on: 23 Sep 2015
 *      Author: nokeeffe
 */

#include "gpio.h"

/*------------------------------------------------------------------------
 * void FRDM_KL26Z_LEDs_Configure()
 *
 * Function to configure the FRDM_KL26Z RGB LED
 * Blue LED		PTD5
 * Red LED		PTE29
 * Green LED	PTE31
 *
 * LED pins are configured as GPIO output pins.
 * Pins are set on initialisation to turn off the 3 LEDs
 * A logic 0 turns on a LED
 -----------------------------------------------------------------------*/
void FRDM_KL26Z_LEDs_Configure()
{
	//enable port clocks
	SIM_SCGC5 |= PORTE_CLK_ENABLE_MASK | PORTD_CLK_ENABLE_MASK;
	//configure blue LED
	PORTD_PCR5 |= 0x1u << 8;
	GPIOD_PDDR |= BLUE_LED_MASK;	//output
	GPIOD_PSOR |= BLUE_LED_MASK;	//LED off
	//configure red LED
	PORTE_PCR29 |= 0x1u << 8;
	GPIOE_PDDR |= RED_LED_MASK;		//output
	GPIOE_PSOR |= RED_LED_MASK;		//LED off
	//configure blue LED
	PORTE_PCR31 |= 0x1u << 8;
	GPIOE_PDDR |= GREEN_LED_MASK;	//output
	GPIOE_PSOR |= GREEN_LED_MASK;	//LED off
}

/*------------------------------------------------------------------------
 * void LED_set(int LED_code, int setting)
 *
 * Function to set/clear/toggle a single LED or all 3 LEDs together
 *
 * Passed Parameters:
 * LED_code	-	LED/s to control
 * 				Options -	BLUE, RED, GREEN, ALL
 *
 * setting -	action to be performed on LED
 *  			Options -	ON, OFF, TOGGLE
 *
 * Example Usage - LED_set(GREEN, ON);	//turn on green LED
 --------------------------------------------------------------------  -*/
void LED_set(int LED_code, int setting)
{
	if(setting == ON)
	{
		switch(LED_code)
		{
		//case BLUE:break;
		case BLUE:	GPIOD_PCOR |= BLUE_LED_MASK;
			break;
		case RED:	GPIOE_PCOR |= RED_LED_MASK;
			break;
		case GREEN:	GPIOE_PCOR |= GREEN_LED_MASK;
			break;
		case ALL:	GPIOD_PCOR |= BLUE_LED_MASK;
					GPIOE_PCOR |= RED_LED_MASK;
					GPIOE_PCOR |= GREEN_LED_MASK;
					break;

		default: break;
		}
	}
	else if(setting == OFF)
	{
		switch(LED_code)
		{
		//case BLUE:break;
		case BLUE:	GPIOD_PSOR |= BLUE_LED_MASK;
			break;
		case RED:	GPIOE_PSOR |= RED_LED_MASK;
			break;
		case GREEN:	GPIOE_PSOR |= GREEN_LED_MASK;
			break;
		case ALL:	GPIOD_PSOR |= BLUE_LED_MASK;
					GPIOE_PSOR |= RED_LED_MASK;
					GPIOE_PSOR |= GREEN_LED_MASK;
					break;

		default: break;
		}
	}
	else if(setting == TOGGLE)
	{
		switch(LED_code)
		{
		//case BLUE:break;
		case BLUE:	GPIOD_PTOR |= BLUE_LED_MASK;
			break;
		case RED:	GPIOE_PTOR |= RED_LED_MASK;
			break;
		case GREEN:	GPIOE_PTOR |= GREEN_LED_MASK;
			break;
		case ALL:	GPIOD_PTOR |= BLUE_LED_MASK;
					GPIOE_PTOR |= RED_LED_MASK;
					GPIOE_PTOR |= GREEN_LED_MASK;
					break;

		default: break;
		}

	}
}

/*
 * void FRDM_KL26Z_SW1_Configure(int pull_resistor, int interrupt)
 *
 * Function to configure the push-button switch SW1 on pin PTC3
 *
 * Passed Parameters:
 * pull_resistor	-	option for a pullup/pulldown resistor
 * 						Options -	PULLUP, PULLDOWN 0,
 *
 * setting -	action to be performed on LED
 *  			Options -	LOW_LEVEL, RISING_EDGE, FALLING_EDGE, EITHER_EDGE, HIGH_LEVEL, 0
 *
 *
 * Example Usage: FRDM_KL26Z_SW1_Configure(0,0);	//configure as an input pin only
 * FRDM_KL26Z_SW1_Configure(PULLUP, 0);	//configure as an input pin with pullup resistor
 * FRDM_KL26Z_SW1_Configure(PULLUP, FALLING_EDGE);   //configure as an input pin with pullup resistor and falling edge interrupt
 */
void FRDM_KL26Z_SW1_Configure(int pull_resistor, int interrupt_option)
{
	//enable port clock
	SIM_SCGC5 |= PORTC_CLK_ENABLE_MASK;
	PORTC_PCR3 |= GPIO_MUX_MASK;	//configure as GPIO pin

	//configure pullup/pulldown resistor
	if(pull_resistor == PULLUP)
		PORTC_PCR3 |= PULLUP_ENABLED_MASK;	//PE=1, PS=1
	else if(pull_resistor == PULLDOWN)
		PORTC_PCR3 |= PULLDOWN_ENABLED_MASK;	//PE=1,PS=0

	//configure interrupt
	switch(interrupt_option)
	{
	case LOW_LEVEL: PORTC_PCR3 |= LOW_LEVEL_INTERRUPT_MASK;
	break;
	case RISING_EDGE: PORTC_PCR3 |= RISING_EDGE_INTERRUPT_MASK;
	break;
	case FALLING_EDGE: PORTC_PCR3 |= FALLNG_EDGE_INTERRUPT_MASK;
	break;
	case EITHER_EDGE: PORTC_PCR3 |= EITHER_EDGE_INTERRUPT_MASK;
	break;
	case HIGH_LEVEL: PORTC_PCR3 |= HIGH_LEVEL_INTERRUPT_MASK;
	break;
	default:
	break;
	}
}

/*------------------------------------------------------------------
 * char SW1_read()
 *
 * Function to return the logic level of the SW1 push-button switch
 * SW1 is connected to GPIO pin PTC3
 -------------------------------------------------------------------*/
char SW1_read()
{
	if(GPIOC_PDIR & SW1_MASK)	//input = 1
		return 1;
	else
		return 0;
}
