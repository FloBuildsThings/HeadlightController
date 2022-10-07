/*
 * init_Counter2_PWM.c
 *
 * Created: 23.08.2020 14:46:12
 *  Author: flo97
 */ 

#include "init_Counter2_PWM.h"

void init_Counter2_PWM()
{
	//Ausgang setzen
	DDRD |= (1<<DDD3);
		
		
	//PWM Mode - Fast PWM 8-bit
	TCCR2A |= (1<<WGM20);
	TCCR2A |= (1<<WGM21);
	TCCR2B &= ~(1<<WGM22);
	
	//Clock Select - CLK from Prescaler / 256
	TCCR2B &= ~(1<<CS20);
	TCCR2B |= (1<<CS21);
	TCCR2B |= (1<<CS22);
	
/*	//Clock Select - CLK from Prescaler / 1024
	TCCR2B |= (1<<CS20);
	TCCR2B |= (1<<CS21);
	TCCR2B |= (1<<CS22);
*/	
	
	//Output A - Clear OC2A on Compare Match, set OC2A at BOTTOM,(non-inverting mode)
	TCCR2A &= ~ (1<<COM2A1);
	TCCR2A &= ~ (1<<COM2A0);
	
	//Output B - Clear OC2B on Compare Match, set OC2B at BOTTOM,(non-inverting mode).
	TCCR2A |= (1<<COM2B1);
	TCCR2A &= ~ (1<<COM2B0);
	
	//Force Output Compare - off
	TCCR2B &= ~(1<<FOC2A);
	TCCR2B &= ~(1<<FOC2B);

	//Timer/Counter Interrupt Mask Register
	TIMSK2 &= ~(1<<OCIE2B); //no B Match Interrupt
	TIMSK2 &= ~(1<<OCIE2A); //no A Match Interrupt
	TIMSK2 &= ~(1<<TOIE2);  //no Overflow Interrupt

	//Counter
	TCNT2 = 0x00;

	//OutputCompareRegister (PWM Rate)
	OCR2B = 0xFF; //PD3
}