/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section: 23
 *	Assignment: Lab 8  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	DEMO Link: https://youtu.be/vDyODBpHs7k
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
unsigned char light =0x00;
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
	light = MAX/8;
	if(my_short >= light)
	{
		PORTB = 0x01;
	}
	if(my_short >= light*2)
	{
		PORTB = 0x03;
	}
	if(my_short >= light*3)
	{
		PORTB = 0x07;
	}
	if(my_short >= light*4)
	{
		PORTB = 0x0F;
	}
	if(my_short >= light*5)
	{
		PORTB = 0x1F;
	}
	if(my_short >= light*6)
	{
		PORTB = 0x3F;
	}
	if(my_short >= light*7)
	{
		PORTB = 0x7F;
	}
	if(my_short >= MAX)
	{
		PORTB = 0xFF;
	}
    }
    return 1;
}
