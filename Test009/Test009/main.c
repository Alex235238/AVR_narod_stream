#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
//覧覧覧覧覧覧
#define e1 PORTD |= 0b00001000; // ���瑙�粲� �竟韋 E � 1
#define e0 PORTD &= 0b11110111; // ���瑙�粲� �竟韋 E � 0
#define rs1 PORTD |= 0b00000100; // ���瑙�粲� �竟韋 RS � 1 (萵����)
#define rs0 PORTD &= 0b11111011; // ���瑙�粲� �竟韋 RS � 0 (���瑙萵)
//覧覧覧覧覧覧


//覧覧覧覧覧覧
void port_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
}
//覧覧覧覧覧覧�

//覧覧覧覧覧覧�
void sendhalfbyte(unsigned char c)
{
	c<<=4;
	e1;   //粲���瑯� �竟�� ﾅ
	_delay_us(50);
	PORTD &= 0b00001111; //��頏瑯� 竟����璋�� �� 糢�萵� DB4-DB7, ���琿���� �� ���聰褌
	PORTD |= c;
	e0; //糺����瑯� �竟�� ﾅ
	_delay_us(50);
}
//覧覧覧覧覧覧�

//覧覧覧覧覧覧�-

void sendbyte(unsigned char c, unsigned char mode)
{
	  if (mode==0) {
		rs0;
	  }
	  else {
		rs1;
	  }
	  unsigned char hc=0;
	  hc=c>>4;
	  sendhalfbyte(hc); sendhalfbyte(c);
}
//覧覧覧覧覧覧�-

//覧覧覧覧覧覧�-
void sendchar(unsigned char c)
{
	sendbyte(c,1);
}
//覧覧覧覧覧覧�-


//覧覧覧覧覧覧�-
void setpos(unsigned char x, unsigned y)
{
  char adress;
  adress=(0x40*y+x)|0b10000000;
  sendbyte(adress, 0);
}
//覧覧覧覧覧覧�-

//覧覧覧覧覧覧�-
void LCD_ini(void)
{
	_delay_us(15);
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000, 0); //4礪�-�褂韲 (DL=0) � 2 �竟韋 (N=1)
	_delay_ms(1);
	sendbyte(0b00001100, 0); //粲���瑯� 韈�碣琥褊韃 �� 蒻���裹 (D=1), ������� �韭瑕韃 �� 粲���瑯� (C=0, B=0)
	_delay_ms(1);
	sendbyte(0b00000110, 0); //������ (���� �� � �瑰 � �裘鞴韲��) 碯蒟� 葢鞳瑣��� 粱裘�
	_delay_ms(1);
}
//覧覧覧覧覧覧�-

//覧覧覧覧覧覧�-

void str_lcd(char str1[])
{
	char n;
	for(n=0;str1[n]!='\0';n++){
		sendchar(str1[n]);
	}
}
//覧覧覧覧覧覧�-

int main(void)
{
	port_ini();
	LCD_ini();
	setpos(0,0);
	str_lcd("Hello World!");
	setpos(2,1);
	str_lcd("String 2");
    while (1) 
    {
		
    }
}

