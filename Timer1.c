/*
 * Timer1.c
 *
 * Created: 01.02.2023 16:28:59
 *  Author: Sahd1
 */ 
#include "Timer1.h"

//Deklaration der Variablen

unsigned char ucFlagT1_10ms = 0; //wird 1 wenn 10 ms vergangen sind
unsigned char ucFlagT1_100ms = 0; // wird 1 wenn 100 ms vergangen sind
unsigned char ucFlagT1_1000ms = 0; // wird 1 wenn 1s vergangen sind
unsigned char ucCntT1_10ms = 0;
unsigned char ucCntT1_100ms = 0;
void Timer1_Init(void)
{
	TCCR1A = (0 << WGM11) | (0 << WGM10);				// CTC-Modus wird eingestellt
	TCCR1B = (1<<CS11);	// Prescaler=1024 wird gewählt;
	//entspricht dem Eingang Nummer 5 des Prescaler-Multiplexers
	OCR1A = 156;						// 10ms @ f=18,432 MHz
	TIMSK1 = 1 << OCIE1A;				//Freigabe des (Timerintrrupts)CTC-Interrupts
	//für den Timer 0, Kanal A
	sei();								//Freigabe aller Interrupts
}

//Funktion: Timer1_get_10msState
unsigned char Timer1_get_10msState(void)
{
	if(ucFlagT1_10ms == 1)
	{
		ucFlagT1_10ms = 0;
		return TIMER1_TRIGGERED;
	}
	return TIMER1_RUNNING;
}

//Funktion: Timer1_get_100msState
unsigned char Timer1_get_100msState(void)
{
	if(ucFlagT1_100ms == 1)
	{
		ucFlagT1_100ms = 0;
		return TIMER1_TRIGGERED;
	}
	return TIMER1_RUNNING;
}

//Funktion: Timer1_get_1sState
unsigned char Timer1_get_1000msState(void)
{
	if(ucFlagT1_1000ms == 1)
	{
		ucFlagT1_1000ms = 0;
		return TIMER1_TRIGGERED;
	}
	return TIMER1_RUNNING;
}

ISR(TIMER1_COMPA_vect)
{
	ucFlagT1_10ms = 1;
	ucCntT1_10ms++;		// wird jede 10 ms inkrementiert
	if(ucCntT1_10ms == 10)
	// disen kannst du verändern um zb. 1s zu erhalten mal 10
	// und dann sagst du einfach ucFlag1000ms =1 weil es dann erfüllt ist!!!
	{//100ms sind vergangen
		ucCntT1_10ms = 0;
		ucFlagT1_100ms = 1;
		
		// will man z.B. für 1 Sekunde aber die Funktion müssen wir dann in der main
		// wie die andren Funktionen dann Programmieren :)
		ucCntT1_100ms++;
		if (ucCntT1_100ms==10)
		{
			ucCntT1_100ms=0;
			ucFlagT1_1000ms=1;
		}
	}
}