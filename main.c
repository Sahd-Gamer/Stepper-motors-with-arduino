/*
 * Qadir_Bachelorarbeit.c
 *
 * Created: 30.01.2023 21:17:14
 * Author : Sahd1
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

//#include <stdbool.h> // fuer boolean benutzten
// hier definiert, zur Vereinfachung von Tiparbeit

#define stepPinX (1<<PD2) //stepPinX
#define dirPinX (1<<PD5) //DirPinX
#define stepPinY (1<<PD3) //stepPinY
#define dirPinY (1<<PD6) //DirPinY

#define  pi 3.14159265358979323846
//***************************************************
// rpm = 300 U/min = 5/sec = 5 Hz
//***************************************************

//====================================Berechnung von Schritte pro Centimeter ====================//
/*https://www-globalspec-com.translate.goog/pfdetail/motors/stepper-motor-calculations?_x_tr_sl=auto&_x_tr_tl=de&_x_tr_hl=de&_x_tr_pto=wapp
Für riemengetriebene Systeme werden die "Schritte des Schrittmotors pro mm" ausgedrückt als:
Steps per mm = s = (1/p)*(1/microstep)*Motor's number of steps per revolution*(1/Pulley tooth cout)
microsteps= Mikroschritte
Motors's number of steps per revolution; steps_value = 200
p = Riementeilung (mm)
Pulley tooth count = Zähnezahl der Riemenscheibe
*/
//===============================================================================================//
//====================================Berechnung von Schritte pro Centimeter ====================//

//===============================================================================================//
//float steps_value = 200;// Schritte vom Motor für 360 Grad
//float p = 1000; //Riementeilung mm
//float microstep = 0.00625; // microstep 1, 2,4,8, 16
//float z = 50; // Zaehnezahl der Riemenscheibe
// Für andere Berechnungen:
//int turns_per_mm = 6; // 6 Umdrehungen pro mm 
//===============================================================================================//
// Input in Centimeter
//float d = 1;

// Analog
float xpos = 400; //132 in mm für eine Umdrehung
float ypos = 200; // in mm
int32_t mx ;//= 2000 ;//Motormxp fuer X- Richtung
int32_t my ;//Motormxp fuer Y- Richtung

int32_t rotate_x_cw(int32_t mx);
int32_t rotate_x_acw(int32_t mx);
int32_t rotate_y_cw(int32_t my);
int32_t rotate_y_acw(int32_t my);
void movingToX (int32_t mx);
void movingToY (int32_t my);

