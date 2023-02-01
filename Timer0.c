/*
 * Timer0.c
 *
 * Created: 01.02.2023 11:28:16
 *  Author: Sahd1
 */ 
#include <avr/io.h>
#include "Timer0.h"

unsigned char ucFlag10ms = 0;
unsigned char ucFLag100ms = 0;
unsigned char ucCnt100ms = 0;
unsigned char ucFlag500ms=0;
unsigned char ucCnt500ms=0;


void Timer0_Init(void)
{
	//Set interrupt mode
	TCCR0A |= (1 << WGM01); //CTC mode (Clear Timer on Compare)

	//Set prescaler
	TCCR0B |=  (1<< CS00) | (1 << CS02) ; //1024 prescaler set

	//8-bit value that is continuously compared with the counter value (TCNT0)
	OCR0A = 156; //Total Timer Ticks, https://eleccelerator.com/avr-timer-calculator/ by setting Real Time in 0.01

	//Enable specific interrupt (the interrupt that we want to use)
	TIMSK0 = 1 << OCIE0A;//enable OCIE0A in TIMSK0 interrupt
	sei();//set external interrupt. It sets the I-bit in the Status Register. [Datasheet page 111, Bit 2 ]

}

unsigned char Timer0_get_10msState(void)
{
	if(ucFlag10ms == 1)
	{
		ucFlag10ms = 0;
		return TIMER_TRIGGERED;
	}
	return TIMER_RUNNING;
}

unsigned char Timer0_get_100msState(void)
{
	if(ucFlag500ms == 1)
	{
		ucFlag500ms = 0;
		return TIMER_TRIGGERED;
	}
	return TIMER_RUNNING;
}

unsigned char Timer0_get_500msState(void)
{
	if(ucFlag500ms == 1)
	{
		ucFlag500ms = 0;
		return TIMER_TRIGGERED;
	}
	return TIMER_RUNNING;
}

ISR(TIMER0_COMPA_vect)
{
	ucFlag10ms = 1;
	ucCnt100ms++;
	if(ucCnt100ms == 10)
	{//100ms sind vergangen
		ucCnt100ms = 0;
		ucFLag100ms = 1;
		ucCnt500ms++;
		if (ucCnt500ms==5)
		{
			ucCnt500ms=0;
			ucFlag500ms=1;
		}
	}
}