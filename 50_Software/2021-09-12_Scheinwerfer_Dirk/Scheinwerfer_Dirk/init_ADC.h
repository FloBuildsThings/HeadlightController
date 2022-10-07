/*
 * Scheinwerfer_Dirk.c
 *
 * Created: 03.07.2020 08:35:33
 * Author : flo97
 */ 

//Includes
#include <avr/io.h>
#include <stdbool.h>

//functions
bool init_ADC();

uint8_t readADC(uint8_t channel);