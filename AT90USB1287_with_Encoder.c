//avrdude -c usbasp -p usb1287 -P usb -U flash:w:AT90USB1287_with_Encoder.hex

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "Encoder.h"

ISR(INT0_vect)	{
	PORTA=~PORTA;
}

int main (void)	{
	DDRA=0xFF;
	PORTA=0x00;
	DDRB=0xFF;
	PORTB=0x00;
	DDRC=0x00;
	PORTC=0x00;
	DDRD=0x00;
	PORTD=0x00;
	DDRE=0x00;
	PORTE=0x00;
	DDRF=0x00;
	PORTF=0x00;

	ENCODER_Init();
	ENCODER_Button();
	
	EncoderData=0x40;
	uint8_t a=0x40;
		
	while (1)	{
		ENCODER_Poll(0x00,0x80);
		if(a<EncoderData)	{
			PORTB=~PORTB;
		}
		if(a>EncoderData)	{
			PORTB=~PORTB;
		}
		a=EncoderData;
	}
}
