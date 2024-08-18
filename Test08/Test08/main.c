#define F_CPU 8000000L
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
//-------------------------------
unsigned int i;
unsigned int R1 = 0, R2 = 0;

//-------------------------------
void segchar(unsigned char seg)
{
	switch(seg)
	{
		case 1: PORTD = 0b11111001; break;
		case 2: PORTD = 0b10100100; break;
		case 3: PORTD = 0b10110000; break;
		case 4: PORTD = 0b10011001; break;
		case 5: PORTD = 0b10010010; break;
		case 6: PORTD = 0b10000010; break;
		case 7: PORTD = 0b11111000; break;
		case 8: PORTD = 0b10000000; break;
		case 9: PORTD = 0b10010000; break;
		case 0: PORTD = 0b11000000; break;
	}
}

//-------------------------------
void timer_ini(void)
{
	TCCR1B |= (1<<WGM12);
	TIMSK |= (1<<OCIE1A);
	OCR1AH = 0b01111010;	//записываем в регистр число для сравнения
	OCR1AL = 0b00010010;
	TCCR1B |= (1<<CS11);	//установим делитель.
}
//-------------------------------
unsigned char n_count = 0;
//-------------------------------
ISR (TIMER1_COMPA_vect)
{
	if(n_count == 0){PORTB&=~(1<<0); PORTB|=(1<<1); segchar(R1);}
	if(n_count == 1){PORTB&=~(1<<1); PORTB|=(1<<0); segchar(R2);}
	n_count++;
	if(n_count>1) n_count = 0;
}

//-------------------------------
void ledprint (unsigned int number)
{
	R1 = number % 10;
	R2 = number / 10;
}

int main(void)
{
	unsigned char butcount=0, butstate=0;
	timer_ini();
	DDRD = 0xFF;
	DDRB = 0b00001111;
	PORTD = 0b11111111;
	PORTB = 0b00100000;
	i=0;
	sei();
	ledprint(97);
	while(1)
	{
		for(i=0;i<100;i++)
		{
			while (butstate==0)
			{
				if (!(PINB&0b00100000))
				{
					if(butcount < 5)
					{
						butcount++;
					}
					else
					{
						i=0;
						butstate=1;
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
						butstate=1;
					}
				}
			}
			ledprint(i);
			_delay_ms(500);
			butstate=0;
		}
	}
	
}