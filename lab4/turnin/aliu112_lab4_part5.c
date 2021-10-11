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
 


enum States{start,beginning,match, match2, reset, unlock,lock} state;

void Tick(){

	unsigned char arr[4] = {0x04,0x01,0x02,0x01};
	int i =0;

	switch (state){
	 case start:
	   PORTB =0x00;
	   state = beginning;
	   break;
	
	 case beginning:
	   PORTC=0x01;
	   if( PINA== arr[i])
	   {
		state = match;
	   }
	   else if( PINA == 0x80)
	   {
		state = lock;
	   } 
	   else 
		   state= beginning;
	   break;
	 
	 case match:
	   if((i == 3) && (PORTB == 0x01) )
	   {
		state = lock;
	   }
	   else if( (i== 3) && (PORTB == 0x00))
	   {
		state = unlock;
	   }
	   else if(PINA == arr[i] )
		{
			state = match;
		}
	   else if (PINA == 0x00)
		{
			state = match2;
		}	
		else
		{
			state = reset;
		}
			
	break;

	 case match2:
		i = i+1;
		if(PINA == arr[i])
		{
			state = match;
		}
		else
			state = reset;
		break;

	 
	 case reset:
	   i=0;
	   break;

	 case unlock:
	   PORTC = 0x05;
	   PORTB = 1;

		   state = beginning;
	   break;

	 case lock:
	   PORTC =0x06;
	   if(PINA  == 0x80)
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

	case match:
		  break;
	case match2:
		  break;

	case reset:
		  i=0;
		  break;
	case unlock:
		  PORTB =0x01;
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
