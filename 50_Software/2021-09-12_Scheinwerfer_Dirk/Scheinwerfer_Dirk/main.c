/*
 * Scheinwerfer_Dirk.c
 *
 * Created: 03.07.2020 08:35:33
 * Author : flo97
 */ 

/*
	Controller : ATMEGA328P U
	
	Pinout:
									   V
	ISP5	PCINT14/RESET		PC6	 1	28 PC5	ADC5/SCL/PCINT13	
	LED1	PCINT16/RXD			PD0	 2	27 PC4	ADC4/SDA/PCINT12
	LED2	PCINT17/TXD			PD1	 3	26 PC3	ADC3/PCINT11		POTI SYS
	SW_Mode	PCINT18/INT0		PD2  4	25 PC2	ADC2/PCINT10		POTI B
	PWM B	PCINT19/OC2B/INT1	PD3  5	24 PC1	ADC1/PCINT9			POTI G
			PCINT20/XCK/T0		PD4  6	23 PC0	ADC0/PCINT8			POTI R
	5V							VCC  7	22 GND						0V
	0V							GND  8	21 AREF						5V
			PCINT6/XTAL1/TOSC1	PB6	 9	20 AVCC						5V
			PCINT7/XTAL2/TOSC2	PB7 10	19 PB5	SCK/PCINT5			ISP0
	FET1.2	PCINT21/OC0B/T1		PD5 11	18 PB4	MISO/PCINT4			ISP2
	FET1.1	PCINT22/OC0A/AIN0	PD6 12	17 PB3	MOSI/OC2A/PCINT3	ISP8
			PCINT23/AIN1		PC7 13	16 PB2	SS/OC1B/PCINT2		PWM G
	SWITCH	PCINT0/CLKO/ICP1	PB0 14	15 PB1	OC1A/PCINT1			PWM R
	
	ISP1 GND 
	ISP3 5V
*/

#define F_CPU 8000000UL

#define BufferSize 9

#define LightOut 0x00
#define LightMid 0x6F
#define LightFull 0xFF
#define LightFadeOut 0x0F
#define LightHighThreshold 200
#define LightLowThreshold -200
#define SweepSpeed 10 //RGB sweep time in µs

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

#include "init_Counter0_PWM.h"
#include "init_Counter1_PWM.h"
#include "init_Counter2_PWM.h"
#include "init_ADC.h"
#include "IO.h"

#include "init_Test_LED.h"
#include "init_Interrupts.h"

bool change_Mode = false;

bool init()
{

	if(!init_Counter0_PWM())return false;
	if(!init_Counter1_PWM())return false;
	if(!init_Counter2_PWM())return false;
	
	if(!init_ADC())return false;
	
	if(!init_IO())return false;
	
	//init_Test_LED();
		//init_Interrupts();
		
	return true;
}

