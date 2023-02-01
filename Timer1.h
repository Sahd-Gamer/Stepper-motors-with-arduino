/*
 * Timer1.h
 *
 * Created: 01.02.2023 16:29:35
 *  Author: Sahd1
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr/io.h>
#include <avr/interrupt.h>

//Rückgabewerte 0 false 1 true
#define TIMER1_TRIGGERED	1
#define	TIMER1_RUNNING	0

// Deklaration der Funktionen
void Timer1_Init(void);
unsigned char Timer1_get_10msState(void);
unsigned char Timer1_get_100msState(void);
unsigned char Timer1_get_1000msState(void);



#endif /* TIMER1_H_ */