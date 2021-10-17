/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	DEMO LINK: https://youtu.be/fCCZao0xEOI
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
 


enum States{start,firstStage,light1_press,relief1,light2_press,relief2,light3_press,relief3,light4_press,relief4} state;

void Tick(){
	unsigned char temp = 0x00;

	temp =  ~PINA & 0x01;

	switch (state){
	 case start:
	   PORTC = 0xFF;
	   state = firstStage;
	   break;

	 case firstStage:
	   if(temp == 0x01){
		state = light1_press;
	   }
		
	   break;
	
	 case light1_press:
	   if((temp & 0x01) == 0x01){
		state = light1_press;
	   }
	   else if((temp & 0x01) == 0x00){
		state = relief1;
	   }
	   break;
	  
	  case relief1:
	   if((temp & 0x01)  == 0x01)
           {
                state = light2_press;
           }
           break;



	 case light2_press:
	   if((temp & 0x01) == 0x01)
	   {
		state = light2_press;
	   }
	   else if((temp & 0x01) == 0x00)
	   {
		state = relief2;
	   }
	   break;

	 case relief2:
	   if((temp & 0x01) == 0x01)
	   {
		state = light3_press;
	   }

	   break;

	case light3_press:
	   if((temp & 0x01)  == 0x01)
           {
		state = light3_press;
           }
           else if((temp & 0x01)  == 0x00)
           {
		state= relief3;
           }
	   break;

	 case relief3:
	   if((temp & 0x01)  == 0x01){
		state = light4_press;
	   }
	   break;

	 case light4_press:
	   if((temp & 0x01)  == 0x01)
           {
		state = light4_press;
           }
           else if((temp & 0x01)  == 0x00)
           {
		state = relief4;
           }
	   break;

	 case relief4:
	   if((temp & 0x01)  == 0x01)
		  {
			state = light1_press;
		  }
	   break;


	 default:

	   break;

	 
	}
	switch(state){
	  case start:
		  PORTC = 0xFF;
		  break;
	case firstStage:
		  PORTC = 0xFF;
		  break;
	case light1_press:
		  PORTC = 0xC3;
		  break;
	case relief1:
		  break;
	case light2_press:
		  PORTC = 0x3C;
		  break;
	case relief2:
		  break;
	case light3_press:
		  PORTC = 0x24;
		  break;
	case relief3:
		  break;
	case light4_press:
		PORTC = 0x81;
		break;
	case relief4:
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
