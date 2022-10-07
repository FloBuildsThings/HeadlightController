/*
 * Scheinwerfer_Dirk.c
 *
 * Created: 03.07.2020 08:35:33
 * Author : flo97
 */ 

#include "init_ADC.h"

void init_ADC()
{
	
	//ADC Reference
	ADMUX &= ~(1<<REFS1);
	ADMUX &= ~(1<<REFS0);
	
	//ADC Left Adjust - on
	ADMUX |= (1<<ADLAR);
	
	//ADC Channel Selection
	//ADC Channel0
	ADMUX &= ~(1<<MUX3);
	ADMUX &= ~(1<<MUX2);
	ADMUX &= ~(1<<MUX1);
	ADMUX &= ~(1<<MUX0);
	//ADC Channel1
	/*
	ADMUX &= ~(1<<MUX3);
	ADMUX &= ~(1<<MUX2);
	ADMUX &= ~(1<<MUX1);
	ADMUX |= (1<<MUX0);
	*/
	//ADC Channel2
	/*
	ADMUX &= ~(1<<MUX3);
	ADMUX &= ~(1<<MUX2);
	ADMUX |= (1<<MUX1);
	ADMUX &= ~(1<<MUX0);
	*/
	//ADC Channel3
	/*
	ADMUX &= ~(1<<MUX3);
	ADMUX &= ~(1<<MUX2);
	ADMUX |= (1<<MUX1);
	ADMUX |= (1<<MUX0);
	*/
	//ADC Channel4
	/*
	ADMUX &= ~(1<<MUX3);
	ADMUX |= (1<<MUX2);
	ADMUX &= ~(1<<MUX1);
	ADMUX &= ~(1<<MUX0);
	*/
	//ADC Channel5
	/*
	ADMUX &= ~(1<<MUX3);
	ADMUX |= (1<<MUX2);
	ADMUX &= ~(1<<MUX1);
	ADMUX |= (1<<MUX0);
	*/
	//ADC Channel6
	/*
	ADMUX &= ~(1<<MUX3);
	ADMUX |= (1<<MUX2);
	ADMUX |= (1<<MUX1);
	ADMUX &= ~(1<<MUX0);
	*/
	//ADC Channel7
	/*
	ADMUX &= ~(1<<MUX3);
	ADMUX |= (1<<MUX2);
	ADMUX |= (1<<MUX1);
	ADMUX |= (1<<MUX0);
	*/
	//ADC Channel8
	/*
	ADMUX |= (1<<MUX3);
	ADMUX |= (1<<MUX2);
	ADMUX |= (1<<MUX1);
	ADMUX |= (1<<MUX0);
	*/
	//1.1 V_BG
	/*
	ADMUX |= (1<<MUX3);
	ADMUX |= (1<<MUX2);
	ADMUX |= (1<<MUX1);
	ADMUX &= ~(1<<MUX0);
	*/
	//0 V GND
	/*
	ADMUX |= (1<<MUX3);
	ADMUX |= (1<<MUX2);
	ADMUX |= (1<<MUX1);
	ADMUX |= (1<<MUX0);
	*/

	//ADC Auto Trigger - off
	ADCSRA &= ~(1<<ADATE);	
	
	//ADC Prescaler - Clock with Prescaler/16 = 500 kHz
	ADCSRA |= (1<<ADPS2);
	ADCSRA &= ~(1<<ADPS1);
	ADCSRA &= ~(1<<ADPS0);
	
//	//ADC Prescaler - Clock with Prescaler/8 = 1 MHz
//	ADCSRA &= ~(1<<ADPS2);
//	ADCSRA |= (1<<ADPS1);
//	ADCSRA |= (1<<ADPS0);

	//ADC Auto Trigger Source - Free running
	ADCSRB &= ~(1<<ADTS2);
	ADCSRB &= ~(1<<ADTS1);
	ADCSRB &= ~(1<<ADTS0);
	
	//Analog Comparator Multiplexed Input - off
	ADCSRB &= ~(1<<ACME);
	
	//First Run
	//ADC enable
	ADCSRA |= (1<<ADEN);
	
	//ADC First conversion
	ADCSRA |= (1<<ADSC);
	
	//DUmmy Readout
	while (ADCSRA & (1<<ADSC)) {}        // wait for hardware to finis
	
	// ADCW has to be read so that the next conversion has an effect
	uint8_t result = ADCH;	
}

uint8_t readADC(uint8_t channel)
{
	// select channel bits
	ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
	ADCSRA |= (1<<ADSC);            // single conversion
	while (ADCSRA & (1<<ADSC) ) {}  // wait for hardware to finish
	return ADCH;                    // read ADC value and return as result	
}
		