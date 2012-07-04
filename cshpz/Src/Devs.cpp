#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"
#include <avr/delay.h>
#include "Nls.h"



#define NUM_OF_DEVS_CENTER 11
#define NUM_OF_DEVS_02 1
//#define NUM_OF_DEVS_3 1
//#define NUM_OF_DEVS_6 15
//#define NUM_OF_DEVS_9 15
//#define NUM_OF_DEVS_11 10
//#define NUM_OF_DEVS_14 15
//#define NUM_OF_DEVS_16 15
//#define NUM_OF_DEVS_18 15
//#define NUM_OF_DEVS_20 15
//#define NUM_OF_DEVS_21 11

extern NET_OUTPUT_STRUCT1 data_from_slave18;
extern NET_INPUT_STRUCT1 data_for_slave18;
//typedef char PROGMEM prog_char_moe;
extern const prog_char dev_name_str[][5] PROGMEM;
#define MSK_NUMER_MOE 2

extern uint8_t scafe_net;


//KOG( *name, *mn_os, enh_info,	*out, *press, *os, *mp, *ktr)
//-------------------------------------------------------------------------------------------YA6
VZK GR3						//клас місцевих пристроїв
	(dev_name_str[0],		//назва яка буде відображитися на LCD
	(uint8_t*)&mGR1,		                //свытлодіод мнемосхеми
	VZK_CHECK_OS,			//статус
	&OP_GR1,              		//вихід МТ
	0,						//контроль стану перепаду тиску
	0,				        //контроль стану зворотній зв'язок
	0,						//контроль стану магнітного пускача
	0);						//контроль стану теплового реле


//extern const prog_char dev_name_str[][5] PROGMEM;
const prog_char dev_name_str[][5]=
{
	"Гр1",
	"Гр22",
};



#define NUM_OF_DEV_SET 1
int16_t dev_set_iic_copy[NUM_OF_DEV_SET];
Set Dev_set[NUM_OF_DEV_SET];
extern const prog_char dev_set_name_str[NUM_OF_DEV_SET][17] PROGMEM;
const prog_char dev_set_name_str[NUM_OF_DEV_SET][17]=
{
	"Т ожид давления",
};

extern void WriteSetIIC(uint16_t _value, uint16_t _adr);
extern uint16_t ReadSetIIC(uint16_t _adr);
extern uint16_t net_fl;
void Dev_init()
{
    uint8_t i;

	SET_SET(Dev_set[0],dev_set_name_str[0],30,0,1000,0)

	//считывание уставок из памяти
	if(!(tech_fl&DEFAULT_SET))//считывание уставок из флэши
	{
		for(i=0;i<NUM_OF_DEV_SET;i++)
		{
			Dev_set[i].value=ReadSetIIC(0x200+i*2);
			dev_set_iic_copy[i]=Dev_set[i].value;
		}
	}
	else //запись заводских уставок во флэш
	{
		for(i=0;i<NUM_OF_DEV_SET;i++)
		{
			WriteSetIIC(Dev_set[i].value,0x200+i*2);
			dev_set_iic_copy[i]=Dev_set[i].value;
			_delay_ms(10);
		}
	}
}
#include "Etaz.h"
//extern uint8_t NetPackInfo[NUM_OF_SCAF];
//uint8_t array_of_net_on [NUM_OF_SCAF];
void Dev_drv()
{
	uint8_t i;
	//GR2.show_lcd();

//	for(i=0;i<NUM_OF_DEVS_CENTER;i++)
//	{
//		pDevs_arr_Center[i]->drv();
//		pDevs_arr_Center[i]->show_mnem();
//	}

	for(i=0;i<NUM_OF_DEVS_02;i++)
	{
		pDevs_arr_02[i]->drv();
		pDevs_arr_02[i]->show_mnem();
	}

//	for(i=0;i<NUM_OF_DEVS_3;i++)
//	{
//		pDevs_arr_3[i]->drv();
//		pDevs_arr_3[i]->show_mnem();
//	}
//
//	for(i=0;i<NUM_OF_DEVS_6;i++)
//	{
//		pDevs_arr_6[i]->drv();
//		pDevs_arr_6[i]->show_mnem();
//	}
//
//    for(i=0;i<NUM_OF_DEVS_9;i++)
//	{
//		pDevs_arr_9[i]->drv();
//		pDevs_arr_9[i]->show_mnem();
//	}
//
//    for(i=0;i<NUM_OF_DEVS_11;i++)
//	{
//		pDevs_arr_11[i]->drv();
//		pDevs_arr_11[i]->show_mnem();
//	}
//
//    for(i=0;i<NUM_OF_DEVS_14;i++)
//	{
//		pDevs_arr_14[i]->drv();
//		pDevs_arr_14[i]->show_mnem();
//	}
//
//
//	for(i=0;i<NUM_OF_DEVS_16;i++)
//	{
//		pDevs_arr_16[i]->drv();
//		pDevs_arr_16[i]->show_mnem();
//	}
//
//	for(i=0;i<NUM_OF_DEVS_18;i++)
//	{
//		pDevs_arr_18[i]->drv();
//		pDevs_arr_18[i]->show_mnem();
//	}
//
//    for(i=0;i<NUM_OF_DEVS_20;i++)
//	{
//		pDevs_arr_20[i]->drv();
//		pDevs_arr_20[i]->show_mnem();
//	}
//
//    for(i=0;i<NUM_OF_DEVS_21;i++)
//	{
//		pDevs_arr_21[i]->drv();
//		pDevs_arr_21[i]->show_mnem();
//	}

//	for(i=0;i<NUM_OF_DEVS_2;i++)
//	{
//		pDevs_arr_2[i]->drv();
//		pDevs_arr_2[i]->show_mnem();
//	}

}


