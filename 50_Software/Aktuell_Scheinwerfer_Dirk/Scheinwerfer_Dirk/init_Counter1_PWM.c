/*
 * init_Counter1_PWM.c
 *
 * Created: 23.08.2020 14:46:12
 *  Author: flo97
 */ 

#include "init_Counter1_PWM.h"

void init_Counter1_PWM()
{
	//Ausgang setzen
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	
	
	//PWM Mode - Fast PWM 8-bit
	TCCR1A |= (1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	//Clock Select - CLK from Prescaler / 256
	TCCR1B &= ~(1<<CS10);
	TCCR1B &= ~(1<<CS11);	
	TCCR1B |= (1<<CS12);
	
/*	//Clock Select - CLK from Prescaler / 1024
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);
*/
	
	//Output A - Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM,(non-inverting mode).
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~(1<<COM1A0);
	
	//Output B - Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM,(non-inverting mode).
	TCCR1A |= (1<<COM1B1);
	TCCR1A &= ~(1<<COM1B0);
	
	//Input Capture Noise Canceler - off
	TCCR1B &= ~(1<<ICNC1);
	
	//Input Capture Edge Select - falling
	TCCR1B &= ~(1<<ICES1);

	//Force Output Compare - off
	TCCR1C &= ~(1<<FOC1A);
	TCCR1C &= ~(1<<FOC1B);	
	
	//Timer/Counter Interrupt Mask Register
	TIMSK1 &= ~(1<<ICIE1); //no Input Capture Interrupt
	TIMSK1 &= ~(1<<OCIE1B); //no B Match Interrupt
	TIMSK1 &= ~(1<<OCIE1A); //no A Match Interrupt
	TIMSK1 &= ~(1<<TOIE1);  //no Overflow Interrupt

	//Counter
	TCNT1 = 0x0000;

	//OutputCompareRegister (PWM Rate)
	OCR1A = 0xFF; //PB1
	OCR1B = 0xFF; //PB2
}