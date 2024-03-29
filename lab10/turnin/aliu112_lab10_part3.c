/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section: 
 *	Assignment: Lab 10  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	DEMO LINK: https://youtu.be/wnX4bK78kUo
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, On, Off}state;
enum States2{start2,zero,one,two} state2;
enum States3{start3}state3;
enum States4{start4,on,off}state4;

volatile unsigned char TimerFlag = 0;

unsigned char input=0x00;
unsigned long i=0x00;
unsigned long j=0x00;
unsigned char k=0x00;
unsigned char speaker=0x00;
unsigned char threeLEDs=0x00;
unsigned char blinkingLED=0x00;
unsigned long _avr_timer_M=0;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 =0;

	_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80;

}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void BlinkLEDSM(){
	switch(state){
		case start:
		state = On;
		break;

		case On:
		  if(i>=1000)
		  {
			  i=0;
		  	state=Off;
		  }
		  break;

		case Off:
		  if(i>=1000)
		  {
			  i=0;
		  	state =On;
		  }
		  break;

		default:
		  break;
	}
	switch(state){
		case start:
			i=0;
			break;
		case On:
			++i;
			blinkingLED = 0x08;
			break;
		case Off:
			++i;
			blinkingLED = 0x00;
		default:
			break;
	}
}

void ThreeLEDsSM(){
	switch(state2){
		case start2:
			j=0;
			state2 = zero;
			break;
		case zero:
			
			if(j>=300)
			{
				j=0;
				state2 = one;
			}
			break;
		case one:
			if(j>=300)
			{
				j=0;
				state2 = two;
			}
			break;
		case two:
			
			if(j>=300)
			{
				j=0;
				state2 = zero;
			}
			break;
		default:
			break;

	}
	switch(state2){
		case start2:
			break;
		case zero:
			++j;
			threeLEDs = 0x01;
			break;
		case one:
			++j;
			threeLEDs = 0x02;
			break;
		case two:
			++j;
			threeLEDs = 0x04;
			break;
		default:
			break;
	}

}

void SPEAKER(){
	input = ~PINA & 0x04;
	switch(state4)
	{
		case start4:
			if(input == 0x04)
			{
				state4 = on;
			}
			break;
		case on:
			if(input ==0x00)
			{
				state4=off;
			}
			break;
		case off:
			if(input ==0x04)
			{
				state4 =on;
			}
			break;
		default:
			break;
	}
	switch(state4)
	{
		case start4:
		        k=0;	
			speaker=0x00;
			break;
		case on:
			if(k<=2)
			{
				speaker=0x10;
			}
			else if(k<=4)
			{
				speaker =0x00;
			}
			else
			{
				k=0;
			}
			++k;
			break;
		case off:
			k=0;
			speaker=0x00;
			break;
		default:
			break;
	}
}
void CombineLEDsSM(){
	switch(state3)
	{
		case start3:
			state3 = start3;
			break;
		default:
			break;

	}
	switch(state3)
	{
		case start3:
			PORTB = speaker| threeLEDs | blinkingLED;
			break;
		default:
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA=0x00; PORTA=0xFF;
	DDRB = 0xFF; PORTB=0x00;
    /* Insert your solution below */
	TimerSet(1);
	TimerOn();

    while (1) {
	BlinkLEDSM();
	ThreeLEDsSM();
	SPEAKER();
	CombineLEDsSM();
	while(!TimerFlag);
	TimerFlag=0;
    }
    return 1;
}
