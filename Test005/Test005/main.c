#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//	unsigned char i;
	unsigned char butcount=0;
	DDRD = 0xFF;
	DDRB = 0x00;
	PORTD = 0b00000000;  // 1 2 3 4 5 6 7 8
	PORTB = 0b00000001; //0b|dp|g|f|e|d|c|b|a|
	while(1)
	{
		if (!(PINB&0b00000001))
		{
			if(butcount < 5) 
			{
				butcount++;
			}
			else
			{
				PORTD = ~0b00000110;
				_delay_ms(500);
				PORTD = ~0b01011011;
				_delay_ms(500);
				PORTD = ~0b01001111;
				_delay_ms(500);
				PORTD = ~0b01100110;
				_delay_ms(500);
				PORTD = ~0b01101101;
				_delay_ms(500);
				PORTD = ~0b01111101;
				_delay_ms(500);
				PORTD = ~0b00000111;
				_delay_ms(500);
				PORTD = ~0b01111111;
				_delay_ms(500);
				PORTD = ~0b01101111;
				_delay_ms(500);
				PORTD = ~0b00111111;
				_delay_ms(500);
			}
		}
		else
		{
			if(butcount > 0) 
			{
				butcount--;
			}
			else
			{
				PORTD = ~0b00000000;
			}
		}
	}
}