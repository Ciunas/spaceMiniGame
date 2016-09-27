/*
 * pit_kl26z.h
 *
 *  Created on: 21 Sep 2015
 *      Author: nokeeffe
 */
/*
 * pit.h
 *
 *  Created on: 19 Oct 2012
 *      Author: nokeeffe
 *
 *      Header File for PIT
 */

#ifndef PIT_H_
#define PIT_H_

//Peripheral bus frequency
#define PERIPHERAL_BUS_FREQUENCY 12000000

//PIT function prototypes
void PIT0_Configure_interrupt_mode(float time_delay_secs);
void PIT1_Configure_interrupt_mode(float time_delay_secs);
void PIT_delay(float time_delay_secs);


#endif /* PIT_H_ */


