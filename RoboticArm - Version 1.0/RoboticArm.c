#include <avr/io.h> 
#include <util/delay.h>
#include "Robot_Lib.h"
#include "ButtonPress.h"
#include "lcd_lib.h"


t_Mode currentMode = GRIP_MODE; 

int main()
{
	init(); 
	init_positions(); 
	init_buttons(); 

	while(1)
	{		
		if(ButtonPressed(BUTTON3, PA2))
		{
			change_mode(); 
		}
		
		process_mode(currentMode); 
	} 

	return 0; 
}



void init() 
{
	TCCR1A |= (1 << WGM11); 
	TCCR1B |= (1 << WGM12) | (1 << WGM13); 

	TCCR3A |= (1 << WGM31); 
	TCCR3B |= (1 <<WGM32) | (1 <<WGM33); 

	TCCR1A |= (1 << COM1A1) | (1 <<COM1A0) | (1 <<COM1B1) | (1 <<COM1B0) | (1 << COM1C1) | (1 <<COM1C0);  
	TCCR3A |= (1 << COM3A1) | (1 << COM3A0) | (1 << COM3B1) | (1 << COM3B0); 

	TCCR1B |= (1 << CS11); 
	TCCR3B |= (1 << CS31); 
	
	ICR3 = 40000; 
	ICR1 = 40000; 

	//set PWM pins as output 
	DDRB |= (1 << 5) | (1 << 6) | (1 << 7);  
	DDRE |= (1 << 3) | (1 << 4); 

	LCDinit(); 
	LCDclr();  
	LCDcursorOFF(); 
	LCDstring("GRIP MODE", 9); 
} 

void init_buttons() 
{
	///set the buttons for output 
	DDRA &= ~(1 << PA0); DDRA &= ~(1 << PA1); DDRA &= ~(1 << PA2); 
	DDRA &= ~(1 << PA3); DDRA &= ~(1 << PA4); 
	
	///set the buttons high 
	PORTA |= (1 << PA0) | (1 << PA1) | (1 << PA2) | (1 << PA3) | (1 << PA4); 

	///the light for testing purposes...
	DDRA |= (1 << PA6); 
	//PORTA |= (1 << PA6); 
}


void init_positions() 
{
	BASE 		= ANG_BASE_MID; 
	SHOULDER 	= ANG_SHOULDER_MID; 
	ELBOW 		= ANG_ELBOW_MID; 
	GRIP 		= ANG_GRIP_MIN;
	WRIST		= ANG_WRIST_MAX; 
	
	basic_delay(300); 
} 


void process_mode(int mode) 
{
	switch(mode)
	{
		case GRIP_MODE: 
				///closes the grip 
				while(bit_is_clear(PINA, PA1))
				{
					if(!(GRIP < ANG_GRIP_MIN)) 
					{ 
						GRIP--; 
						_delay_ms(3); //so it moves slow
					}
				}
				///opens the grip 
				while(bit_is_clear(PINA, PA3))
				{
					if(!(GRIP > ANG_GRIP_MAX)) 
					{ 
						GRIP++; 
						_delay_ms(3); //so it moves slow
					}
				}
			break; 

		case SHOULDER_MODE: 
			//lifts the shoulder upwards 
			while(bit_is_clear(PINA, PA0)) 
			{
				if(!(SHOULDER < ANG_SHOULDER_MIN)) //do not go more than the middle 
				{ 
					SHOULDER--; 
					WRIST++; //keep wrist steady in the same position 
					_delay_ms(3); //so it moves slow
				}
			} 
			//pulls shoulder downwards 
			while(bit_is_clear(PINA, PA4))
			{
				if(!(SHOULDER > ANG_SHOULDER_MAX)) 
				{ 
					SHOULDER++; 
					WRIST--; //keep wrist steady in the same position 
					_delay_ms(3); //so it moves slow
				}
			} 
			//rotate to the left
			while(bit_is_clear(PINA, PA1))
			{
				if(!(BASE < ANG_BASE_MIN)) 
				{ 
					BASE--; 
					_delay_ms(3); //so it moves slow
				}
			}
			//rotates to the right
			while(bit_is_clear(PINA, PA3))
			{
				if(!(BASE > ANG_BASE_MAX)) 
				{ 
					BASE++; 
					_delay_ms(3); //so it moves slow 
				}
			}
			break; 

		case ELBOW_MODE: 
			//lifts the shoulder upwards 
			while(bit_is_clear(PINA, PA4)) 
			{
				if(!(ELBOW < ANG_ELBOW_MIN)) //do not go more than the middle 
				{ 
					ELBOW--; 
					WRIST--; 
					_delay_ms(3); //so it moves slow
				}
			} 
			//pulls shoulder downwards 
			while(bit_is_clear(PINA, PA0))
			{
				if(!(ELBOW > ANG_ELBOW_MAX)) 
				{ 
					ELBOW++; 
					WRIST++; 
					_delay_ms(3); //so it moves slow
				}
			} 

			//rotate to the left
			while(bit_is_clear(PINA, PA1))
			{
				if(!(BASE < ANG_BASE_MIN)) 
				{ 
					BASE--; 
					_delay_ms(3); //so it moves slow
				}
			}
			//rotates to the right
			while(bit_is_clear(PINA, PA3))
			{
				if(!(BASE > ANG_BASE_MAX)) 
				{ 
					BASE++; 
					_delay_ms(3); //so it moves slow 
				}
			}
			break; 

		default:
			break; 
	} 
}


void change_mode()
{
	LCDclr(); 
	if(currentMode == GRIP_MODE)
	{
		currentMode = SHOULDER_MODE; 
		LCDstring("SHOULDER MODE", 13); 
		PORTA |= (1 << PA6); //light on for lift mode
	} 
	else if(currentMode == SHOULDER_MODE)
	{
		currentMode = ELBOW_MODE; 
		LCDstring("ELBOW MODE", 10); 
		PORTA |= (1 << PA6); 	//light off for grip mode
	} 
	else if(currentMode == ELBOW_MODE) 
	{
		currentMode = GRIP_MODE; 
		LCDstring("GRIP MODE", 9); 
		PORTA &= ~(1 << PA6);
	} 
	else {/*just empty*/}
}


void basic_delay(int duration) 
{
	for(int i=0; i < duration; i++ ) 
	{
		_delay_ms(1); 
	}
}
