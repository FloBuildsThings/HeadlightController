/*
 * Scheinwerfer_Dirk.c
 *
 * Created: 03.07.2020 08:35:33
 * Author : flo97
 */ 

#include "init_Counter0_PWM.h"

void init_Counter0_PWM()
{
	//PWM
	//TCCR0A
	TCCR0A |= (1<<COM0A1);
	TCCR0A |= (1<<COM0A0);
	TCCR0A |= (1<<COM0B1);
	TCCR0A |= (1<<COM0B0);


	TCCR0A |= (1<<WGM00);
	TCCR0A |= (1<<WGM01);

	//TCCR0B
	TCCR0B &= ~ (1<<FOC0A);
	TCCR0B &= ~ (1<<FOC0B);


	TCCR0B &= ~ (1<<WGM02);
	TCCR0B |= (1<<CS02);
	TCCR0B &= ~ (1<<CS01);
	TCCR0B |= (1<<CS00);

	//TIMSK0
	TIMSK0 &= ~ (1<<OCIE0B); //B Match Interrupt
	TIMSK0 &= ~ (1<<OCIE0A); //A Match Interrupt
	TIMSK0 &= ~ (1<<TOIE0);  //Overflow Interrupt

	//TIFR0
	//Ineterrupt Flags for TIMSK0 enabled Bits

	//Counter
	TCNT0 = 0x00;

	//OutputCompareRegister (PWM Rate)
	OCR0A = 0x00; //PD6
	OCR0B = 0x00; //PD5
}