/*
 * SPI- ATmega16 to Atmega16.c
 *
 * Created: 7/24/2016 2:49:23 PM
 * Author : Dell
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include "Init.h"
#include <util/delay.h>
#include "lcd.h"
#include <string.h>
#include <avr/interrupt.h>

#define DataPort	PORTA	// Using PortC as our Dataport
#define DataDDR		DDRA

//Interrupt Service Routine for INT0


unsigned char spi_tranceiver(unsigned char );

int main(void)
{
	pins_init(); 
	lcd_init();   
	uint8_t recieved_data;
	uint8_t transmitted_data;
	uint8_t s;

char switches;
		 lcd_cursor(1,1);
	
	
    while (1) 
    { 
	for(int i=0;i<8;i++)
	{
	
	 switches=PINC;
	 transmitted_data = switches ;
	

	 recieved_data = spi_tranceiver(transmitted_data);
	 
	 lcd_cursor(1,1+i);
	 lcd_wr_char( recieved_data);
	 _delay_ms(1000);

	}
}

}



//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
	SPDR = data;                       //Load data into the buffer
	while(!(SPSR & (1<<SPIF) ));       //Wait until transmission complete
	return(SPDR);                      //Return received data
}

