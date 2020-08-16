/*
 * RFID.c
 *
 * Created: 7/9/2018 10:59:43 AM
 * Author : GNC
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <usart.h>
#include <util/delay.h>
void lcd_cmd(int);
void lcd_data(int);
void lcd_init(void);
void clrscr(void);
int compare(char*,int);
void lcd_num(int );
void lcd_string(char*);
int main(void)
{	
	DDRB=0xff;
	DDRD = 0xfe;
	usart_init();
	_delay_ms(10);
	lcd_init();
	_delay_ms(100);
	char bg[12];
	int a=0,b=0,c=0;//eeprom read
	int aa=0,bb=0,cc=0;
	int s,k;
    while (1) 
    {	
		_delay_ms(100);
		for(int i=0;i<12;i++)
		{
			char val=usart_rec();
			usart_send(val);
			bg[i]=val;
			 s=1;
		}
		bg[12]='\0';
		lcd_cmd(0x80);
		for (int j=0;j<=11;j++)
		{
			lcd_data(bg[j]);
			_delay_ms(10);
		}
		lcd_string("Attendance is being recorded");
		if(s==1)
		{
			 k=compare( bg,12);
			 clrscr();
			 lcd_cmd(0xc5);
			 lcd_num(k);
			 _delay_ms(1500);
			 if(k==1)
			 {
				 clrscr();
				 lcd_string("Welcome student A");
				 _delay_ms(1000);
				 if(aa!=1)
				 a=a+1;//eeprom
				 else
				 lcd_string("Your attendance is being recorded");
				 aa=1;
			 }
			 else if(k==2)
			{
			 	clrscr();
			 	lcd_string("Welcome student B");
			 	_delay_ms(1000);
				 if(bb!=1)
				 b=b+1;//eeprom
				 else
				 lcd_string("Your attendance is being recorded");
				 bb=1;
			}
		 	else if(k==3)
			{
				 clrscr();
				 lcd_string("Welcome student C");
				 _delay_ms(1000);
				 if(cc!=1)
				 c=c+1;//eeprom
				 else
				 lcd_string("Your attendance is being recorded");
				 cc=1;
			}
			else if(k==4)
			{
				clrscr();
				lcd_string("Welcome teacher");
				_delay_ms(1000);
				clrscr();
				lcd_string("Student A");
				lcd_cmd(0xc5);
				lcd_num(a);
				_delay_ms(2000);
				clrscr();
				lcd_string("Student B");
				lcd_cmd(0xc5);
				lcd_num(b);
				_delay_ms(2000);
				lcd_string("Student C");
				lcd_cmd(0xc5);
				lcd_num(c);
				_delay_ms(2000);
			}
		}
	}
}
int compare(char bg[],int n)
{
	char a[12]={'1','0','0','0','4','B','3','4','9','A','F','5'};//13466//k=1
	char b[12]={'1','0','0','0','4','B','9','4','9','E','5','1'};//38046//k=2
	char c[12]={'1','0','0','0','4','A','9','9','9','4','5','7'};//39316//k=3
	char d[12]={'1','0','0','0','4','A','E','E','3','F','8','B'};//60991//k=4
	if(a[10]==bg[10])
	return 1;
	if(b[10]==bg[10])
	return 2;
	if(c[10]==bg[10])
	return 3;
	if(d[10]==bg[10])
	return 4;
}
void lcd_num(int n)
{
	int i=0;
	lcd_cmd(0x04);
	if(n==0)
	lcd_data(48);
	else
	{
		while(n!=0)
		{
			i=n%10;
			lcd_data(48+i);
			n=n/10;
		}
	}
	lcd_cmd(0x06);
}
void lcd_cmd(int c)
{
	PORTB = (c&0xf0)+0x04;
	_delay_ms(1);
	PORTB =PORTB-0x04;
	PORTB=((c<<4)&0xf0)+0x04;
	_delay_ms(1);
	PORTB =PORTB-0x04;
}
void lcd_data(int d)
{
	PORTB = (d&0xf0)+0x05;
	_delay_ms(1);
	PORTB =PORTB-0x04;
	PORTB=((d<<4)&0xf0)+0x05;
	_delay_ms(1);
	PORTB =PORTB-0x04;
}
void clrscr(void)
{
	lcd_cmd(0x01);
	_delay_ms(5);
}
void lcd_init(void)
{
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0c);
	lcd_cmd(0x06);
}
void lcd_string(char*name)
{
	int k=0;
	int i=0;
	for(int m=0;name[m]!='\0';m++)
	{
		k=m;
	}
	_delay_ms(1000);
	
	for(int j=0;j<k+1;j=j+i)
	{
		int e = 0x80;
		for( i=0;i<32;i++)
		{
			lcd_cmd(e++);
			lcd_data(name[i+j]);
			_delay_ms(1);
			if(i==15)
			{e=0xc0;
			}
			if(i+j==k+1)
			break;
		}
		//clrscr();
	}
}
 

