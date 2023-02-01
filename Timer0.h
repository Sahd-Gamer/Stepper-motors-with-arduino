/*
 * Timer0.h
 *
 * Created: 01.02.2023 11:30:19
 *  Author: Sahd1
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER_TRIGGERED	1
#define	TIMER_RUNNING	0

void Timer0_Init(void);
unsigned char Timer0_get_10msState(void);
unsigned char Timer0_get_100msState(void);
unsigned char Timer0_get_500msState(void);




#endif /* TIMER0_H_ */