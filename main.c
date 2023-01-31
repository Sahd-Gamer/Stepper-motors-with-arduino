/*
 * Qadir_Bachelorarbeit.c
 *
 * Created: 30.01.2023 21:17:14
 * Author : Sahd1
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>




//#include <stdbool.h> // fuer boolean benutzten
// hier definiert, zur Vereinfachung von Tiparbeit
#define stepPinX (1<<PD2) //stepPinX
#define dirPinX (1<<PD5) //DirPinX
#define stepPinY (1<<PD3) //stepPinY
#define dirPinY (1<<PD6) //DirPinY
//#define EN (1<<PD8)
#define  pi 3.14159265358979323846
//***************************************************
// rpm = 300 U/min = 5/sec = 5 Hz
//***************************************************

//====================================Berechnung von Schritte pro Centimeter ====================//
/*https://www-globalspec-com.translate.goog/pfdetail/motors/stepper-motor-calculations?_x_tr_sl=auto&_x_tr_tl=de&_x_tr_hl=de&_x_tr_pto=wapp
F�r riemengetriebene Systeme werden die "Schritte des Schrittmotors pro mm" ausgedr�ckt als:
Steps per mm = s = (1/p)*(1/microstep)*Motor's number of steps per revolution*(1/Pulley tooth cout)
microsteps= Mikroschritte
Motors's number of steps per revolution; steps_value = 200
p = Riementeilung (mm)
Pulley tooth count = Z�hnezahl der Riemenscheibe
*/
//===============================================================================================//
//====================================Berechnung von Schritte pro Centimeter ====================//

//===============================================================================================//
//float steps_value = 200;// Schritte vom Motor f�r 360 Grad
//float p = 1000; //Riementeilung mm
//float microstep = 0.00625; // microstep 1, 2,4,8, 16
//float z = 50; // Zaehnezahl der Riemenscheibe
// F�r andere Berechnungen:
//int turns_per_mm = 6; // 6 Umdrehungen pro mm 
//===============================================================================================//
// Input in Centimeter
//float d = 1;

// Analog
float xpos = -1320; // in mm 
float ypos = -1320; // in mm
int32_t mx ;//= 2000 ;//Motormxp fuer X- Richtung
int32_t my ;//Motormxp fuer Y- Richtung

int32_t rotate_x_cw(int32_t mx);
int32_t rotate_x_acw(int32_t mx);
int32_t rotate_y_cw(int32_t my);
int32_t rotate_y_acw(int32_t my);
void movingToX (int32_t mx);
void movingToY (int32_t my);

int main(void)
{
	// Umwandlung in Digitatl, in Schritten:
	my = ypos/(0.66);
	mx = xpos/(0.66);
	
	//==================Berechnung von Geschwindigkeit und Weg======================================//
	//double s = (1/(p*microstep*z))*steps_value; // Steps per mm
	//float steps_p_mm = (turns_per_mm*steps_value)/(microstep);//Schritte pro mm 
	//float ziel = d * 10 *steps_p_mm;// Weg in Centimeter // Eingabe f�r die Motoren
	//======================================================================================//
	
	
    // setup dirPin and stepPin as output // Bitts werden gesetzt = 1
    DDRD |= dirPinX | stepPinX | dirPinY| stepPinY;
		
		movingToX (mx);
		movingToY (my);
		
		
		
		
		
	    
	
    
    
    return 0;
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
