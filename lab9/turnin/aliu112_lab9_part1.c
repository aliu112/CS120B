/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 9  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	DEMO Link: https://youtu.be/m55m2a9vXNw
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, note1, note2,note3}state;

volatile unsigned char TimerFlag = 0;

unsigned char input=0x00;
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

void set_PWM(double frequency){
	static double current_frequency;

	if(frequency != current_frequency)
	{
		if(!frequency){TCCR3B &= 0x08;}
	
		else{TCCR3B |= 0x03;}

		if(frequency < 0.954){OCR3A = 0xFFFF;}

		else if(frequency > 31250) {OCR3A = 0x0000;}

		else{OCR3A = (short)(8000000/(128*frequency))-1; }
	
		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){

	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A=0x00;
	TCCR3B=0x00;
}

void Tick(){
	input = ~PINA & 0x07;

	switch(state){
	 case start:
		if(input == 0x01)
		{
			state = note1;
		}
		else if(input == 0x02)
		{
			state= note2;
		}
		else if(input == 0x04)
		{
			state = note3;
		}
		break;

	 case note1:
		if(input == 0x01)
		{
			state = note1;
		}
		else
		{
			state = start;
		}
		break;

	 case note2:
		if(input == 0x02)
		{
			state = note2;
		}
		else
		{
			state = start;
		}
		break;
	
	 case note3:
		if(input == 0x04)
		{
			state = note3;
		}
		else
		{
			state = start;
		}
		break;

	 default:
		break;

	}
	switch(state){
	case start:
	       set_PWM(0);	
		break;
	case note1:
		set_PWM(261.63);
		break;
	case note2:
		set_PWM(293.66);
		break;
	case note3:
		set_PWM(329.63);
		break;
	default:
		break;
	}	


}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    TimerSet(100);
    TimerOn();
    PWM_on();
    while (1) {
	    Tick();
	    while(!TimerFlag);
	    TimerFlag=0;

    }
    return 1;
}
