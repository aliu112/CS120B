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
 


enum States{start,beginning, pound_press, pound_release,Y_press, Y_unlock,lock} state;

void Tick(){
	switch (state){
	 case start:
	   PORTB =0x00;
	   state = beginning;
	   break;
	
	 case beginning:
	   PORTC=0x01;
	   if( (PINA & 0x07) == 0x04)
	   {
		state = pound_press;
	   }
	   else if( (PINA & 0x87) == 0x80)
	   {
		state = lock;
	   } 
	   else 
		   state= beginning;
	   break;

	 case pound_press:
	   PORTC = 0x02;
	   if((PINA & 0x07) == 0x04)
	   {
		   state = pound_press;
	   }
	  // else
	//	   state =pound_release;
	   else if((PINA & 0x07) == 0x00)    
	   {
		state = pound_release;
	   }
	   else 
		state = beginning;
	   break;
	 
	 case pound_release:
	   PORTC =0x03;
	   if((PINA & 0x07) == 0x04)
	   {
		state = pound_press;
	   }
	   else if((PINA & 0x07) == 0x02)
	   {
		state = Y_unlock;
	   }
	   else
	   {
		state = beginning;
	   }
	   break;
	 
	 case Y_press:
	   PORTC = 0x04;
	   if((PINA & 0x07) == 0x02)
	   {
		state = Y_press;
	   }
	   else if((PINA & 0x07) == 0x00)
	   {
		state = Y_unlock;
	   }
	   else
		   state = beginning;

	   break;

	 case Y_unlock:
	   PORTC = 0x05;
		   state = beginning;
	   break;

	 case lock:
	   PORTC =0x06;
	   if((PINA & 0x87) == 0x80)
	   {
		state = lock;
	   }
	   else 
		   state = beginning;
	   break;
	 
	 default:

	   break; 
	}
	switch(state){
	  case start:
		  break;
	  case pound_press:
		  break;
	case pound_release:
		  break;
	case Y_press:
		  break;
	case Y_unlock:
		  PORTB = 0x01;
		  break;
	case lock:
		  PORTB = 0x00;
		  break;
	   default:
		  break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB= 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
      Tick();   
    }
    return 1;
}
