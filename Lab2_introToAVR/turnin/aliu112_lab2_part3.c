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
    DDRA = 0x00; PORTA = 0xFF;    DDRB = 0xFF;
    PORTB = 0x00;
    /* Insert your solution below */
    unsigned char tempB = 0x00;
    unsigned char tempA = 0x00;
    unsigned char tempC = 0x00;
    unsigned char tempD = 0x00;
    unsigned char cntavail = 0x00;
    while (1) {
	 cntavail = 0x04;   
	 tempA = PINA & 0x01; 
	 tempB = PINA & 0x02;
	 tempC = PINA & 0x04;
	 tempD = PINA & 0x08;
	 

	 if(tempA == 0x01)
	 {
		 cntavail = cntavail -1;
	 }
	 if(tempB == 0x02)
	 {
		 cntavail = cntavail -1;
	 }
	 if(tempC == 0x04)
	 {
		cntavail = cntavail -1;
	 }
	 if(tempD ==0x08)
	 {
		cntavail = cntavail -1;
	 }
	
	 if(cntavail == 0x00)
	 {
		cntavail = 0x80;
	 }
	PORTC = cntavail;


    }
    return 0;
}
