/*
 * Qadir_Bachelorarbeit.c
 *
 * Created: 01.01.2023 21:17:14
 * Author : Sahd1
 
 */ 

#define F_CPU 16000000UL
#include "main.h"// Einschlieﬂung von Header-Datei "main.h"
//#include <stdbool.h> // fuer boolean benutzten



//============================================Globale Definitionen===============================================================================//

#define stepPinX (1<<PD2) //stepPinX
#define dirPinX (1<<PD5) //DirPinX
#define stepPinY (1<<PD3) //stepPinY
#define dirPinY (1<<PD6) //DirPinY
#define  pi 3.14159265358979323846

//============================================Globale Definitionen abgeschlossen =================================================================//

//============================================ Eingabe von Positionen, Zeit und Geschwindigkeit ==================================================//

// Analoge Eingaben: in X- und Y-Richtung in milimeter:
float xpos = 264; // Dabei entspricht: 132 mm Umfang der Rolle und das entspricht 360∞ bzw. 200 Motor Schritte, da 1 Schritt 1,8∞ entspricht
float ypos = 132; //

// Hier kann die Zeit eingegeben werden in Milisekunden
float t =10000; // Zeit in Milisekunden

//============================================ Eingabe von Positionen, Zeit und Geschwindigkeit Beendet ===========================================//

//======================================================== Verwendetet Variablen:===================================================================//

// mx und my sind die Variablen die nacher fuer die Umwandlung von Analoge 
//Eingaben ins Digitale, sprich in Motorschritte umgewandelt werden.
int32_t mx ;//X- Richtung
int32_t my ;//Y- Richtung

// diese Variabeln werden daf¸r verwendet, damit die Verh‰tnisse zwischen my und mx Schritten ausgerechnet werden,
// um die Motoren dem entsprechend zu takten.
float i_steps_x;
float i_steps_y;

// Berechnug der Schrittdauer; Schritte/gew¸nschte Zeit Interval
double schrittdauer_x;
double schrittdauer_y;

//========================================================Verwendete Variablen abgeschlossen =============================================//


//======================================================== Verwendetet Funktionen:========================================================//

//Die Parameter mx und my werden in diese Funktionen uebergeben, und diese Argumente
//werden intern ueber if-Bedingungen an die Funktionen "rotate_x_cw" und "rotate_x_acw"
//bzw. f¸r movingToY die Funktoinen "rotate_y_cw" und "rotate_y_acw" uebergeben
void movingToX (int32_t mx);
void movingToY (int32_t my);
 
// Beide Schrittmotoren in Positive und Negative Richtungen Fahren lassen jeweils um 360∞, also mit 200 Schritten
int32_t rotate_x_cw(int32_t mx);// Schrittmotor X in nach Uhrzeigersin drehen
int32_t rotate_x_acw(int32_t mx); // hier in die andere Richtung
int32_t rotate_y_cw(int32_t my);//  Schrittmotor Y in nach Uhrzeigersin drehen
int32_t rotate_y_acw(int32_t my); // hier in die andere Richtung

//========================================================Funktionen Beendet===============================================================//



//========================================Hauptprogramm=====================================================================================//
int main(void)
{
	//Initialiersierung von Initfunktionen:
	//Init();
		
	// Umwandlung der Positionen von mm in Schritten: (Digitalisierung)
	mx = xpos/(0.66);
	if(mx > 0 ) mx +=1;
	if(mx < 0 ) mx -=1;
	my = ypos/(0.66);
	if(my > 0 ) my +=1;
	if(my < 0 ) my -=1;
	
	// Berechnug der Schrittdauer; Schritte/gew¸nschte Zeit Interval
	schrittdauer_x = t/mx;
	schrittdauer_x= (int)(schrittdauer_x + 0.5);
	schrittdauer_y = t/my;
	schrittdauer_y = (int)(schrittdauer_y + 0.5);
	//!!!!!!!!!!!!!!!!!!! schritt_zeit_x und i_steps_x sind gliech!!!!!!!!!!!!!!!!!!!??????????
	// Berechnung der Schrittverh‰ltnisse von my und my 
	if (mx > my || mx == my)
	{
		i_steps_x = mx/my;
		i_steps_x = (int)(i_steps_x + 0.5);
		i_steps_y = 1/i_steps_x;
		i_steps_y = (int)(i_steps_y + 0.5);
	}
	if (my > mx)
	{
		i_steps_y = my/mx;
		i_steps_y = (int)(i_steps_y + 0.5);
		i_steps_x = 1/i_steps_y;
		i_steps_x = (int)(i_steps_x + 0.5);
	}

    // setup dirPin and stepPin as output // Bitts werden gesetzt = 1
    DDRD |= dirPinX | stepPinX | dirPinY| stepPinY ;
		//movingToX (mx);
		//movingToY (my);
	//========================================While-Schleife====================================================//
	while(1){
		
		for (int i = 0; i < t; i++ )
		{
			int32_t z = t;
				
			if (t > 0)
			{
				while (1) {
				z %=2;
				if (z == 0)
				{
					t--;//Die Zeit wird um i_steps_x verringert weil die Funktion _delay_ms so oft gestartet wird 
					
					if (mx > 0)
					{	
						int flagx = 0;
						// Schrittdauer daurch laufen:
						for (int j = 0; j < schrittdauer_x; j++)
						{	
							_delay_ms(1);
							flagx++;
							if (flagx == schrittdauer_x)
							{
									for (int i = 0; i < i_steps_x; i++)
									{
										mx--;
										//send low pulse for clockwise direction
										PORTD &= ~dirPinX;
										//send 200 pulses to rotate One full cycle
										PORTD |= stepPinX;
										//_delay_ms(1);
										PORTD &= ~stepPinX;
										_delay_ms(1); //
									}
							}
							
						}
							
						
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
					t--;//Die Zeit wird um i_steps_y verringert weil die Funktion _delay_ms so oft gestartet wird 
					
					if(my > 0)
					{	
							int flagy = 0;
							for (int j = 0; j < schrittdauer_y; j++)
							{
										_delay_ms(1);
										flagy++;
										if (flagy == schrittdauer_y)
										{
												for (int i = 0; i < i_steps_y; i++)
												{
													my--;
													PORTD &= ~dirPinY;
													//send 200 pulses to rotate One full cycle
													
													PORTD |= stepPinY;
													//_delay_ms(1);
													PORTD &= ~stepPinY;
													_delay_ms(1);
												}
										}
										
										
							}
						
						
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
		
			
		}
	}
    return 0;
}




/*void Init(void) //Initialisiert die einzelnen Init Funktionen
{
	//Timer0_Init();
	//Timer1_Init();
}*/


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

/*if (Timer1_get_10msState() == TIMER1_TRIGGERED) //jede 1s wird die Bedingung erf¸lt
			{
				ucFlagBlink_Y++;
				if (ucFlagBlink_Y) movingToY (my);
				
			}*/




//============================================weitere Informationen:===================================================//
//***************************************************
// rpm = 300 U/min = 5/sec = 5 Hz
//***************************************************