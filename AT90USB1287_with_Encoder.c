//avrdude -c usbasp -p usb1287 -P usb -U flash:w:AT90USB1287_with_Encoder.hex
//PC6	OC.3A
//PC5	OC.3B
//PC4	OC.3C
/*
16000000/1024=15625Гц
1/15625=0,000064сек
16000000/256=62500Гц
1/62500=0,000016сек
16000000/64=250000Гц
1/250000=0,000004сек
1/2000=0,0005сек  -  2кГц
0,0005/0,000004=125тактов
*/


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "Encoder.h"

#define		MAX_VALUE	0x28
#define 	ZERO_VALUE	0x00
#define		MIN_VALUE	0x00


ISR(INT0_vect)	{
	TCCR3B	|=	_BV(CS31)|_BV(CS30);
	PORTA=~PORTA;	
}

ISR(TIMER3_COMPA_vect)	{
	ENCODER_Poll(MIN_VALUE, MAX_VALUE);
	OCR3BL = EncoderData*3;
}


int main (void)	{
	DDRA=0xFF;
	PORTA=0x00;
	DDRB=0xFF;
	PORTB=0x00;
	DDRC=0x70;
	PORTC=0x00;
	DDRD=0x00;
	PORTD=0x00;
	DDRE=0x00;
	PORTE=0x00;
	DDRF=0x00;
	PORTF=0x00;

	ENCODER_Init();
	ENCODER_Button();
	
	EncoderData = ZERO_VALUE;
	
	TCCR3A	|=	_BV(COM3B1)|_BV(WGM31)|_BV(WGM30);
	TCCR3B	|=	_BV(WGM33)|_BV(WGM32);
	TCCR3C	=	0x00;
	TCNT3H	=	0x00;
	TCNT3L	=	0x00;
	ICR3H	=	0x00;
	ICR3L	=	0x00;
	OCR3AH	=	0x00;
	OCR3AL	=	0x7D;
	OCR3BH	=	0x00;
	OCR3BL	=	EncoderData;
	OCR3CH	=	0x00;
	OCR3CL	=	0x00;
	TIMSK3	|=	_BV(OCIE3A);

	while (1)	{
		
	}
}
