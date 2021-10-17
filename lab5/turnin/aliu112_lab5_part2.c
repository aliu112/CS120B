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
 


enum States{start,post_increment, increment,post_decrement, decrement, pause, reset} state;

void Tick(){
	switch (state){
	 case start:
	   PORTC = 7;
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
	   else if((~PINA & 0x01) == 0x01)
	   {
		   state = post_increment;
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
           else if((~PINA & 0x02) == 0x02)
           {
                   state = post_decrement;
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
		  PORTC = 0x07;
		  break;
	case post_increment:
		  break;
	   case increment:
		  if(PORTC < 0x09)
		  {
			PORTC =PORTC +1;
		  }
		  break;

	case post_decrement:
		  break;
	   case decrement:
		  if(PORTC > 0x00)
		  {
			PORTC = PORTC -1;
		  }
		  break;
	   case pause:
		  break;
	   case reset:
		  PORTC = 0x00;
	  	break;
	   default:
		  break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC= 0xFF; PORTC = 0x00;


    /* Insert your solution below */
    while (1) {
      Tick();   
    }
    return 1;
}