extern const prog_char strNoDevs[] PROGMEM;
const prog_char strNoDevs[]="No devs";

//uint8_t _cur_dev_center;
//void show_devs_center()
//{
//	_cur_dev_center=getpm(_cur_dev_center,NUM_OF_DEVS_CENTER);
//	pDevs_arr_Center[_cur_dev_center]->show_lcd();
//}

uint8_t _cur_dev_02;
void show_devs_02()
{
	_cur_dev_02=getpm(_cur_dev_02,NUM_OF_DEVS_02);
	pDevs_arr_02[_cur_dev_02]->show_lcd();
}

//uint8_t _cur_dev_3;
//void show_devs_3()
//{
//	_cur_dev_3=getpm(_cur_dev_3,NUM_OF_DEVS_3);
//	pDevs_arr_3[_cur_dev_3]->show_lcd();
////    _cur_dev_02=getpm(_cur_dev_02,NUM_OF_DEVS_02);
////	pDevs_arr_02[_cur_dev_02]->show_lcd();
//    //LCD_abc((char*)strNoDevs,21);//17
//}
//uint8_t _cur_dev_6;
//void show_devs_6()
//{
//	_cur_dev_6=getpm(_cur_dev_6,NUM_OF_DEVS_6);
//	pDevs_arr_6[_cur_dev_6]->show_lcd();
//}
//uint8_t _cur_dev_9;
//void show_devs_9()
//{
//	_cur_dev_9=getpm(_cur_dev_9,NUM_OF_DEVS_9);
//	pDevs_arr_9[_cur_dev_9]->show_lcd();
//}
//uint8_t _cur_dev_11;
//void show_devs_11()
//{
//	_cur_dev_11=getpm(_cur_dev_11,NUM_OF_DEVS_11);
//	pDevs_arr_11[_cur_dev_11]->show_lcd();
//}
//uint8_t _cur_dev_14;
//void show_devs_14()
//{
//	_cur_dev_14=getpm(_cur_dev_14,NUM_OF_DEVS_14);
//	pDevs_arr_14[_cur_dev_14]->show_lcd();
//}
//uint8_t _cur_dev_16;
//void show_devs_16()
//{
//	_cur_dev_16=getpm(_cur_dev_16,NUM_OF_DEVS_16);
//	pDevs_arr_16[_cur_dev_16]->show_lcd();
//}
//uint8_t _cur_dev_18;
//void show_devs_18()
//{
//	_cur_dev_18=getpm(_cur_dev_18,NUM_OF_DEVS_18);
//	pDevs_arr_18[_cur_dev_18]->show_lcd();
//}
//
//uint8_t _cur_dev_20;
//void show_devs_20()
//{
//	_cur_dev_20=getpm(_cur_dev_20,NUM_OF_DEVS_20);
//	pDevs_arr_20[_cur_dev_20]->show_lcd();
//}
//
//uint8_t _cur_dev_21;
//void show_devs_21()
//{
//	_cur_dev_21=getpm(_cur_dev_21,NUM_OF_DEVS_21);
//	pDevs_arr_21[_cur_dev_21]->show_lcd();
//}


uint8_t _cur_dev_set;
void show_dev_set()
{
	_cur_dev_set=getpm(_cur_dev_set,NUM_OF_DEV_SET);
	LCD_abc((char*)dev_set_name_str[_cur_dev_set],0);
	LCD_float(Dev_set[_cur_dev_set].value,Dev_set[_cur_dev_set].dot,20);//16
	getpm_dig(&Dev_set[_cur_dev_set].value,Dev_set[_cur_dev_set].dot,
				Dev_set[_cur_dev_set].min_value,Dev_set[_cur_dev_set].max_value);

	if(!(tech_fl&IIC_BUSY))
	if(dev_set_iic_copy[_cur_dev_set]!=Dev_set[_cur_dev_set].value)
	{//запись в ИИС обновленного параметра
		tech_fl|=IIC_BUSY;
		WriteSetIIC(Dev_set[_cur_dev_set].value,0x200+_cur_dev_set*2);
		dev_set_iic_copy[_cur_dev_set]=Dev_set[_cur_dev_set].value;
	}
}

    const prog_char stad_str[4][3]=
	{
		"OP",
		"CL",
		"ST",
		"ER"
	};

    const prog_char mode_str[3][5]=
	{
		"АВТО",
		"ОПЕР",
		"ДИСТ"
	};

    const prog_char error_str[]         = "Ош:";
	const prog_char press_err_str[]     = "тиск";
	const prog_char mp_err_str[]        = "МП";
	const prog_char ktr_err_str[]       = "КТР";
	const prog_char os_err_str[]        = "ОС";
	const prog_char stan_err_str[]      = "CТАН";
	const prog_char auto_str[]          = "АВТО";
	const prog_char dist_str[]          = "ДИСТ";
	const prog_char oper_str[]          = "ОПЕР";
	const prog_char vidk_str[]          = "Вiдк";
	const prog_char zakr_str[]          = "Закр";

