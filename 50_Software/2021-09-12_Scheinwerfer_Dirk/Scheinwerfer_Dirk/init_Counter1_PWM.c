/*
 * init_Counter1_PWM.c
 *
 * Created: 23.08.2020 14:46:12
 *  Author: flo97
 */ 

#include "init_Counter1_PWM.h"

bool init_Counter1_PWM()
{
	//Ausgang setzen
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	
	//PWM
	//TCCR1A
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~ (1<<COM1A0);
	TCCR1A |= (1<<COM1B1);
	TCCR1A &= ~ (1<<COM1B0);


	TCCR1A |= (1<<WGM10);
	TCCR1A &= ~ (1<<WGM11);

	//TCCR1B
	TCCR1B &= ~ (1<<ICNC1);
	TCCR1B &= ~ (1<<ICES1);

	TCCR1B &= ~ (1<<WGM13);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~ (1<<CS12);
	TCCR1B &= ~ (1<<CS11);
	TCCR1B |= (1<<CS10);
	
	//TCCR1C
	TCCR1C &= ~ (1<<FOC1A);
	TCCR1C &= ~ (1<<FOC1B);	
	
	//TIMSK1
	TIMSK1 &= ~ (1<<ICIE1); //
	TIMSK1 &= ~ (1<<OCIE1B); //B Match Interrupt
	TIMSK1 &= ~ (1<<OCIE1A); //A Match Interrupt
	TIMSK1 &= ~ (1<<TOIE1);  //Overflow Interrupt

	//TIFR0
	//Interrupt Flags for TIMSK0 enabled Bits

	//Counter
	TCNT1 = 0x00;

	//OutputCompareRegister (PWM Rate)
	OCR1A = 0x00; //PB1
	OCR1B = 0x00; //PB2
	
	return true;
}