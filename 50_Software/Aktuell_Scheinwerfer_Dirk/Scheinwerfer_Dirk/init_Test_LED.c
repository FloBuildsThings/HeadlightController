/*
 * init_Test_LED.c
 *
 * Created: 13.12.2020 23:50:58
 *  Author: flo97
 */ 

#include "init_Test_LED.h"

void init_Test_LED()
{
	DDRD |= (1<<DDD2);
}

bool set_Test_LED(bool pvalue)
{
	if(pvalue)
	{
		PORTD |= (1<<PIND2);
	}
	else
	{
		PORTD &= ~(1<<PIND2);
	}
	
}