/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
	
 	DEMO LINK: https://youtu.be/fwSAzmuS7kA 

 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <timer.h>
#include <keypad.h>
#include <io.h>
#include <scheduler.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif



enum states { Display };
unsigned char position = 0x00;
unsigned char lcd[76] ={ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','C','S','1','2','0','B',' ','i','s',' ','L','e','g','e','n','d','.','.','.','w','a','i','t',' ','f','o','r',' ','i','t',' ','D','A','R','Y','!',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
int LCD(int state) {
	switch(state) {
		case Display:	
				state = Display;
				break;
		default: 	
				break;
	}
	switch(state) {
		case Display:	for (int k = 1; k <= 16; ++k) {
					LCD_Cursor(k);
					LCD_WriteData(lcd[position + (k)]);
					if(position  == 60)
					{
						position = 1;
					}
				}
				++position;

				
				break;
		default:	break;
	}
	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    LCD_init();
    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
    const char start = 0;

    task1.state = start;
    task1.period = 20;
    task1.elapsedTime = task1.period;
    task1.TickFct = &LCD;

    TimerSet(20);
    TimerOn();

    unsigned short i;
    while (1) {
	for (i = 0; i < numTasks; ++i) {
		if (tasks[i]->elapsedTime == tasks[i]->period) {
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 1;
	}
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
