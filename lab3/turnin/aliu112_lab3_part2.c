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
    DDRA = 0x00; PORTA = 0xFF;    
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0x00; PORTC = 0xFF;
    
    /* Insert your solution below */
    unsigned char temp = 0x00;
    unsigned char tempNew =0x00;
    unsigned char counter = 0x00;
    unsigned char holder = 0x00;
    while (1) {
	tempNew = PINA;
	temp = tempNew & 0xF;
	holder = 0x00;

	if(temp > 0x00)// && temp <= 0x02)
	{
	  holder = holder | 0x20;
	}
	if(temp > 0x02)// && temp <=0x04)
	{
	 holder = holder | 0x10; 
	}	
	if(temp > 0x04)// && temp <=0x06)
	{
	 holder = holder | 0x08;
	}
	if(temp > 0x06)// && temp <=0x09)
	{
	 holder = holder | 0x04;
	}
	if(temp > 0x09)// && temp <=0x0C)
	{
	 holder = holder | 0x02;
	}
	if(temp > 0x0C)// && temp <= 0x0F)
	{
	 holder = holder | 0x01;
	}

	//low fuel
	if(temp <= 0x04 && temp >= 0x00)
	{
	  holder = holder | 0x40;
	}

	PORTC = holder;
    
    }
    return 1;
}
