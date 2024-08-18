#define F_CPU 8000000L
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

unsigned char i;

void timer_ini(void)
{
	TCCR1B |= (1<<WGM12);
	TIMSK |= (1<<OCIE1A);
	OCR1AH = 0b01111010;	//записываем в регистр число для сравнения
	OCR1AL = 0b00010010;
	TCCR1B |= (1<<CS12);	//установим делитель.
}

ISR (TIMER1_COMPA_vect)
{
	if(i > 9) i = 0;
	segchar(i);
	i++;
}

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

int main(void)
{
	DDRD = 0xFF;
	DDRB = 0x00;
	PORTD = 0b11111111;
	PORTB = 0b00000001;
	i=0;
	sei();
	while(1)
	{
		timer_ini();
	}
		
}