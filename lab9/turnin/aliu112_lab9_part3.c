/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section: 
 *	Assignment: Lab 9  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	DEMO Link: https://youtu.be/A3a1UxcL3Dc
 *
 *	NOTE: Sorry for messy code, but I didn't know how to implement using the hint from the lab documentation.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start,pause,play}state;

volatile unsigned char TimerFlag = 0;


unsigned char i= 0x00;
unsigned short  arr[8] = {261.63,293.66,329.63,349.23,392.00,440.00,493.88,523.25};
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
		state = pause;
		break;
	case pause:
		if(input ==0x01)
		{
			state= play;
		}
		break;
	case play:
		if(input == 0x01)
		{
			state = play;
		}
		else if(input ==0x00 &&i>110)
		{
			state = pause;
		}
		break;


	 default:
		break;

	}
	switch(state){
	case start:
	       set_PWM(0);
	case pause:
	       set_PWM(0);
	       i=0;
	       break;
	case play:
	       ++i;
	       if(i >0 && i <=5)
	       {
		       set_PWM(arr[4]);
	       }
	       if(i >5 && i<=8)
	       {
			set_PWM(0);
	       }
	       if(i>8 && i<=13)
	       {
			set_PWM(arr[4]);
	       }
	       if(i>13 && i<=15)
	       {
			set_PWM(0);
	       }
	       if(i>15 && i<= 22)
	       {
			set_PWM(arr[5]);
	       }
	       if(i>22 && i<=24)
	       {
			set_PWM(0);
	       }
	       if(i>24 && i<= 31)
	       {
			set_PWM(arr[4]);
	       }
	       if(i>31 && i<=33)
	       {
			set_PWM(0);
	       }
	       if(i>33 && i<= 40)
	       {
			set_PWM(arr[7]);
	       }
	       if(i>40 && i<= 42)
	       {
			set_PWM(0);
	       }
	       if(i>42 && i<=56)
	       {
			set_PWM(arr[6]);
	       }
	       if(i>56 && i<=58)
	       {
			set_PWM(0);
	       }
	       if(i>58 && i<= 63)
	       {
			set_PWM(arr[4]);
	       }
	       if(i>63 && i<=65)
	       {
			set_PWM(0);
	       }
	       if(i>65 && i<=70)
	       {
			set_PWM(arr[4]);
	       }
	       if(i>70 && i<=72)
	       {
			set_PWM(0);
	       }
	       if(i>72 && i<=79 )
	       {
			set_PWM(arr[5]);
	       }
	       if(i>79 && i<=81)
	       {
			set_PWM(0);
		}
	       if(i>81 && i<=89)
	       {
			set_PWM(arr[4]);
	       }	
		if(i>89 && i<= 91)
		{
			set_PWM(0);
		}
		if(i>91 && i<=98)
		{
			set_PWM(587.33);
		}
		if(i>98 && i<=100)
		{
			set_PWM(0);
		}
		if(i>100 && i<=110)
		{
			set_PWM(arr[7]);
		}
		if(i>110)
		{
			set_PWM(0);
		}
	       
	        
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
