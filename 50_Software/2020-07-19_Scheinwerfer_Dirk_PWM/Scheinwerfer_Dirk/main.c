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
	ISP5	PCINT14/RESET		PC6	 1	28 PC5	ADC5/SCL/PCINT13	AUX_IN
			PCINT16/RXD			PD0	 2	27 PC4	ADC4/SDA/PCINT12	POTI B
			PCINT17/TXD			PD1	 3	26 PC3	ADC3/PCINT11		POTI G
	MODE	PCINT18/INT0		PD2  4	25 PC2	ADC2/PCINT10		POTI R
	PWM B	PCINT19/OC2B/INT1	PD3  5	24 PC1	ADC1/PCINT9			High Threshold
			PCINT20/XCK/T0		PD4  6	23 PC0	ADC0/PCINT8			Low Threshold
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

#define F_CPU 20000000UL

#define BufferSize 9

#define LightOut 0x00
#define LightMid 0x6F
#define LightFull 0xFF
#define LightFadeOut 0x0F
#define LightHighThreshold 200
#define LightLowThreshold -200

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

#include "init_Counter0_PWM.h"
#include "init_Counter1_PWM.h"
#include "init_Counter2_PWM.h"
#include "init_ADC.h"


void init()
{
	
	init_Counter0_PWM();
	init_Counter1_PWM();
	init_Counter2_PWM();
	
	init_ADC();
	
}


int main(void)
{
	
	uint8_t PotiR = 0b00000000;
	uint8_t PotiG = 0b00000000;
	uint8_t PotiB = 0b00000000;
	
	//DDR
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	
	DDRD |= (1<<DDD3);
	
	//init_Counter1_PWM
	//PWM
	//TCCR1A
	TCCR1A |= (1<<COM1A1);
	TCCR1A &= ~ (1<<COM1A0);
	TCCR1A |= (1<<COM1B1);
	TCCR1A &= ~ (1<<COM1B0);
	TCCR1A |= (1<<WGM10);
	TCCR1A &= ~ (1<<WGM11);

	//TCCR1B
	TCCR1B &= ~ (1<<ICNC1);
	TCCR1B &= ~ (1<<ICES1);
	TCCR1B &= ~ (1<<WGM13);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~ (1<<CS12);
	TCCR1B &= ~ (1<<CS11);
	TCCR1B |= (1<<CS10);
		
	//TCCR1C
	TCCR1C &= ~ (1<<FOC1A);
	TCCR1C &= ~ (1<<FOC1B);
		
	//TIMSK1
	TIMSK1 &= ~ (1<<ICIE1); //
	TIMSK1 &= ~ (1<<OCIE1B); //B Match Interrupt
	TIMSK1 &= ~ (1<<OCIE1A); //A Match Interrupt
	TIMSK1 &= ~ (1<<TOIE1);  //Overflow Interrupt

	//TIFR0
	//Interrupt Flags for TIMSK1 enabled Bits

	//Counter
	TCNT1 = 0x00;

	//OutputCompareRegister (PWM Rate)
	OCR1A = 0b11110000; //PB1 R
	OCR1B = 0b11111111; //PB2 G
	
	
	//PWM
	//TCCR2A
	TCCR2A &= ~ (1<<COM2A1);
	TCCR2A &= ~ (1<<COM2A0);
	TCCR2A |= (1<<COM2B1);
	TCCR2A &= ~ (1<<COM2B0);
	TCCR2A |= (1<<WGM20);
	TCCR2A |= (1<<WGM21);

	//TCCR2B
	TCCR2B &= ~ (1<<FOC2A);
	TCCR2B &= ~ (1<<FOC2B);
	TCCR2B &= ~ (1<<WGM22);
	TCCR2B &= ~ (1<<CS22);  //011 = 32
	TCCR2B &= ~ (1<<CS21); //100 = 64
	TCCR2B |= (1<<CS20); //001 = 1

	//TIMSK2
	TIMSK2 &= ~ (1<<OCIE2B); //B Match Interrupt
	TIMSK2 &= ~ (1<<OCIE2A); //A Match Interrupt
	TIMSK2 &= ~ (1<<TOIE2);  //Overflow Interrupt

	//TIFR0
	//Interrupt Flags for TIMSK2 enabled Bits

	//Counter
	TCNT2 = 0x00;

	//OutputCompareRegister (PWM Rate)
	OCR2A = 0x00; //PB3
	OCR2B = 0x00; //PD3
	
	
	OCR2B = 0b00000000; //PD3 B
	
	while(1)
	{
			if(OCR1A>= 0b11111111)
			{
				OCR1A=0;
				OCR1B=0b11111111;	
			}
			OCR1A++;
			OCR1B--;
			
			if(OCR1A>= 0b10000000)
			{
				OCR2B=0;
			}
			OCR2B++;
			
			_delay_ms(1);
	}
	
}

