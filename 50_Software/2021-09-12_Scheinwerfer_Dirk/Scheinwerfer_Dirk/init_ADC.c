/*
 * Scheinwerfer_Dirk.c
 *
 * Created: 03.07.2020 08:35:33
 * Author : flo97
 */ 

#include "init_ADC.h"

bool init_ADC()
{
	//ADMUX - ADC Multiplexer
	//Ref Pin = 00
	ADMUX &= ~(1<<REFS1);
	ADMUX &= ~(1<<REFS0);
	//Left Adj
	ADMUX |= (1<<ADLAR);
	//Channel select - 0
	ADMUX &= ~(1<<MUX3);
	ADMUX &= ~(1<<MUX2);
	ADMUX &= ~(1<<MUX1);
	ADMUX &= ~(1<<MUX0);
	
	//ADCSR - ADC Control and Status
	//A
	ADCSRA = 0x00;
	//ADC Enable
	ADCSRA &= ~(1<<ADEN);
	//ADC Start Conversion
	ADCSRA &= ~(1<<ADSC);
	//Auto Trigger
	ADCSRA &= ~(1<<ADATE);
	//Interrupt
	ADCSRA &= ~(1<<ADIF);
	ADCSRA &= ~(1<<ADIE);
	//Clock - 2,2,4,8,16,32,64,128
	ADCSRA |= (1<<ADPS2);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS0);
	
	//B
	ADCSRB = 0x00;
	//Analog Comperator
	ADCSRB &= ~ (1<<ACME);
	//Auto Trigger Source
	ADCSRB &= ~ (1<<ADTS2);
	ADCSRB &= ~ (1<<ADTS1);
	ADCSRB &= ~ (1<<ADTS0);
	
	//DIDR0 - Digital Input Buffer Disable - do for every Analog Input
	DIDR0 = 0x00;
	DIDR0 &= ~(1<<ADC5D);
	DIDR0 &= ~(1<<ADC4D);
	DIDR0 |= (1<<ADC3D);
	DIDR0 |= (1<<ADC2D);
	DIDR0 |= (1<<ADC1D);
	DIDR0 |= (1<<ADC0D);
		
	//Start ADC
	ADCSRA |= (1<<ADEN);
	
	//Dummy Readout
	//Start
	ADCSRA |= (1<<ADSC);
	//Wait for hardware
	while(ADCSRA & (1<<ADSC)){}        
	//Get Result
	uint8_t result = ADCH;	
	
	return true;
}

uint8_t readADC(uint8_t channel)
{
	//Select Channel
	ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
	//Start Readout
	ADCSRA |= (1<<ADSC);
	//Wait for Hardware            
	while(ADCSRA & (1<<ADSC)){}
	//Return Value  
	return ADCH;	
}		