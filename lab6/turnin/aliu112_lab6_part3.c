/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section: 23
 *	Assignment: Lab 6  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 * 	YOUTUBE LINK: https://youtu.be/k2Q4YORZEY0
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, post_increment, increment, post_decrement, decrement, pause, reset}state;

volatile unsigned char TimerFlag = 0;

unsigned char i=0x00;
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
	switch (state){
	 case start:
	   PORTB = 7;
	   state = pause;
	   break;

	 case pause:
	   if( (~PINA & 0x03) == 0x03 ) // reset needs to go first bc 0x03 & 0x01 will still give 0x01
	   {
	     state = reset;
	   }
	   else if((~PINA & 0x02) == 0x02)
	   {
	     state = decrement;
	   }
	   else if((~PINA & 0x01) == 0x01)
           {
            state = increment;
           }
	   else
		   state = pause;

	  break;

	 case increment:
	   state = post_increment;
	   break;

	 case post_increment:
	   if((~PINA & 0x03) == 0x03)
	   {
		state = reset;
	   }
	   else if( ((~PINA & 0x01) == 0x01) && i >= 10 )
	   {
		   state = increment;
	   }
	   else if((~PINA & 0x03) == 0x00)
	   {
		state = pause;
	   }
	   break;

	 case decrement:
   	  state = post_decrement;
	   break;
	
	case post_decrement:
	   if((~PINA & 0x03) == 0x03)
           {
                state = reset;
           }
	   else if((~PINA & 0x01) == 0x01)
	   {
		state = increment;
	   }
           else if( ((~PINA & 0x02) == 0x02) && i>=10 )
           {
                   state = decrement;
	   }
           else if((~PINA & 0x03) == 0x00)
           {
                state = pause;
           }
	   break;


	case reset:
	   if((~PINA & 0x03) == 0x03)
	   {
		state = reset;
	   }
	   else 
		   state = pause;
               
	break;

	 
	 default:

	   break;

	 
	}
	switch(state){
	  case start:
		  PORTB = 0x07;
		  break;
	case post_increment:
		  ++i;
		  break;
	   case increment:
		  i=0;
		  if(PORTB < 0x09)
		  {
			PORTB =PORTB +1;
		  }
		  break;

	case post_decrement:
		  ++i;
		  break;
	   case decrement:
		  i=0;
		  if(PORTB > 0x00)
		  {
			PORTB = PORTB -1;
		  }
		  break;
	   case pause:
		  break;
	   case reset:
		  PORTB = 0x00;
	  	break;
	   default:
		  break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; DDRA = 0x00;
    PORTB =0x00; PORTA = 0xFF;
    TimerSet(100);
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
