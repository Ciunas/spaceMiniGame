/*

 * pit_kl26z.c
 *
 *  Created on: 21 Sep 2015
 *      Author: nokeeffe
 */


/*
 * pit.c
 *
 *  Created on: 19 Oct 2012
 *      Author: nokeeffe
 */

//#include "common.h"
#include "fsl_device_registers.h"
#include "pit_kl26z.h"

/*****************************************************************************************
 * Function to configure the PIT in interrupt mode
 * The function is passed the timer reload value in seconds (float)
 * The timer interrupt in enabled in the module and the NVIC and the timer is started
 * An ISR must be written to service the PIT interrupt
 * ***************************************************************************************/
void PIT0_Configure_interrupt_mode(float time_delay_secs)
{
	unsigned long reload_value = (unsigned long)(PERIPHERAL_BUS_FREQUENCY * time_delay_secs);
	//Configure NVIC
	NVIC_ClearPendingIRQ(22);
	NVIC_EnableIRQ(22);

	//Enable PIT peripheral clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

	//Configure PIT
	PIT_MCR = 0x01ul;			//PIT timer clock enabled
	PIT_TCTRL0 = 0;				//timer disabled and interrupt turned off
	PIT_TFLG0 = 0x01ul;			//Clear interrupt flag
	PIT_LDVAL0 = reload_value;	//time is calculated from parameter passed to function

	PIT_TCTRL0 |= 0x03ul;		//enable timer and interrupt
}

/*****************************************************************************************
 * Function to configure the PIT in interrupt mode
 * The function is passed the timer reload value in seconds (float)
 * The timer interrupt in enabled in the module and the NVIC and the timer is started
 * An ISR must be written to service the PIT interrupt
 * ***************************************************************************************/
void PIT1_Configure_interrupt_mode(float time_delay_secs)
{
	unsigned long reload_value = (unsigned long)(PERIPHERAL_BUS_FREQUENCY * time_delay_secs);
	//Configure NVIC
	NVIC_ClearPendingIRQ(22);
	NVIC_EnableIRQ(22);

	//Enable PIT peripheral clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

	//Configure PIT
	PIT_MCR = 0x01ul;			//PIT timer clock enabled
	PIT_TCTRL1 = 0;				//timer disabled and interrupt turned off
	PIT_TFLG1 = 0x01ul;			//Clear interrupt flag
	PIT_LDVAL1 = reload_value;	//time is calculated from parameter passed to function

	PIT_TCTRL1 |= 0x03ul;		//enable timer and interrupt
}

/*****************************************************************************************
 * Function to configure the PIT in polling mode
 * The function is passed the timer reload value in seconds (float)
 * The timer is started
 * The timer interrupt flag should be polled to determine when the timer has reached 0
 * ***************************************************************************************/

void PIT_delay(float time_delay_secs)
{
	unsigned long reload_value = (unsigned long)(PERIPHERAL_BUS_FREQUENCY * time_delay_secs);

	//Enable PIT peripheral clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

	//Configure PIT
	PIT_MCR = 0x01ul;		//PIT timer clock enabled
	PIT_TCTRL0 = 0;			//timer disabled and interrupt turned off
	PIT_TFLG0 = 0x01ul;		//Clear interrupt flag
	PIT_LDVAL0 = reload_value;	//time is calculated from parameter passed to function
	PIT_TCTRL0 |= 0x01ul;	//enable timer
	while(PIT_TFLG0==0)	//wait for timer overflow flag
	{}
	PIT_TFLG0 = 0x01u;	//Clear interrupt flag
	PIT_TCTRL0 = 0;		//timer disabled
}


