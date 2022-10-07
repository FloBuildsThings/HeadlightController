/*
 * init_Interrupts.c
 *
 * Created: 13.12.2020 22:58:48
 *  Author: flo97
 */ 

#include "init_Interrupts.h"

void init_Interrupts()
{
	//Ausgang/Eingang setzen (1=Ausgang; 0=Eingang)
	//Interrupts
	DDRD &= ~(1<<DDD2);
	
	//INT0 - on - rising edge
	EIMSK |= (1<<INT0); //1 = INT0 enable
	EICRA |= (1<<ISC01); //1 = INT0 Falling Edge
	EICRA &= ~(1<<ISC00); //1 = INT0 Falling Edge
	
	//INT1 - off - low
	EIMSK &= ~(1<<INT1);
	EICRA &= ~(1<<ISC11);
	EICRA &= ~(1<<ISC10);
	
	//Pin Change Interrupt 0
	PCICR &= ~(1<<PCIE0); //1 = PinChange Interrupt Block 0
	PCMSK0 &= ~(1<<PCINT0);
	PCMSK0 &= ~(1<<PCINT1);
	PCMSK0 &= ~(1<<PCINT2);
	PCMSK0 &= ~(1<<PCINT3);
	PCMSK0 &= ~(1<<PCINT4);
	PCMSK0 &= ~(1<<PCINT5);
	PCMSK0 &= ~(1<<PCINT6);
	PCMSK0 &= ~(1<<PCINT7);
		
	//Pin Change Interrupt 1
	PCICR &= ~(1<<PCIE1); //1 = PinChange Interrupt Block 1
	PCMSK1 &= ~(1<<PCINT8);
	PCMSK1 &= ~(1<<PCINT9);
	PCMSK1 &= ~(1<<PCINT10);
	PCMSK1 &= ~(1<<PCINT11);
	PCMSK1 &= ~(1<<PCINT12);
	PCMSK1 &= ~(1<<PCINT13);
	PCMSK1 &= ~(1<<PCINT14);
	
	//Pin Change Interrupt 2
	PCICR &= ~(1<<PCIE2); //1 = PinChange Interrupt Block 2
	PCMSK2 &= ~(1<<PCINT16);
	PCMSK2 &= ~(1<<PCINT17);
	PCMSK2 &= ~(1<<PCINT18);
	PCMSK2 &= ~(1<<PCINT19);
	PCMSK2 &= ~(1<<PCINT20);
	PCMSK2 &= ~(1<<PCINT21);
	PCMSK2 &= ~(1<<PCINT22);
	PCMSK2 &= ~(1<<PCINT23);	
}