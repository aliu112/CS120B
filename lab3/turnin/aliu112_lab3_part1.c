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
    
    /* Insert your solution below */
    unsigned char temp = 0x00;
    unsigned char counter = 0x00;
    unsigned char holder = 0x00;
    while (1) {
	counter = 0x00;
    	    temp = PINA;
	
	for(int i=0; i<8; i++)
	{
  	  holder = temp & 0x01;
	  if(holder == 0x01)
	  {
	    counter = counter +1;
	  }
	  temp = temp >> 1;
	}

	temp = PINB;
	for(int i=0; i< 8; i++)
	{
	  holder = temp & 0x01;
	  if(holder == 0x01)
	  {
	   counter= counter +1;
	  }
	  temp = temp >>1;
	}

	PORTC = counter;

	
    }
    return 1;
}
