/*	Author: ab
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
    DDRD = 0x00; PORTD = 0xFF;    
    DDRB = 0xFE; PORTB = 0x00;
    
    
    /* Insert your solution below */
    unsigned short temp = 0x000;
    unsigned char tempNew = 0x000;
    unsigned char output = 0x00;

    while (1) {
	temp = 0x000;
	output = 0x00;
	temp = PIND; 
	tempNew = PINB;
	tempNew = tempNew & 0x001;
        temp = temp << 1;
	temp = temp | tempNew;

	if(temp >= 70)
	{
		output = output | 0x02;
	}
	if(temp> 5 && temp <70)
	{
		output = output | 0x04;
	}
	PORTB = output;
		
    
    
    }
    	return 1;
    
  }
