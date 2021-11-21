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
#include "scheduler.h"
#include "timer.h"
#include "simAVRHeader.h"
#include <stdio.h>
#include <stdlib.h>

#endif
void transmit_data(unsigned char data) {
    int i;
    for (i = 0; i < 8 ; ++i) {
   	 PORTC = 0x08;
   	 
   	 PORTC |= ((data >> i) & 0x01);
   	 
   	 PORTC |= 0x02;  
    }
    PORTC |= 0x04;
   
    PORTC = 0x00;
}

unsigned long counter=0x00;
unsigned char row = 0x01;
enum states{d1,d2,d3,d4,d5}state;

int tick(){
	switch(state)
	{
		case d1:
			if(counter > 75)
                        {
                                row =0x00;
                                counter=0;
                                state = d2;
                        }
                        else if(counter >70)
                        {
                                row = 0x80;
                        }
                        else if(counter >60)
                        {
                                row = 0x40;
                        }
                         else if(counter >50)
                        {
                                row = 0x20;
                        }
                         else if(counter >40)
                        {
                                row = 0x10;
                        }
                         else if(counter >30)
                        {
                                row = 0x08;
                        }
                         else if(counter >20)
                        {
                                row = 0x04;
                        }
                         else if(counter >10)
                        {
                                row = 0x02;
                        }
                        else
                        {
                                row = 0x01;
                        }
			break;
		case d2:
			if(counter > 75)
                        {
                                row =0x00;
                                counter=0;
                                state = d3;
                        }
                        else if(counter >70)
                        {
                                row = 0x80;
                        }
                        else if(counter >60)
                        {
                                row = 0x40;
                        }
                         else if(counter >50)
                        {
                                row = 0x20;
                        }
                         else if(counter >40)
                        {
                                row = 0x10;
                        }
                         else if(counter >30)
                        {
                                row = 0x08;
                        }
                         else if(counter >20)
                        {
                                row = 0x04;
                        }
                         else if(counter >10)
                        {
                                row = 0x02;
                        }
                        else
                        {
                                row = 0x01;
                        }
			break;
		case d3:
			if(counter > 75)
                        {
                                row =0x00;
                                counter=0;
                                state = d4;
                        }
                        else if(counter >70)
                        {
                                row = 0x80;
                        }
                        else if(counter >60)
                        {
                                row = 0x40;
                        }
                         else if(counter >50)
                        {
                                row = 0x20;
                        }
                         else if(counter >40)
                        {
                                row = 0x10;
                        }
                         else if(counter >30)
                        {
                                row = 0x08;
                        }
                         else if(counter >20)
                        {
                                row = 0x04;
                        }
                         else if(counter >10)
                        {
                                row = 0x02;
                        }
                        else
                        {
                                row = 0x01;
                        }
			break;
		case d4:
			if(counter > 75)
                        {
                                row =0x00;
				counter=0;
                                state = d5;
                        }
                        else if(counter >70)
                        {
                                row = 0x80;
 			}
                        else if(counter >60)
                        {
                                row = 0x40;
                        }
                         else if(counter >50)
                        {
                                row = 0x20;
                        }
                         else if(counter >40)
                        {
                                row = 0x10;
                        }
                         else if(counter >30)
                        {
                                row = 0x08;
                        }
                        
		       	else if(counter >20)
			{
		       		row = 0x04;
                        }
                         else if(counter >10)
                        {
                                row = 0x02;
                        }
                        else
                        {
                                row = 0x01;
                        }

			break;
		case d5:
			if(counter > 75)
                        {
                                row =0x00;
                                counter=0;
                                state = d1;
                        }
                        else if(counter >70)
                        {
                                row = 0x80;
                        }
                        else if(counter >60)
                        {
                                row = 0x40;
                        }
                         else if(counter >50)
                        {
                                row = 0x20;
                        }
                         else if(counter >40)
                        {
                                row = 0x10;
                        }
                         else if(counter >30)
                        {
                                row = 0x08;
                        }
                         else if(counter >20)
                        {
                                row = 0x04;
                        }
                         else if(counter >10)
                        {
                                row = 0x02;
                        }
                        else
                        {
                                row = 0x01;
                        }
			break;
		default:
			break;
	}
	switch(state)
	{
 		case d1:
                        PORTD = 0xFE;
			transmit_data(row);
			++counter;
                        break;
                case d2:
                        PORTD = 0xFD;
			transmit_data(row);
			++counter;
                        break;
                case d3:
                        PORTD = 0xFB;
			transmit_data(row);
			++counter;
                        break;
                case d4:
                        PORTD = 0xF7;
			transmit_data(row);
			++counter;
                        break;
                case d5:
                        PORTD = 0xEF;
			transmit_data(row);
			++counter;
                        break;
                default:
                        break;
	}

	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA =0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks) / sizeof(task*);

	task1.state=0;
	task1.period=100;
	task1.elapsedTime = task1.period;
	task1.TickFct = &tick;

	TimerSet(100);
	TimerOn();

	unsigned short i;
    while (1) {
	    for (i = 0; i < numTasks; i++)
        {
            if (tasks[i]->elapsedTime == tasks[i]->period)
            {
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime +=100;
        }
        while (!TimerFlag)
            ;
        TimerFlag = 0;

    }
    return 1;
}
