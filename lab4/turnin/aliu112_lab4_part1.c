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
 


enum States{start, OFF_Release, OFF_Press, ON_Release, ON_Press} state;

void Tick(){
	switch (state){
	 case start:
	   state = OFF_Release;
	   break;

	 case OFF_Release:
	   if( (PINA & 0x01) == 0x01)
	   {
	     state=ON_Press;
	   }
	   else
	     state = OFF_Release;
	   break;

	 case ON_Press:
	   if( (PINA & 0x01) == 0x01 )
	   {
	     state = ON_Press;	  
	   }
	   else
		state = ON_Release;
	   break;

	 case ON_Release:
	   if((PINA ==1)==0x01)
	   {
		state = OFF_Press;
	   }
	   else
		   state = ON_Release;
	   break;

	 case OFF_Press:
	   if((PINA & 0x01) == 0x01)
	   {
	     state = OFF_Press;
	   }
	   else 
             state = OFF_Release;
	   break;
	 
	 default:
	   break;

	 
	}
	switch(state){
	  case start:
		  PORTB = 0x01;
		  break;
	   case OFF_Release:
		  break;
	   case ON_Press:
		  PORTB = 0x02;
		  break;
	   case ON_Release:
		  break;
	   case OFF_Press:
		  PORTB = 0x01;

	  default:
		  break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
      Tick();   
    }
    return 1;
}
