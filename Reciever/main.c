/*
 * SPI-ATmega to ATmega(Reciv).c
 *
 * Created: 7/24/2016 3:32:10 PM
 * Author : Dell
 */ 

#include <avr/io.h>
#include "Init.h"
#include "lcd.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL

#define sbit(reg,bit)	reg |= (1<<bit)
#define cbit(reg,bit)	reg &= ~(1<<bit)



unsigned char spi_tranceiver(unsigned char );

int main(void)
{
   pins_init();
   lcd_init();
	uint8_t recieved_data;
    uint8_t transmitting_data;
	
	int j=1;
	
	uint8_t a[8]={'a','b','c','d','e','f','g','h'};
	
	PORTC=0xFF;
	
    while (1) 
    {
		for(int k=0;k<8;k++)
		{
		transmitting_data = a[k];
		
			
		recieved_data= spi_tranceiver(transmitting_data);
		
		PORTC = recieved_data;
		
		
	//	for(int k=0 ; k<8; k++){
			if ((recieved_data&(1<<k))==0)
			{lcd_cursor(1,k+1);
				lcd_wr_char('0');
			}
			else
			{lcd_cursor(1,k+1);
				lcd_wr_char('1');
			}
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
