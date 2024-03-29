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
    DDRB = 0xFF;
    PORTB = 0x00;
    /* Insert your solution below */
    unsigned char tempB = 0x00;
    unsigned char tempA = 0x00;
    while (1) {
	tempA = PINA & 0x01;
	tempB = PINA & 0x02;
	if(tempA == 0x01 && tempB==0x00)
	{
	tempB = (tempB & 0xFC) | 0x01;
	}
	else
	{
	tempB = (tempB & 0xFC) | 0x00;
	}
	PORTB = tempB;
    }
    return 0;
}
