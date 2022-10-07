/*
 * IO.h
 *
 * Created: 26.05.2021 13:34:57
 *  Author: flo97
 */ 


#ifndef IO_H_
#define IO_H_

#define SW_Mode			
#define LED1			PORTD0
#define LED2			PORTD1

#include <avr/io.h>
#include <stdbool.h>

bool init_IO();
bool set_Output(uint8_t Pin);
bool reset_Output(uint8_t Pin);

#endif /* IO_H_ */