int main(void)
{
	//Init
	bool initSuccessfull = init();
	   
	//Variables   
	
	uint8_t PotiR = 0;
	uint8_t PotiG = 0;
	uint8_t PotiB = 0;
	uint8_t PotiSys = 0;
	
	uint8_t lMode = 4;
	
	
	
	uint8_t PotiLowThr = LightOut;
	uint8_t PotiHighThr = LightOut;

	
	uint8_t ValueR = 0;
	uint8_t ValueG = 0;
	uint8_t ValueB = 0;
	
	bool RUp = 1;
	bool GUp = 0;
	bool BUp = 0;
	
	bool RDown = 0;
	bool GDown = 0;
	bool BDown = 1;
		
	sei();
	
	//Code   
	while (initSuccessfull)
	{   
	
		PotiR = readADC(0);
		PotiG = readADC(1);
		PotiB = readADC(2);
		PotiSys = readADC(3);
			
		/*	
			
		OCR1A = PotiR; // R!
		OCR1B = PotiG; // G!
		OCR2B = PotiB; // B!
		//OCR2B = 0xFF;
		
		*/
		
		/*
		_delay_ms(100);
		
		OCR1A = 0x00;
		OCR1B = 0x00;
		OCR2B = 0x00;
		
		set_Output(LED1);
		reset_Output(LED2);
		
		_delay_ms(100);
		
		OCR1A = 0xFF;
		OCR1B = 0xFF;
		OCR2B = 0xFF;
		
		set_Output(LED2);
		reset_Output(LED1);
		
		_delay_ms(100);
		
		*/
			
		if(lMode == 1)
		{
			
			OCR1A = PotiR;
			OCR1B = PotiG;
			OCR2B = PotiB;
			
			_delay_ms(10);
		}
								
		//Blink slow
		if(lMode == 2)
		{
			OCR0A = LightOut;
			OCR0B = LightOut;
			_delay_ms(250);
			OCR0A = LightMid;
			_delay_ms(250);
			OCR0B = LightFull;
			_delay_ms(250);
			OCR0A = LightFull;
			_delay_ms(250);
			OCR0B = LightMid;
			_delay_ms(250);
		}
		
		//Blink fast
		else if(lMode == 3)
		{
			OCR0A = LightOut;
			OCR0B = LightOut;
			_delay_ms(50);
			OCR0A = 0x20;
			_delay_ms(50);
			OCR0B = LightFull;
			_delay_ms(50);
			OCR0A = 0x40;
			_delay_ms(50);
			OCR0B = 0xDF;
			_delay_ms(50);
			OCR0A = 0x60;
			_delay_ms(50);
			OCR0B = 0xBF;
			_delay_ms(50);
			OCR0A = 0x80;
			_delay_ms(50);
			OCR0B = LightMid;
			_delay_ms(50);
			OCR0A = 0xA0;
			_delay_ms(50);
			OCR0B = LightMid;
			_delay_ms(50);
			OCR0A = 0xC0;
			_delay_ms(50);
			OCR0B = 0x5F;
			_delay_ms(50);
			OCR0A = 0xE0;
			_delay_ms(50);
			OCR0B = 0x3F;
			_delay_ms(50);
			OCR0A = LightFull;
			_delay_ms(50);
			OCR0B = 0x1F;
			_delay_ms(50);
			
		}
		
		//RGB Sweep
		else if(lMode == 4)
		{
			if(RUp)
			{
				ValueR++;
				if(ValueR>=255)
				{
					ValueR = 255;
					GUp = true;
					RUp = false;
					BDown = true;
				}
			}
			
			if(GUp)
			{
				ValueG++;
				if(ValueG>=255)
				{
					ValueG = 255;
					BUp = true;
					GUp = false;
					RDown = true;
				}
			}
			
			if(BUp)
			{
				ValueB++;
				if(ValueB>=255)
				{
					ValueB = 255;
					RUp = true;
					BUp = false;
					GDown = true;
				}
			}
			
			if(RDown)
			{
				ValueR--;
				if(ValueR<=0)
				{
					ValueR=0;
					RDown = false;
					GDown = true;
				}
			}
			if(GDown)
			{
				ValueG--;
				if(ValueG<=0)
				{
					ValueG=0;
					GDown = false;
					BDown = true;
				}
			}
			
			if(BDown)
			{
				ValueB--;
				if(ValueB<=0)
				{
					ValueB=0;
					BDown = false;
					RDown = true;
				}
			}
			
			
			OCR1A = ValueR;
			OCR1B = ValueG;
			OCR2B = ValueB;
			
			_delay_us(SweepSpeed);

		}
				
		//Off
		else
		{
			_delay_ms(250);
		}
		
		if(change_Mode)
		{
			lMode++;
			
			if(lMode >= 5)
			{
				lMode = 0;
			}
			change_Mode = false;
			set_Test_LED(false);
			sei();
		}
	}		
}


//ISR INT0

ISR (INT0_vect)
{
	change_Mode = true;
	//set_Test_LED(true);
}

/*
//ISR PCINT20

ISR (PCINT2_vect)
{
	change_Mode = true;
	set_Test_LED(true);
}
*/