//int main(void)
//{
//	//Init
//	init();
//	
//	//LED
//	DDRB |= (1<<DDB1);
//	DDRD = 0xFF;
//	DDRD &= ~(1<<DDB0); 
//	PORTD = 0x00;
//   
//	//Variables   
//	uint8_t lMode = 1;
//	
//	uint8_t	SoundIn = 0x00;
//	uint8_t SoundBufferNext = 0;
//	uint8_t SoundBuffer[BufferSize];
//	uint8_t SoundMean = 0;
//	uint8_t SoundMeanHighThreshold;
//	uint8_t SoundMeanLowThreshold;
//	
//	uint8_t PotiLowThr = LightOut;
//	uint8_t PotiHighThr = LightOut;
//	uint8_t PotiR = 0;
//	uint8_t PotiG = 0;
//	uint8_t PotiB = 0;
//	
//	uint8_t ValueR = 0;
//	uint8_t ValueG = 0;
//	uint8_t ValueB = 255;
//	
//	bool RUp = 1;
//	bool GUp = 0;
//	bool BUp = 0;
//	
//	bool RDown = 0;
//	bool GDown = 0;
//	bool BDown = 1;
//	
//	//Code   
//	while (1)
//	{   
//		//Mode
///*		if(PIND & (1<<PIND2))
//		{
//			//PCINT8
//			lMode++;
//			if(lMode >= 5)
//			{
//				lMode = 0;
//			}
//			while(PIND & (1<<PINB1))
//			{
//				
//			}
//		}
//*/
//		
//		//Sound-to-Light
//		if(lMode == 0)
//		{
//			SoundIn = readADC(5);
//			SoundMean = SoundMean/SoundBuffer[SoundBufferNext];			
//			SoundBuffer[SoundBufferNext] = SoundIn;
//			SoundMean = SoundMean * SoundBuffer[SoundBufferNext];
//			SoundBufferNext++;			
//			if(SoundBufferNext == BufferSize)
//			{
//				SoundBufferNext = 0;
//			}
//			
//			//High
//			SoundMeanHighThreshold = SoundMean + LightHighThreshold;
//			if(SoundMeanHighThreshold>0b1111111111)SoundMeanHighThreshold=0b1111111111;
//			if(SoundIn >= SoundMeanHighThreshold)
//			{
//				OCR0A = LightFull;
//			}
//			else
//			{
//				OCR0A = OCR0A - LightFadeOut;
//			}
//			
//			//Low
//			SoundMeanLowThreshold = SoundMean + LightLowThreshold;
//			if(SoundMeanLowThreshold<0b0)SoundMeanLowThreshold=0b0;
//			if(SoundIn >= SoundMeanLowThreshold)
//			{
//				OCR0B = SoundIn;
//			}
//			else
//			{
//				OCR0B = OCR0B - LightFadeOut;
//			}
//		}
//		
//		//Poti-Fade RGB-LED
//		else if(lMode == 1)
//		{
//			PotiR = readADC(2);
//			PotiG = readADC(3);
//			PotiB = readADC(4);
//			
//			//OCR1A = PotiR; // R!
//			OCR1A = 0xFF;
//			//OCR1B = PotiG; // B?
//			OCR1B = 0x00;
//			//OCR2B = PotiB; // Leitung G -> B
//			OCR2B = 0xFF;
//						
//			_delay_ms(20);
//		}
//		
//		//Blink slow
//		else if(lMode == 2)
//		{
//			OCR0A = LightOut;
//			OCR0B = LightOut;
//			_delay_ms(250);
//			OCR0A = LightMid;
//			_delay_ms(250);
//			OCR0B = LightFull;
//			_delay_ms(250);
//			OCR0A = LightFull;
//			_delay_ms(250);
//			OCR0B = LightMid;
//			_delay_ms(250);
//		}
//		
//		//Blink fast
//		else if(lMode == 3)
//		{
//			OCR0A = LightOut;
//			OCR0B = LightOut;
//			_delay_ms(50);
//			OCR0A = 0x20;
//			_delay_ms(50);
//			OCR0B = LightFull;
//			_delay_ms(50);
//			OCR0A = 0x40;
//			_delay_ms(50);
//			OCR0B = 0xDF;
//			_delay_ms(50);
//			OCR0A = 0x60;
//			_delay_ms(50);
//			OCR0B = 0xBF;
//			_delay_ms(50);
//			OCR0A = 0x80;
//			_delay_ms(50);
//			OCR0B = LightMid;
//			_delay_ms(50);
//			OCR0A = 0xA0;
//			_delay_ms(50);
//			OCR0B = LightMid;
//			_delay_ms(50);
//			OCR0A = 0xC0;
//			_delay_ms(50);
//			OCR0B = 0x5F;
//			_delay_ms(50);
//			OCR0A = 0xE0;
//			_delay_ms(50);
//			OCR0B = 0x3F;
//			_delay_ms(50);
//			OCR0A = LightFull;
//			_delay_ms(50);
//			OCR0B = 0x1F;
//			_delay_ms(50);
//			
//		}
//		
//		//RGB Sweep
//		else if(lMode == 4)
//		{
//			if(RUp)
//			{
//				ValueR++;
//				if(ValueR>=255)
//				{
//					ValueR = 255;
//					GUp = true;
//					RUp = false;
//					BDown = true;
//				}
//			}
//			
//			if(GUp)
//			{
//				ValueG++;
//				if(ValueG>=255)
//				{
//					ValueG = 255;
//					BUp = true;
//					GUp = false;
//					RDown = true;
//				}
//			}
//			
//			if(BUp)
//			{
//				ValueB++;
//				if(ValueB>=255)
//				{
//					ValueB = 255;
//					RUp = true;
//					BUp = false;
//					GDown = true;
//				}
//			}
//			
//			if(RDown)
//			{
//				ValueR--;
//				if(ValueR<=0)
//				{
//					ValueR=0;
//					RDown = false;
//					GDown = true;
//				}
//			}
//			if(GDown)
//			{
//				ValueG--;
//				if(ValueG<=0)
//				{
//					ValueG=0;
//					GDown = false;
//					BDown = true;
//				}
//			}
//			
//			if(BDown)
//			{
//				ValueB--;
//				if(ValueB<=0)
//				{
//					ValueB=0;
//					BDown = false;
//					RDown = true;
//				}
//			}
//			
//			
//			OCR1A = ValueR;
//			OCR1B = ValueG;
//			OCR2B = ValueB;
//			
//			_delay_ms(10);
//		}
//				
//		//Off
//		else
//		{
//			_delay_ms(250);
//		}
//
//	}		
//}

//Pin-change Interrupt for Mode Switch
