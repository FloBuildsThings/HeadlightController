/*
 * Scheinwerfer_Dirk.c
 *
 * Created: 03.07.2020 08:35:33
 * Author : flo97
 */ 

#include "init_ADC.h"

void init_ADC()
{
	//ADCSRA
	ADCSRA = 0x00;
	//20MHz/128 = 156.25kHz
	ADCSRA |= (1<<ADPS2);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS0);
	
	ADCSRA &= ~ (1<<ADATE);	
	
	//ADCSRB
	ADCSRB = 0x00;
	ADCSRB &= ~ (1<<ACME);
	ADCSRB &= ~ (1<<ADTS2);
	ADCSRB &= ~ (1<<ADTS1);
	ADCSRB &= ~ (1<<ADTS0);
	
	//ADC
	//ADMUX
	ADMUX = 0x00;
	ADMUX &= ~ (1<<REFS1);
	ADMUX &= ~ (1<<REFS0);
	ADMUX |= (1<<ADLAR);
	
	//ADC Channel0
	ADMUX &= ~ (1<<MUX3);
	ADMUX &= ~ (1<<MUX2);
	ADMUX &= ~ (1<<MUX1);
	ADMUX &= ~ (1<<MUX0);
	//ADC Channel1
	/*
	ADMUX &= ~ (1<<MUX3);
	ADMUX &= ~ (1<<MUX2);
	ADMUX &= ~ (1<<MUX1);
	ADMUX |= (1<<MUX0);
	*/
	
	//first run
	ADCSRA |= (1<<ADEN);		//start ADC
	
	
	// after activation of ADC a dummy readout is recommended
	ADCSRA |= (1<<ADSC);                  // convert ADC voltage
	
	while (ADCSRA & (1<<ADSC) ) {}        // wait for hardware to finis
	
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
		