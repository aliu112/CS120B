/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section: 23
 *	Assignment: Lab 7  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *
 *	YOUTUBE LINK: https://youtu.be/xOcbIEldGKs
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, light1, light2, light3,pause,reset,reset2,victory}state;

volatile unsigned char TimerFlag = 0;

unsigned char counter=0x05;
unsigned char temp = 0x00;
unsigned char temp2 = 0x00;
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
	//unsigned char temp =0x00;
	//temp= 1;
	unsigned char input = 0x00;
	input = ~PINA & 0x01;
	switch(state){ //transitions
		case start:
			state = light1;
			break;
		case light1:
			
			if(input==0x01)
			{
				state = pause;
			}
			else{
				temp = 1;
				state = light2;
			}
			break;
		case light2:
			if(input==0x01)
			{
				temp2=1;
				state = pause;
			}
			else{
				if(temp == 1)
				{
				state = light3;
				}
				else if(temp == 0)
				{
				state = light1;
				}
			}
			break;
		case light3:
			if(input==0x01)
			{
				state = pause;
			}
			else{
				temp =0;
				state = light2;
			}
			break;
		case pause:
			if(temp2 == 1 && counter <9)
			{
				counter= counter +1;
			}
			else if(temp2 == 0 && counter >0)
			{
				counter= counter -1;
			}

			if(counter == 9)
			{
				LCD_ClearScreen();
				LCD_DisplayString(1,"VICTORY");
				//state = victory;
			}

			if(input==0x01){
				state = pause;
			}
			else
			{
				temp2=0;
				state = reset;
			}
			break;
		case reset:
			if(input == 0x01)
			{
				state = reset2;
			}
			else
			{
				state = reset;
			}
			break;
		case reset2:
			if(counter ==9)
			{
				counter =5;
				LCD_ClearScreen();
			}
			if(input ==0x01)
			{
				state = reset2;
			}
			else
			{
				state = light1;
			}
			break;

		case victory:
			LCD_ClearScreen();
			LCD_DisplayString(1,"VICTORY");
			if(input ==0x01){
				state = reset2;
			}
			else
			{
				state =victory;
			}
			break;
		default:
			state = start;
			break;

	}
	switch(state){
		case start:
			break;
		case light1:
			temp = 1;
			PORTB = 0x01;
			break;
		case light2:
			PORTB = 0x02;
			break;
		case light3:
			temp = 0;
			PORTB = 0x04;
			break;
		case pause:
			break;
		case reset:
			break;
		case reset2:
			break;
		case victory:
			break;
		default:
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; DDRA = 0x00; DDRC = 0xFF;
    PORTB =0x00; PORTA = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    TimerSet(300);
    TimerOn();
    LCD_init();
   // unsigned char tmpB = 0x00;
    while(1){
	Tick();
//	tmpB = ~tmpB;
//	PORTB = tmpB;
	if(counter !=9)
	{
	LCD_Cursor(1);
	LCD_WriteData(counter + '0');
	}
	while(!TimerFlag);
	TimerFlag = 0;
    }
	
    return 1;
}
