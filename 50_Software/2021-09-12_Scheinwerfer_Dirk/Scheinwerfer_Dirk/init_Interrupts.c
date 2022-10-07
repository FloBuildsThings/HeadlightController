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
	DDRD &= ~(1<<DDD4);
	//BusyLED
	//DDRD |= (1<<DDD0);
	
	//Register for Interrupts
	//EICRA External Interrupt Control Register
	EICRA &= ~(1<<ISC11);
	EICRA &= ~(1<<ISC10);
	EICRA &= ~(1<<ISC01); //1 = INT0 Rising Edge
	EICRA &= ~(1<<ISC00); //1 = INT0 Rising Edge
	
	//EIMSK External Interrupt Mask Register
	EIMSK &= ~(1<<INT1);
	EIMSK &= ~(1<<INT0); //1 = INT0 enable
	
	//EIFR External Interrupt Flag Register //nicht setzen
	EIFR &= ~(1>>INTF1);
	EIFR &= ~(1>>INTF0);
	
	//PCICR Pin Change Interrupt Control Register 
	PCICR |= (1<<PCIE2); //1 = PinChange Interrupt Block 2
	PCICR &= ~(1<<PCIE1); //1 = PinChange Interrupt Block 1
	PCICR &= ~(1<<PCIE0); //1 = PinChange Interrupt Block 0
	
	//PCIFR Pin Change Interrupt Flag Register //nicht setzen
	PCIFR &= ~(1<<PCIF2);
	PCIFR &= ~(1<<PCIF1);
	PCIFR &= ~(1<<PCIF0);
	
	//PCMSK2 Pin Change Interrupt Mask Register
	PCMSK2 &= ~(1<<PCINT23);
	PCMSK2 &= ~(1<<PCINT22);
	PCMSK2 &= ~(1<<PCINT21);
	PCMSK2 |= (1<<PCINT20); //1 = Interrupt aktiv
	PCMSK2 &= ~(1<<PCINT19);
	PCMSK2 &= ~(1<<PCINT18);
	PCMSK2 &= ~(1<<PCINT17);
	PCMSK2 &= ~(1<<PCINT16);
	
	//PCMSK1
	PCMSK1 &= ~(1<<PCINT14);
	PCMSK1 &= ~(1<<PCINT13);
	PCMSK1 &= ~(1<<PCINT12);
	PCMSK1 &= ~(1<<PCINT11);
	PCMSK1 &= ~(1<<PCINT10);
	PCMSK1 &= ~(1<<PCINT9);
	PCMSK1 &= ~(1<<PCINT8);
	
	//PCMSK0
	PCMSK0 &= ~(1<<PCINT7);
	PCMSK0 &= ~(1<<PCINT6);
	PCMSK0 &= ~(1<<PCINT5);
	PCMSK0 &= ~(1<<PCINT4);
	PCMSK0 &= ~(1<<PCINT3);
	PCMSK0 &= ~(1<<PCINT2);
	PCMSK0 &= ~(1<<PCINT1);
	PCMSK0 &= ~(1<<PCINT0);
}