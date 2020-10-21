/*
 * all_external_interrupts.c
 *
 * Created: 16/07/2020 11:21:58 م
 *  Author: mostafa gomaa
 */ 

#include <avr/io.h>
//including interrupts header file
//including delay header file
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char i;
unsigned char num[] ={0,1,2,3,4,5,6,7,8,9};	

//ISR for INT0
ISR(INT0_vect)
{
	
		PORTA = 0x0f;
		_delay_ms(1000);
		PORTA = 0x00;
		_delay_ms(1000);
	
}
//configuration function for INT0
void INT0_initit (void)
{
	SREG &= (~(1<<7));   //disables global interrupts
	GICR |= (1<<INT0);   //enables INT0 source
	MCUCR |= (1<<ISC01);  //the action is falling edge
	MCUCR &= (~(1<<ISC00));
	SREG |= (1<<7);       //enables global interrupts
}

//ISR for INT1
ISR(INT1_vect)
{
	for(i = 0;i<10;i++)
	{
	
	PORTC = num[i];
	_delay_ms(500);
	}
	
	
}
//configuration function for INT1
void INT1_initit (void)
{
	SREG &= (~(1<<7));   //disables global interrupts
	GICR |= (1<<INT1);   //enables INT1 source
	MCUCR |= (1<<ISC11);  //the action is falling edge
	MCUCR &= (~(ISC10));
	SREG |= (1<<7);       //enables global interrupts
	
}

//ISR for INT2
ISR(INT2_vect)
{
	//rotating the motor for 5 seconds
	PORTB &= (~(1<<PB6));
	PORTB |= (1<<PB7);
	_delay_ms(5000);
	PORTB |= (1<<PB6);
	PORTB |= (1<<PB7);
	
}

//configuration function for INT2
void INT2_initit (void)
{
	SREG &= (~(1<<7));   //disables global interrupts
	GICR |= (1<<INT2);   //enables INT2 source
	MCUCSR &= (~(1<<ISC2)); //the action is falling edge
	SREG |= (1<<7);       //enables global interrupts
	
}

int main(void)
{ 
	//registers direction and initial values
	DDRC |= ((1<<PC0) | (1<<PC1) |(1<<PC2) | (1<<PC3));  //four output pins for 7-seg
	PORTC &=(~((1<<PC0)	|(1<<PC1)	|(1<<PC2)	|(1<<PC3))) ;    //initial value is zero
	DDRA = 0x0f;			//four leds
	PORTA = 0x00;			//all leds are off
	DDRB |= (1<<PB6);		 //motor pins
	DDRB |= (1<<PB7);
	PORTB |= (1<<PB6);		//motor is off
	PORTB |= (1<<PB7);
	DDRD &= (~(1<<PD2));    //PD2/INT0	input pin
	DDRD &= (~(1<<PD3));    //PD3/INT1	input pin
	DDRB |= (~(1<<PB2));    //PB2/INT2	input pin
	
	//calling interrupts functions
	INT0_initit();
	INT1_initit();
	INT2_initit();
	
    while(1)
    {
        //main code 
    }
}