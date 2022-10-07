/*
 * Scheinwerfer_Dirk.c
 *
 * Created: 03.07.2020 08:35:33
 * Author : flo97
 */ 

#include "init_Counter0_PWM.h"

void init_Counter0_PWM()
{
	
	//Ausgang setzen
	DDRD |= (1<<DDD6);
	DDRD |= (1<<DDD5);
	
	
	//PWM Mode - Fast PWM
	TCCR0A |= (1<<WGM00);
	TCCR0A |= (1<<WGM01);
	TCCR0B &= ~(1<<WGM02);
	
	//Clock Select - CLK from Prescaler / 256
	TCCR0B &= ~(1<<CS00);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS02);
	
/*	//Clock Select - CLK from Prescaler / 1024
	TCCR0B |= (1<<CS00);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS02);
*/
		
	//Output A - clear OC0A on Compare Match, set OC0A at BOTTOM,(non-inverting mode). Hardware inv.
	TCCR0A |= (1<<COM0A1);
	TCCR0A &= ~(1<<COM0A0);
	
	//Output B - clear OC0B on Compare Match, set OC0B at BOTTOM,(non-inverting mode). Hardware inv.
	TCCR0A |= (1<<COM0B1);
	TCCR0A &= ~(1<<COM0B0);
	
	//Force Output Compare - only for non-PWM
	TCCR0B &= ~(1<<FOC0A);
	TCCR0B &= ~(1<<FOC0B);


	//Timer/Counter Interrupt Mask Register
	TIMSK0 &= ~(1<<OCIE0B); //no B Match Interrupt
	TIMSK0 &= ~(1<<OCIE0A); //no A Match Interrupt
	TIMSK0 &= ~(1<<TOIE0);  //no Overflow Interrupt

	//Counter
	TCNT0 = 0x00;

	//OutputCompareRegister (PWM Rate)
	OCR0A = 0xFF; //PD6
	OCR0B = 0xFF; //PD5
}