/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 * 	YOUTUBE LINK: https://youtu.be/SX-PkRwjc2U
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, light1, light2, light3}state;

volatile unsigned char TimerFlag = 0;

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


void Tick(){
	switch(state){ //transitions
		case start: 
			state = light1;
			break;
		case light1:
			state = light2;
			break;
		case light2:
			state = light3;
			break;
		case light3:
			state = light1;
			break;
		default:
			state = start;
			break;

	}
	switch(state){
		case start: 
			break;
		case light1:
			PORTB = 0x01;
			break;
		case light2:
			PORTB = 0x02;
			break;
		case light3:
			PORTB = 0x04;
			break;
		default:
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB =0x00;
    TimerSet(1000);
    TimerOn();
   // unsigned char tmpB = 0x00;
    while(1){
	Tick();
//	tmpB = ~tmpB;
//	PORTB = tmpB;
	while(!TimerFlag);
	TimerFlag = 0;
    }
	
    return 1;
}
