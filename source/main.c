/*	Author: Aaron Liu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Project
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	Demo Link 1: https://youtu.be/IVxwJLJ8h1E
 *	Demo Link 2: https://youtu.be/BBfMSuzbskg 
 *	Demo Link 3: https://youtu.be/vgtTz9e9GU0
 *
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include <util/delay.h>
#include <io.h>
#include "scheduler.h"
#include "timer.h"
#include "simAVRHeader.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#endif



void A2D_init(){
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);

}
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
unsigned char timer=0x00;
unsigned char temp1,temp2=0x00;
unsigned char flag =0x00;
unsigned char score = 0x00;
unsigned char score2 = 0x00;
enum states{beginning,d1,d2,d3,d4,d5}state;
enum states2{c1,c2,c3,c4,c5}state2;
enum states3{start}state3;
enum states4{showScore}state4;


int tick2(){
	ADMUX = 0xC0;
	unsigned short input = ADC;

	switch(state2)
	{
		case c1:  
			if(input >900)
			{
			state2 = c2;
			}
			break;
		case c2:
			if(input <300)
			{
			state2 = c1;
			}
			else if(input >900)
			{
			state2 = c3;
			}
			break;
		case c3:
			if(input <300)
			{
				state2 =c2;
			}
			else if(input >900)
			{
				state2 = c4;
			}
			break;
		case c4:
			if(input <300)
			{
			state2 = c3;
			}
			else if(input >900)
			{
			state2 = c5;
			}
			break;
		case c5:
			if(input <300)
			{
			state2 = c4;
			}
			break;
		default:
			break;	
	}
	switch(state2)
	{
		case c1:
			
			temp1 = 0xFE;
			if(flag==0x01)
			{	
				score2++;
				score++;
				if(score >9)
				{
					score=0;
				}
			}
			//transmit_data(0x01);
			break;
		case c2:
			temp1 = 0xFD;
			if(flag ==0x02)
			{
				score2++;
				score++;
				if(score >9)
                                {
                                        score=0;
                                }

			}
			//transmit_data(0x01);
			break;
		case c3:
			temp1 = 0xFB;
			if(flag==0x03)
			{
				score2++;
				score++;
				if(score >9)
                                {
                                        score=0;
                                }

			}
			//transmit_data(0x01);
			break;
		case c4:
			
			temp1 = 0xF7;
			if(flag==0x04)
			{
				score2++;
				score++;
				if(score >9)
                                {
                                        score=0;
                                }

			}
			//transmit_data(0x01);
			break;
		case c5:
			temp1 = 0xEF;
			if(flag==0x05)
			{
				score2++;
				score++;
				if(score >9)
                                {
                                        score=0;
                                }

			}
			//transmit_data(0x01);
			break;
		default:
			break;
	}
	return state2;
}

int tick(){
	srand(rand());
	int x = rand() % 5;
	unsigned char input2 = ~PINA & 0x02;
	switch(state)
	{
		case beginning:	
				if(x == 0)
                                {
                                        state= d1;
                                }
                                else if(x==1)
                                {
                                        state = d2;
                                }
                                else if(x==2)
                                {
                                        state=d3;
                                }
                                else if(x==3)
                                {
                                        state=d4;
                                }
                                else if(x==4)
                                {
                                        state =d5;
                                }
			
			break;
		case d1:
			if(input2 == 0x02)
                        {
                                state=beginning;
                        }

			if(counter > 24)
                        {
				++timer;
				flag=0;
                                row =0x00;
                                counter=0;
                                if(x == 0)
                                {       
                                        state= d1;
                                }
                                else if(x==1)
                                {
                                        state = d2;
                                }
                                else if(x==2)
                                {
                                        state=d3;
                                }
                                else if(x==3)
                                {
                                        state=d4;
                                }
                                else if(x==4)
                                {
                                        state =d5;
                                }
                        }
                        else if(counter >21)
                        {
				flag=0x01;
                                row = 0x80;
                        }
                        else if(counter >18)
                        {
                                row = 0x40;
                        }
                         else if(counter >15)
                        {
                                row = 0x20;
                        }
                         else if(counter >12)
                        {
                                row = 0x10;
                        }
                         else if(counter >9)
                        {
                                row = 0x08;
                        }
                         else if(counter >6)
                        {
                                row = 0x04;
                        }
                         else if(counter >3)
                        {
                                row = 0x02;
                        }
                        else
                        {
                                row = 0x01;
                        }
			break;
		case d2:
			if(input2 == 0x02)
			{
				state=beginning;
			}
			if(counter > 24)
                        {
				++timer;
				flag=0;
                                row =0x00;
                                counter=0;
                                if(x == 0)
                                {       
                                        state= d1;
                                }
                                else if(x==1)
                                {
                                        state = d2;
                                }
                                else if(x==2)
                                {
                                        state=d3;
                                }
                                else if(x==3)
                                {
                                        state=d4;
                                }
                                else if(x==4)
                                {
                                        state =d5;
                                }
                        }
                        else if(counter >21)
                        {
				flag=0x02;
                                row = 0x80;
                        }
                        else if(counter >18)
                        {
                                row = 0x40;
                        }
                         else if(counter >15)
                        {
                                row = 0x20;
                        }
                         else if(counter >12)
                        {
                                row = 0x10;
                        }
                         else if(counter >9)
                        {
                                row = 0x08;
                        }
                         else if(counter >6)
                        {
                                row = 0x04;
                        }
                         else if(counter >3)
                        {
                                row = 0x02;
                        }
                        else
                        {
                                row = 0x01;
                        }
			break;
		case d3:
			if(input2 == 0x02)
                        {
                                state=beginning;
                        }

			if(counter > 24)
                        {
				++timer;
				flag=0;
                                row =0x00;
                                counter=0;
                                if(x == 0)
                                {       
                                        state= d1;
                                }
                                else if(x==1)
                                {
                                        state = d2;
                                }
                                else if(x==2)
                                {
                                        state=d3;
                                }
                                else if(x==3)
                                {
                                        state=d4;
                                }
                                else if(x==4)
                                {
                                        state =d5;
                                }
                        }
                        else if(counter >21)
                        {
				flag=0x03;
                                row = 0x80;
                        }
                        else if(counter >18)
                        {
                                row = 0x40;
                        }
                         else if(counter >15)
                        {
                                row = 0x20;
                        }
                         else if(counter >12)
                        {
                                row = 0x10;
                        }
                         else if(counter >9)
                        {
                                row = 0x08;
                        }
                         else if(counter >6)
                        {
                                row = 0x04;
                        }
                         else if(counter >3)
                        {
                                row = 0x02;
                        }
                        else
                        {
                                row = 0x01;
                        }
			break;
		case d4:
			if(input2 == 0x02)
                        {
                                state=beginning;
                        }

			if(counter > 24)
                        {
				++timer;
				flag =0;
                                row =0x00;
				counter=0;

                                if(x == 0)
				{
					state= d1;
				}
				else if(x==1)
				{
					state = d2;
				}
				else if(x==2)
				{
					state=d3;
				}
				else if(x==3)
				{
					state=d4;
				}
				else if(x==4)
				{
					state =d5;
				}
                        }
                        else if(counter >21)
                        {
				flag =0x04;
                                row = 0x80;
 			}
                        else if(counter >18)
                        {
                                row = 0x40;
                        }
                         else if(counter >15)
                        {
                                row = 0x20;
                        }
                         else if(counter >12)
                        {
                                row = 0x10;
                        }
                         else if(counter >9)
                        {
                                row = 0x08;
                        }
                        
		       	else if(counter >6)
			{
		       		row = 0x04;
                        }
                         else if(counter >3)
                        {
                                row = 0x02;
                        }
                        else
                        {
                                row = 0x01;
                        }

			break;
		case d5:
			if(input2 == 0x02)
                        {
                                state=beginning;
                        }

			if(counter > 24)
                        {
				flag=0;
                                row =0x00;
                                counter=0;
				++timer;
                                if(x == 0)
                                {       
                                        state= d1;
                                }
                                else if(x==1)
                                {
                                        state = d2;
                                }
                                else if(x==2)
                                {
                                        state=d3;
                                }
                                else if(x==3)
                                {
                                        state=d4;
                                }
                                else if(x==4)
                                {
                                        state =d5;
                                }
                        }
                        else if(counter >21)
                        {
				flag=0x05;
                                row = 0x80;
                        }
                        else if(counter >18)
                        {
                                row = 0x40;
                        }
                         else if(counter >15)
                        {
                                row = 0x20;
                        }
                         else if(counter >12)
                        {
                                row = 0x10;
                        }
                         else if(counter >9)
                        {
                                row = 0x08;
                        }
                         else if(counter >6)
                        {
                                row = 0x04;
                        }
                         else if(counter >3)
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
		case beginning:
			LCD_ClearScreen();
			counter=0;
			timer=0;
			score =0;
			score2=0;
			x=rand()%5;
			break;
 		case d1:
			temp2 = 0xFE;
                       // PORTD = 0xFE;
		//	transmit_data(row);
			x=rand()%5;
			++counter;
                        break;
                case d2:
			temp2 = 0xFD;
                  //     PORTD = 0xFD;
		//	transmit_data(row);
			x= rand()%5;
			++counter;
                        break;
                case d3:
                        temp2	= 0xFB;
		//	PORTD = 0xFB;
		//	transmit_data(row);
			x= rand()%5;
			++counter;
                        break;
                case d4:
                        temp2 = 0xF7;
		//	PORTD = 0xF7;
		//	transmit_data(row);
			x=rand()%5;
			++counter;
                        break;
                case d5:
                        temp2 = 0xEF;
		//	PORTD = 0xEF;
		//	transmit_data(row);
			x=rand()%5;
			++counter;
                        break;
                default:
                        break;
	}

	return state;
}

int tick3()
{
        switch(state3){
                case start: state3=start; break;
                default: break;
        }
        switch(state3){
                case start:
                      PORTD = temp2;
                      transmit_data(row);
                      _delay_ms(175);
                     // PORTD=0x00;
                    // transmit_data(0x00);
                      // _delay_ms(200);
                        PORTD = temp1;
                       transmit_data(0x80);
		       _delay_ms(175);
                //      _delay_ms(10);
              

                default:
                        break;
        }
        return state3;

}

int tick4(){
	switch(state4){
		case showScore:
			state4 = showScore;
			break;
		default:
			break;
	}
	switch(state4){
		case showScore:
			if(timer <15)
			{
				if(score2 < 10)
				{
					LCD_Cursor(1);
					LCD_WriteData(score + '0');
					LCD_Cursor(2);
					LCD_WriteData(47);
					LCD_Cursor(3);
					LCD_WriteData(1+'0');
					LCD_Cursor(4);
					LCD_WriteData(5+'0');
				}
				else if(score2 >=10 && score2 <20)
				{
					LCD_Cursor(1);
					LCD_WriteData(1 + '0');
					LCD_Cursor(2);
					LCD_WriteData(score+'0');
					LCD_Cursor(3);
                                        LCD_WriteData(47);
                                        LCD_Cursor(4);
                                        LCD_WriteData(1+'0');
                                        LCD_Cursor(5);
                                        LCD_WriteData(5+'0');

				}
				else if(score2 >=20 && score2 <25)
                      	 	{
                       		        LCD_Cursor(1);
                        	        LCD_WriteData(2 + '0');
                        	        LCD_Cursor(2);
                             		LCD_WriteData(score+'0');
                       			LCD_Cursor(3);
                                        LCD_WriteData(47);
                                        LCD_Cursor(4);
                                        LCD_WriteData(1+'0');
                                        LCD_Cursor(5);
                                        LCD_WriteData(5+'0');
				}
			}
			if(timer >=15)
			{
				if(score2 >11 )
				{
					LCD_DisplayString(1,"Winner!");
				}
				else if(score2 <= 12)
				{
					LCD_DisplayString(1,"Nice Try!");
				}
			}

			break;
		default:
			break;
	}
	return state4;
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA =0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
	A2D_init();
	LCD_init();
	static task task1;
	static task task2;
	static task task3;
	static task task4;
	task *tasks[] = {&task1,&task2,&task3,&task4};
	const unsigned short numTasks = sizeof(tasks) / sizeof(task*);

	task1.state=0;
	task1.period=100;
	task1.elapsedTime = task1.period;
	task1.TickFct = &tick;

	task2.state = 0;
	task2.period =300;
	task2.elapsedTime = task2.period;
	task2.TickFct = &tick2;

	task3.state=0;
	task3.period=100;
	task3.elapsedTime = task3.period;
	task3.TickFct = &tick3;

	task4.state=0;
	task4.period=100;
	task4.elapsedTime = task4.period;
	task4.TickFct = &tick4;

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
        while (!TimerFlag);
        TimerFlag = 0;

    }
    return 1;
}
