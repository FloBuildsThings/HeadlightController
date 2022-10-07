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
	LED_1	PCINT16/RXD			PD0	 2	27 PC4	ADC4/SDA/PCINT12	
	LED_2	PCINT17/TXD			PD1	 3	26 PC3	ADC3/PCINT11		Poti Sys
	SW_MODE	PCINT18/INT0		PD2  4	25 PC2	ADC2/PCINT10		Poti B
	PWM B	PCINT19/OC2B/INT1	PD3  5	24 PC1	ADC1/PCINT9			Poti G
			PCINT20/XCK/T0		PD4  6	23 PC0	ADC0/PCINT8			Poti R
	5V							VCC  7	22 GND						0V
	0V							GND  8	21 AREF						5V
			PCINT6/XTAL1/TOSC1	PB6	 9	20 AVCC						5V
			PCINT7/XTAL2/TOSC2	PB7 10	19 PB5	SCK/PCINT5			ISP0
	FET1.2	PCINT21/OC0B/T1		PD5 11	18 PB4	MISO/PCINT4			ISP2
	FET1.1	PCINT22/OC0A/AIN0	PD6 12	17 PB3	MOSI/OC2A/PCINT3	ISP8
			PCINT23/AIN1		PC7 13	16 PB2	SS/OC1B/PCINT2		PWM G
			PCINT0/CLKO/ICP1	PB0 14	15 PB1	OC1A/PCINT1			PWM R
	
	ISP1 GND 
	ISP3 5V
*/

#define F_CPU 8000000UL

#define SweepSpeedMax 200 //RGB sweep time in 탎
#define SweepSpeedMin 50000 //RGB sweep time in 탎
#define SweepSpeedDefault 10000 //RGB sweep time in 탎
#define SweepSpeedFast 200 //RGB sweep time in 탎

#define LEDLimitMax 0x60
#define LEDLimitMin 0xEF
#define LEDSweepPrescaler 3

#define StartMode 0

//#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

#include "init_Interrupts.h"
#include "init_Counter0_PWM.h"
#include "init_Counter1_PWM.h"
#include "init_Counter2_PWM.h"
#include "init_ADC.h"
#include "init_Test_LED.h"

//Variables
uint8_t lMode = StartMode;
uint16_t SweepSpeed = SweepSpeedDefault;

bool change_Mode = false;

uint8_t PotiR = 0;
uint8_t PotiG = 0;
uint8_t PotiB = 0;
uint8_t PotiSys = 0x20;

uint8_t ValueR = 0xFF;
uint8_t ValueG = 0xFF;
uint8_t ValueB = 0xFF;

uint8_t ValueLED = 0xFF;
uint8_t LEDSweepPrescaleCounter = 0x00;

uint8_t Int_Counter = 0;

bool RUp = 1;
bool GUp = 0;
bool BUp = 0;

bool RDown = 0;
bool GDown = 0;
bool BDown = 1;

bool LEDUp = 1;

void init()
{
	init_Interrupts();
	
	init_Counter0_PWM();
	init_Counter1_PWM();
	init_Counter2_PWM();
	
	init_ADC();
}

void testLoop()
{
	OCR0A = 0xFF; //LED Bot 0xFF=off 0x00=on
	OCR0B = 0xFF; //LED Top 0xFF=off 0x00=on
	OCR1A = 0XFF; //R 0xFF=off 0x00=on
	OCR1B = 0xFF; //G 0xFF=off 0x00=on
	OCR2B = 0xFF; //B 0xFF=off 0x00=on
}

void readPotis()
{
	PotiR = readADC(0);
	PotiG = readADC(1);
	PotiB = readADC(2);
	PotiSys = readADC(3);
	
}

void RGBSweep()
{
	if(RUp)
	{
		ValueR--;
		if(ValueR<=0)
		{
			ValueR = 0;
			GUp = true;
			RUp = false;
			BDown = true;
		}
	}
	
	if(GUp)
	{
		ValueG--;
		if(ValueG<=0)
		{
			ValueG = 0;
			BUp = true;
			GUp = false;
			RDown = true;
		}
	}
	
	if(BUp)
	{
		ValueB--;
		if(ValueB<=0)
		{
			ValueB = 0;
			RUp = true;
			BUp = false;
			GDown = true;
		}
	}
	
	if(RDown)
	{
		ValueR++;
		if(ValueR>=255)
		{
			ValueR=255;
			RDown = false;
			GDown = true;
		}
	}
	if(GDown)
	{
		ValueG++;
		if(ValueG>=255)
		{
			ValueG=255;
			GDown = false;
			BDown = true;
		}
	}
	
	if(BDown)
	{
		ValueB++;
		if(ValueB>=255)
		{
			ValueB=255;
			BDown = false;
			RDown = true;
		}
	}
	
	
	OCR1A = ValueR;
	OCR1B = ValueG;
	OCR2B = ValueB;
}

void LEDSweep()
{
	if(LEDSweepPrescaleCounter >= LEDSweepPrescaler)
	{
		LEDSweepPrescaleCounter = 0;
		if(LEDUp)
		{
			ValueLED--;
			if(ValueLED <= LEDLimitMax)
			{
				ValueLED = LEDLimitMax;
				LEDUp = false;
			}
		}
		else
		{
			ValueLED++;
			if(ValueLED >= LEDLimitMin)
			{
				ValueLED = LEDLimitMin;
				LEDUp = true;
			}
		}
		OCR0A = ValueLED;
		OCR0B = OCR0A;
	}
	else
	{
		LEDSweepPrescaleCounter++;
	}
}

int main(void)
{
	//Init
	init();
	sei();
	
	testLoop();
	

	
	//Code   
	while (1)
	{   
		if(lMode == 0)
		{
			LEDSweep();
			RGBSweep();
			_delay_us(SweepSpeedDefault);
		}
		else if(lMode == 1)
		{
			LEDSweep();
			RGBSweep();
			_delay_us(SweepSpeedFast);
		}
		else if(lMode == 2)
		{
			OCR0A = PotiSys;
			OCR0B = OCR0A;
			
			OCR1A = PotiR;
			OCR1B = PotiG;
			OCR2B = PotiB;
			_delay_us(SweepSpeedDefault);
		}
		else if(lMode ==  3)
		{
			OCR0A = PotiSys;
			OCR0B = OCR0A;
			
			RGBSweep();
			_delay_us(SweepSpeedDefault);
		}
		else
		{
			lMode = 0;
		}
		
		if(change_Mode == true)
		{
			lMode++;
			if(lMode >= 4)
			{
				lMode = 0;
			}
			
			change_Mode = false;
			Int_Counter = 0;
		}
		readPotis();		
	}		
}

ISR (INT0_vect)
{
	change_Mode = true;
	Int_Counter++;
}
