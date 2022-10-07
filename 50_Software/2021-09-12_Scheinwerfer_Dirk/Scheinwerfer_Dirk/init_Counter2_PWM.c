/*
 * init_Counter2_PWM.c
 *
 * Created: 23.08.2020 14:46:12
 *  Author: flo97
 */ 

#include "init_Counter2_PWM.h"

bool init_Counter2_PWM()
{
	//Ausgang setzen
	DDRD |= (1<<DDD3);
		
	//PWM
	//TCCR2A
	TCCR2A &= ~ (1<<COM2A1);
	TCCR2A &= ~ (1<<COM2A0);
	TCCR2A |= (1<<COM2B1);
	TCCR2A &= ~ (1<<COM2B0);
	TCCR2A |= (1<<WGM20);
	TCCR2A |= (1<<WGM21);

	//TCCR2B
	TCCR2B &= ~ (1<<FOC2A);
	TCCR2B &= ~ (1<<FOC2B);
	TCCR2B &= ~ (1<<WGM22);
	TCCR2B &= ~ (1<<CS22);
	TCCR2B &= ~ (1<<CS21);
	TCCR2B |= (1<<CS20);

	//TIMSK2
	TIMSK2 &= ~ (1<<OCIE2B); //B Match Interrupt
	TIMSK2 &= ~ (1<<OCIE2A); //A Match Interrupt
	TIMSK2 &= ~ (1<<TOIE2);  //Overflow Interrupt

	//TIFR0
	//Interrupt Flags for TIMSK0 enabled Bits

	//Counter
	TCNT2 = 0x00;

	//OutputCompareRegister (PWM Rate)
	OCR2A = 0x00; //PB3
	OCR2B = 0x00; //PD3
	
	return true;
}