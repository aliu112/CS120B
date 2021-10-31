/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 9  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	DEMO Link: https://youtu.be/9rsFHHAQHlA
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start,pause,increment,post_increment,decrement,post_decrement,toggle,post_toggle}state;

volatile unsigned char TimerFlag = 0;

unsigned char flag =0x00;
unsigned char counter= 0x00;
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
			state= increment;
		}
		else if(input ==0x02)
		{
			state=decrement;
		}
		else if(input == 0x04)
		{
			state = toggle;
		}	
		else
		{
			state = pause;
		}
		break;
	case increment:
	      state=post_increment;
	      break;

	case post_increment:
	      if(input ==0x01)
	      {
		state=post_increment;
	      }
	      else if(input == 0x00)
	      {
		state=pause;
	      }
	      break;
	case decrement:
	      state=post_decrement;
	      break;
	case post_decrement:
	      if(input == 0x02)
	      {
		state = post_decrement;
	      }
	      else  if(input ==0x00)
	      {
		state = pause;
	      }

	case toggle:
	      state = post_toggle;
	      break;
	case post_toggle:
	      if(input == 0x04)
	      {
		state = post_toggle;
	      }
	      else if(input ==0x00)
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
	       flag=0;
	case pause:
	       if(flag >=1)
	       {
		set_PWM(arr[counter]);
	       }
	       break;
	case increment:
	       if(counter < 7)
	       {
		counter = counter +1;
	       }
	       break;
	case post_increment:
	       break;
	case decrement:
	       if(counter >0)
	       {
			counter = counter -1;
	       }
	case post_decrement:
		break;
	case toggle:
		flag = ~flag;
		if(flag == 0){
			set_PWM(0);
		}
		else if(flag >= 1)
		{
			set_PWM(arr[counter]);
		}
	case post_toggle:
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