unsigned char ucFlagBlink_X = 0; // Variable für interrupt von Timer0 für jede 500ms 
unsigned char ucFlagBlink_Y = 0; // Variable für interrupt von Timer0 für jede 500ms 
unsigned char t = 100; // Eingabe der Zeit
int main(void)
{
	Init();//Initialiersierung
	// Umwandlung in Digitatl, in Schritten:
	my = ypos/(0.66)+1;
	mx = -xpos/(0.66)+1;
	
	//==================Berechnung von Geschwindigkeit und Weg======================================//
	//double s = (1/(p*microstep*z))*steps_value; // Steps per mm
	//float steps_p_mm = (turns_per_mm*steps_value)/(microstep);//Schritte pro mm 
	//float ziel = d * 10 *steps_p_mm;// Weg in Centimeter // Eingabe für die Motoren
	//======================================================================================//

    // setup dirPin and stepPin as output // Bitts werden gesetzt = 1
    DDRD |= dirPinX | stepPinX | dirPinY| stepPinY ;
		//movingToX (mx);
		//movingToY (my);
		
	while(1){
		for (int i = 0; i < t; i++ )
		{
			unsigned char z = t;	
			if (t > 0)
			{
				while (1) {
				z %=2;
				if (z == 0)
				{
					t--;
					if (mx > 0)
					{		
							mx--;
							//send low pulse for clockwise direction
							PORTD &= ~dirPinX;
							//send 200 pulses to rotate One full cycle
							PORTD |= stepPinX;
							//_delay_ms(1);
							PORTD &= ~stepPinX;
							_delay_ms(1); //
							
					} else if (mx < 0)
					{
						mx++;
						//mx *=-1;
						//send High pulse for anti-clockwise direction
						PORTD |= dirPinX;
						//send 200 pulses to rotate One full cycle
						
						PORTD |= stepPinX;
						//_delay_ms(1);
						PORTD &= ~stepPinX;
						_delay_ms(1);
					}
					z= t;
					}
				if (z == 1)
				{
					t--;
					if(my > 0)
					{
						my--;
						PORTD &= ~dirPinY;
						//send 200 pulses to rotate One full cycle
						
						PORTD |= stepPinY;
						//_delay_ms(1);
						PORTD &= ~stepPinY;
						_delay_ms(1);
					} else if (my < 0)
					{
						my++;
						//my *=-1;
						//send High pulse for anti-clockwise direction
						PORTD |= dirPinY;
						//send 200 pulses to rotate One full cycle
						
						PORTD |= stepPinY;
						//_delay_ms(1);
						PORTD &= ~stepPinY;
						_delay_ms(1);
					}
					z= t;
				}
				}
			}
			/*if (Timer0_get_10msState() == TIMER_TRIGGERED) //jede 1s wird die Bedingung erfült
			{
				j++;
				if (j == 0) 
				if (j == 1) movingToY(my);
			}*/
			/*if (Timer1_get_10msState() == TIMER1_TRIGGERED) //jede 1s wird die Bedingung erfült
			{
				ucFlagBlink_Y++;
				if (ucFlagBlink_Y) movingToY (my);
				
			}*/
		}
	}
    return 0;
}
void Init(void) //Initialisiert die einzelnen Init Funktionen
{
	Timer0_Init();
	Timer1_Init();
}


void movingToX (int32_t mx) {
			if (mx > 0)
				{
					rotate_x_cw(mx);
				} else if (mx < 0)
				{
					mx *=-1;
					rotate_x_acw(mx);
				}else{
					
				}
}

void movingToY (int32_t my) {
	if (my > 0)
	{
		rotate_y_cw(my);
	} else if (my < 0)
	{
		my *= -1;
		rotate_y_acw(my);
		}else{
	}
}
//X-Motor positiver Richtung
int32_t rotate_x_cw(int32_t mx){
	int32_t i;
	
	//send low pulse for clockwise direction
	PORTD &= ~dirPinX;
	//send 200 pulses to rotate One full cycle
	for(i=0; i<mx; i++){
		
		PORTD |= stepPinX;
		//_delay_ms(1);
		PORTD &= ~stepPinX;
		_delay_ms(1); // Pulsrate = 200 * v
	}

	return 0;
}
//X-Motor negativer Richtung
int32_t rotate_x_acw(int32_t mx){
	int32_t i;
	
	//send High pulse for anti-clockwise direction
	PORTD |= dirPinX;
	//send 200 pulses to rotate One full cycle
	for(i=0; i<mx; i++){
		PORTD |= stepPinX;
		//_delay_ms(1);
		PORTD &= ~stepPinX;
		_delay_ms(1);
	}
	return 0;
}
/////////////////////////////////////////////////////
//Y-Motor positiver Richtung
int32_t rotate_y_cw(int32_t my){
	int32_t i;
	//send low pulse for clockwise direction
	PORTD &= ~dirPinY;
	//send 200 pulses to rotate One full cycle
	for(i=0; i<my; i++){
		
		PORTD |= stepPinY;
		//_delay_ms(1);
		PORTD &= ~stepPinY;
		_delay_ms(1);
	}
	return 0;
}
//Y-Motor negativer Richtung
int32_t rotate_y_acw(int32_t my){
	int32_t i;
	
	//send High pulse for anti-clockwise direction
	PORTD |= dirPinY;
	//send 200 pulses to rotate One full cycle
	for(i=0; i<my; i++){
		PORTD |= stepPinY;
		//_delay_ms(1);
		PORTD &= ~stepPinY;
		_delay_ms(1);
	}
	return 0;
}

