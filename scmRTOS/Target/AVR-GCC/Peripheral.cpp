#include <avr/io.h>
#include <avr/delay.h>
#include "Peripheral.h"
//#include "../Src/Sgwork.h"

uint8_t KEY[2]; //отфильтрованое состояние кнопок пульта
uint8_t MT[2];//выдача на МТ
uint8_t MSK[8];//отфильтрованное значение МСК
uint8_t MSK_FLT_TMP[64];//фильтр МСК
uint8_t OS_MT[2];//прием ОС

//uint8_t Test_MSK,TestMSKResult;

#define CDC3 128//PORTD.7
#define CDC2 64//PORTD.6
#define CDC1 32//PORTD.5
#define CDC0 16//PORTD.4
void set_data_low(uint8_t data, uint8_t adr)//запись данных через ALS138D
{
	PORTD|=CDC3;
	DDRA=0xff;
	PORTA=~data;//выдача данных в порт
	PORTD&=~(CDC0|CDC1|CDC2);//сброс всех бит адреса
	PORTD|=(adr<<4);//Установка адреса на ALS138D
	PORTD&=~CDC3;//включение защелки
	asm("nop");
	PORTD|=CDC3;//выключение защелки
	DDRA=0x00;
	PORTA=0xff;
}
uint8_t read_data_low(uint8_t adr)//чтение данных через ALS138D
{
	PORTD|=CDC3;
	DDRA=0x00;
	PORTA=0xff;
	uint8_t temp;
	PORTD&=~(CDC0|CDC1|CDC2);//сброс всех бит адреса
	PORTD|=(adr<<4);//Установка адреса на ALS138D
	PORTD&=~CDC3;//включение защелки
	asm("nop");
	temp=PINA;//чтение данных из порта
	PORTD|=CDC3;//выключение защелки
	return ~temp;
}

#define CS0 0
#define CS1 1
#define CS2 2
#define CS3 3
#define CS4 4
#define CS5 5
uint8_t cur_msk_selector;// выбор текущего столбца МСК
//extern uint8_t TestMsk;
void low_drv()
{
	uint8_t i,temp;
	DDRE|=0x10;
	PORTE&=~0x10;
	set_data_low(MT[0],CS0);//выдача МТ[0]
	OS_MT[0]=read_data_low(CS1);//чтение ОС[0]
	set_data_low(MT[1],CS2);//выдача МТ[1]
	OS_MT[1]=read_data_low(CS3);//чтение ОС[1]

//	MSK[cur_msk_selector]=read_data_low(CS5);//считывание текущего МСК
	temp=read_data_low(CS5);//считывание текущего МСК, затем фильтрация
	//TestMSK=temp;
#if 1
	//побитная фильтрация МСК
	for(i=0;i<8;i++)
	{
		if(temp&(1<<i)) //МСК не нажат
		{
			if(!(MSK[cur_msk_selector]&(1<<i))) //при ненажатом МСК отфильтрованом
			{
				MSK_FLT_TMP[cur_msk_selector*8+i]=0;
			}
			else //отфильтрованый МСК был нажат
			{
				MSK_FLT_TMP[cur_msk_selector*8+i]++;
				if(MSK_FLT_TMP[cur_msk_selector*8+i]>MSK_FLT)//если истекло время фильтрации
				{
					MSK[cur_msk_selector]&=~(1<<i);//отпустить МСК
					MSK_FLT_TMP[cur_msk_selector*8+i]=0;//очистить фильтр
				}
			}
		}
		else //если МСК нажат
		{
			if(!(MSK[cur_msk_selector]&(1<<i))) //при ненажатом МСК отфильтрованом
			{
				MSK_FLT_TMP[cur_msk_selector*8+i]++;
				if(MSK_FLT_TMP[cur_msk_selector*8+i]>MSK_FLT)//если истекло время фильтрации
				{
					MSK[cur_msk_selector]|=(1<<i);//отпустить МСК
					//tech_fl|=SOUND_KEY;
					MSK_FLT_TMP[cur_msk_selector*8+i]=0;//очистить фильтр
				}
			}
			else //отфильтрованая кнопка не была нажата
			{
				MSK_FLT_TMP[cur_msk_selector*8+i]=0;
			}
		}
	}
#endif
//	TestMSK=0x00;
//	switch (cur_msk_selector)
//	{
//		case 0:
//			TestMSK=0x01;
//		break;
//		case 1:
//			TestMSK=0x04;
//		break;
//		case 2:
//			TestMSK=0x10;
//		break;
//		case 3:
//			TestMSK=0x40;
//		break;
//		case 4:
//			TestMSK=0x02;
//		break;
//		case 5:
//			TestMSK=0x08;
//		break;
//		case 6:
//			TestMSK=0x20;
//		break;
//		case 7:
//			TestMSK=0x80;
//		break;
//	}
	//if (cur_msk_selector%2) {
	//	TestMSK|=(1<<(cur_msk_selector%2+4));
	//}
	//else {
	//	TestMSK|=(1<<(cur_msk_selector/2));
	//}
//	if (TestMSK==temp) TestMSKResult|=(1<<cur_msk_selector); else TestMSKResult&=~(1<<cur_msk_selector);
	////for (i=0;i<8;i++) {
	////	if (cur_msk_selector%2) {
	//		TestMsk|=(1<<())
	//	}
	//	else {
	//
	//	}
	//}

	cur_msk_selector++;//инкремент текущего МСК

	if(cur_msk_selector>7)
	{
		cur_msk_selector=0;         // Условие обнуления счетчика выбора МСК.
	}
	set_data_low(1<<cur_msk_selector,CS4);//засвечивание следующего столбца МСК
}

void low_init()
{
	DDRE|=0x10;//живлення для регістрів ввода/вивода
	PORTE&=~0x10;
	set_data_low(0x00,CS0);//выдача МТ[0]
	set_data_low(0x00,CS2);//выдача МТ[1]
}

