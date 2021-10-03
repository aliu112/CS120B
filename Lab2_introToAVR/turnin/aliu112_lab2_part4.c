/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;    
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0x00; PORTC = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    unsigned char tempB = 0x00;
    unsigned char tempA = 0x00;
    unsigned char tempC = 0x00;
    unsigned char tempD = 0x00;
    while (1) {
	    tempA = PINA;
	    tempB = PINB;
	    tempC = PINC;
	    tempD = 0x00;
	if( (tempA + tempB + tempC) > 0x8C )
	{
		tempD = tempD | 0x01;
	}

	if( tempA > tempC)
	{	
		if( (tempA - tempC) > 0x50)
		{
		 tempD = tempD | 0x02;
		}
	}
	else
	{
		if( (tempC - tempA) > 0x50)
		{
		 tempD = tempD | 0x02;
		}
	}
	tempA = (tempA + tempB + tempC) & 0xFC;
	tempD = tempA | tempD;
	PORTD = tempD;
    }
    return 0;
}
