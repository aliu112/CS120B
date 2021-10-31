/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section: 23
 *	Assignment: Lab 8  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	DEMO Link: https://youtu.be/lTR8S0EfiRs
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);

}
unsigned short my_short = 0x00;
unsigned char my_char=0x00;
unsigned char MAX = 0xC2;
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    ADC_init();
    while (1) {
	my_short =ADC;
	if(my_short >= MAX/2)
	{
		PORTB = 0x01;
	}
	else if(my_short < MAX/2)
	{
		PORTB = 0x00;
	}
    }
    return 1;
}
