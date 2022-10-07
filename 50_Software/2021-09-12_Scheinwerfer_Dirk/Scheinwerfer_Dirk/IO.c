/*
 * IO.c
 *
 * Created: 26.05.2021 13:34:41
 *  Author: flo97
 */ 

#include "IO.h"

bool init_IO()
{
	DDRD |= (1<<DDD0);
	DDRD |= (1<<DDD1);
		
	return true;
}

bool set_Output(uint8_t Pin)
{
	PORTD |= (1<<Pin);
	return true;
}

bool reset_Output(uint8_t Pin)
{
	PORTD &= ~(1<<Pin);
	return true;
}

/*

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

*/