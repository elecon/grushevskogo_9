#include "Iic.h"
#include <avr/delay.h>
#define SDA 1
#define SCL 0
#define SDA_1 DDRD&=~(1<<SDA)
#define SDA_0 DDRD|=1<<SDA
#define SCL_1 DDRD&=~(1<<SCL)
#define SCL_0 DDRD|=1<<SCL
void Init_iic()
{
	DDRD&=~((1<<SCL)|(1<<SDA));
	PORTD&=~((1<<SCL)|(1<<SDA));
}

void Start_iic()
{
	SDA_1;
	SCL_1;
	_delay_us(5);
	SDA_0;
	_delay_us(5);
	SCL_0;
	_delay_us(5);
}

void Stop_iic()
{
	SCL_0;
	SDA_0;
	_delay_us(5);	
	SCL_1;
	_delay_us(5);
	SDA_1;
	_delay_us(5);
}

uint8_t Tr_iic_byte(uint8_t _byte)
{
	int8_t _bit_counter;
	for(_bit_counter = 7; _bit_counter >= 0; _bit_counter--)
	{
		if(_byte&(1<<_bit_counter))
		{
			SDA_1;
		}
		else
		{
			SDA_0;
		}
		SCL_1;
		_delay_us(5);
		SCL_0;
		_delay_us(5);
	}
	SDA_1;
	SCL_1;
	_delay_us(5);
	_bit_counter = PIND&(1<<SDA);
	SCL_0;
	_delay_us(5);
	if(_bit_counter) return 0; // no acknowledge
	return 1; // ok acknowledge
}

uint8_t Rd_iic_byte(uint8_t _mode)// mode=0 last byte mode=1 not last byte
{
	int8_t _bit_counter;
	uint8_t _byte=0;
	SCL_0;
	SDA_1;
	for(_bit_counter = 7; _bit_counter >= 0; _bit_counter--)
	{
		SCL_1;
		_delay_us(5);
		if(PIND&(1<<SDA))
		{
			_byte|=1<<_bit_counter;
		}
		SCL_0;
		_delay_us(5);
	}
	if(_mode)
	{
		SDA_0;
	}
	else
	{
		SDA_1;
	}
		SCL_1;
	_delay_us(5);
	SCL_0;
	_delay_us(5);
	return _byte;
}

void WriteSetIIC(uint16_t _value, uint16_t _adr)
{
	Start_iic();
	Tr_iic_byte(0xA2);//10100010 select iic write
	Tr_iic_byte((uint8_t)(_adr>>8));//first addr
	Tr_iic_byte((uint8_t)_adr);//second addr
	Tr_iic_byte((uint8_t)(_value>>8));
	Tr_iic_byte((uint8_t)_value);
	Stop_iic();
}

uint16_t ReadSetIIC(uint16_t _adr)
{
	uint16_t _temp;
	Start_iic();
	Tr_iic_byte(0xA2);//10100010 select iic write
	Tr_iic_byte((uint8_t)(_adr>>8));//first addr
	Tr_iic_byte((uint8_t)_adr);//second addr
	Start_iic();
	Tr_iic_byte(0xA3);
	_temp=Rd_iic_byte(1)*0x100;
	_temp+=Rd_iic_byte(0);
	Stop_iic();
	return _temp;
}

