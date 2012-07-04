#include "Pdz.h"
#include "Sgwork.h"
//#include "Main.h"
#include <avr/delay.h>

#define NUM_OF_PDZ 1
Pdz Pdz1;

Pdz *pPdz_arr[NUM_OF_PDZ]=
{
	&Pdz1
};

extern const prog_char pdz_name_str[NUM_OF_PDZ][6] PROGMEM;
const prog_char pdz_name_str[NUM_OF_PDZ][6]=
{
	"ПДЗ"
};

void Pdz::init()
{
	clear_t_stad();
	clear_t_sub_st();

}
void Pdz::to_stad(uint8_t _stad, uint8_t _sub_st)
{
	if(stad != _stad)
	{
		clear_t_stad();
		clear_t_sub_st();
		stad = _stad;
		//sub_st = 0;
	}
	if(sub_st != _sub_st)
	{
		clear_t_sub_st();
		sub_st = _sub_st;
	}
}
void Pdz::show_mnem()
{
	if(stad == PDZ_ST_WORK) *mn_os = 0xf0;
	else if(stad == PDZ_ST_STOP) *mn_os=0x33;
}
void Pdz::drv()
{
	(*pdrv)();
}
void Pdz::show_lcd()
{
	(*pshow_lcd)();
}
extern void Pdz1_drv();
extern void Pdz1_show_lcd();

#define NUM_OF_PDZ_SET 2
int16_t pdz_set_iic_copy[NUM_OF_PDZ_SET];
extern const prog_char pdz_set_name_str[NUM_OF_PDZ_SET][16] PROGMEM;
const prog_char pdz_set_name_str[NUM_OF_PDZ_SET][16]=
{
	"Разгон вент, с",
	"Блокировка вент"
};

extern void WriteSetIIC(uint16_t _value, uint16_t _adr);
extern uint16_t ReadSetIIC(uint16_t _adr);
Set Pdz_set[NUM_OF_PDZ_SET];
void Pdz_init()
{
	uint8_t i;
	for(i=0;i<NUM_OF_PDZ;i++)
	{
		pPdz_arr[i]->init();
	}

	Pdz1.name=pdz_name_str[0];
	Pdz1.pdrv=Pdz1_drv;
	Pdz1.pshow_lcd=Pdz1_show_lcd;
	//Pdz1.mn_os=&mtest;

	SET_SET(Pdz_set[0],pdz_set_name_str[0],2,0,100,0)
	SET_SET(Pdz_set[1],pdz_set_name_str[1],0,0,100,0)

	//считывание уставок из памяти
	if(!(tech_fl&DEFAULT_SET))//считывание уставок из флэши
	{
		for(i=0;i<NUM_OF_PDZ_SET;i++)
		{
			Pdz_set[i].value=ReadSetIIC(0x100+i*2);
			pdz_set_iic_copy[i]=Pdz_set[i].value;
		}
	}
	else //запись заводских уставок во флэш
	{
		for(i=0;i<NUM_OF_PDZ_SET;i++)
		{
			WriteSetIIC(Pdz_set[i].value,0x100+i*2);
			pdz_set_iic_copy[i]=Pdz_set[i].value;
			_delay_ms(10);
		}
	}
}
extern void set_reg_set();
extern uint16_t fire_fl;
void Pdz_drv()
{
	uint8_t i;
	for(i=0;i<NUM_OF_PDZ;i++)
	{
		if(!sec_tik) {pPdz_arr[i]->inc_t_stad();pPdz_arr[i]->inc_t_sub_st();}
		pPdz_arr[i]->drv();
		pPdz_arr[i]->show_mnem();
	}
}
uint8_t _cur_pdz;

void show_pdz()
{
//	LCD_uind(tech_fl,18,2|LEAD_ZERO);
	_cur_pdz=getpm(_cur_pdz,NUM_OF_PDZ);
	pPdz_arr[_cur_pdz]->show_lcd();
}

uint8_t _cur_pdz_set;
void show_pdz_set()
{
	_cur_pdz_set=getpm(_cur_pdz_set,NUM_OF_PDZ_SET);
	LCD_abc((char*)pdz_set_name_str[_cur_pdz_set],0);
	LCD_float(Pdz_set[_cur_pdz_set].value,Pdz_set[_cur_pdz_set].dot,20);//16
	getpm_dig(&Pdz_set[_cur_pdz_set].value,Pdz_set[_cur_pdz_set].dot,
				Pdz_set[_cur_pdz_set].min_value,Pdz_set[_cur_pdz_set].max_value);

	if(!(tech_fl&IIC_BUSY))
	if(pdz_set_iic_copy[_cur_pdz_set]!=Pdz_set[_cur_pdz_set].value)
	{//запись в ИИС обновленного параметра
		tech_fl|=IIC_BUSY;
		WriteSetIIC(Pdz_set[_cur_pdz_set].value,0x100+_cur_pdz_set*2);
		pdz_set_iic_copy[_cur_pdz_set]=Pdz_set[_cur_pdz_set].value;
	}
}

extern NET_OUTPUT_STRUCT1 data_for_slave1;
//extern NET_OUTPUT_STRUCT2 data_for_slave2;

uint8_t fire_floor;
uint8_t fire_floor1;
uint8_t fire_floor2;
uint8_t fire_floor3;
uint8_t fire_floor4;
extern uint16_t fire_sps;
extern uint16_t fire_sb;
extern uint16_t fire_net;
uint16_t fire_zone;
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"

extern MOE <13+80*16,24+32*0,      0,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD01> KPD01;
extern MOE <55+80*17,25+32*0,      1,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD02> KPD02;
extern KOGT <12+80*16,1+32*0,     13,             OPT_CHECK_PRESS|OPT_CHECK_OS,    strPP001>   PP001;
extern KOGT <20+80*16,2+32*0,     14,             OPT_CHECK_PRESS|OPT_CHECK_OS,    strPP01>   PP01;
extern ZOVT <19+80*16,5+32*1,       6, 0,                                           strZOV0> ZOV0;
extern KOGT <0+80*0,5+32*1,       4,                               OPT_CHECK_OS,  strVZK0> VZK0;

extern MOE <29+80*16,26+32*0,      2,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD11> KPD11;
extern MOE <71+80*17,27+32*0,      3,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD12> KPD12;
extern KOGT <28+80*16,0+32*0,     12,             OPT_CHECK_PRESS|OPT_CHECK_OS,    strPP1>   PP1;
extern ZOVT <27+80*16,5+32*1,      6, 0,                                           strZOV1> ZOV1;
extern KOGT <0+80*0,5+32*1,       5,                               OPT_CHECK_OS,  strVZK1> VZK1;


void Pdz1_stop()
{
//	switch(Pdz1.sub_st)
//	{
//		case 0://останов вентилятора
//            KPD01.auto_close();
//            KPD02.auto_close();
//            KPD11.auto_close();
//            KPD12.auto_close();
//			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
//				Pdz1.to_stad(PDZ_ST_STOP,1);
//		break;
//		case 1://останов вентилятора
//            PP001.auto_close();
//			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
//				Pdz1.to_stad(PDZ_ST_STOP,2);
//		break;
//		case 2://останов вентилятора
//            PP01.auto_close();
//			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
//				Pdz1.to_stad(PDZ_ST_STOP,3);
//		break;
//		case 3://останов вентилятора
//			PP1.auto_close();
//			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
//				Pdz1.to_stad(PDZ_ST_STOP,4);
//		break;
//		case 4://останов вентилятора
//			VZK0.auto_close();
//			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
//				Pdz1.to_stad(PDZ_ST_STOP,5);
//		break;
//		case 5://останов вентилятора
//			VZK1.auto_close();
//			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
//				Pdz1.to_stad(PDZ_ST_STOP,6);
//		break;
//		case 6://останов вентилятора
//			ZOV0.auto_close();
//			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
//				Pdz1.to_stad(PDZ_ST_STOP,7);
//		break;
//		case 7://останов вентилятора
//			ZOV1.auto_close();
//			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
//				Pdz1.to_stad(PDZ_ST_STOP,8);
//		break;
//		case 8://полный останов
//		break;
//   }

}


void Pdz1_work()
{
//	switch(Pdz1.sub_st)
//	{
//		case 0:
//		    if (fire_floor1==0) KPD01.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,1);
//		break;
//		case 1:
//			if (fire_floor1==0) KPD02.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,2);
//		break;
//		case 2:
//			if (fire_floor1==1) KPD11.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,3);
//		break;
//		case 3:
//			if (fire_floor1==1) KPD12.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,4);
//		break;
//		case 4:
//			ZOV0.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,5);
//		break;
//		case 5:
//			ZOV1.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,6);
//		break;
//		case 6:
//			VZK0.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,7);
//		break;
//		case 7:
//			VZK1.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,8);
//		break;
//		case 8:
//            PP001.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,9);
//		break;
//        case 9:
//            PP01.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,10);
//		break;
//		case 10:
//            PP1.auto_open();
//			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,0);
//		break;
//	}

}

extern const prog_char pdz_stad_op_str[10][16] PROGMEM;
const prog_char pdz_stad_op_str[10][16]=
{
	"Пуск Гр1",
	"Пуск Гр2",
	"Пуск Гр3",
	"Пуск Гр4",
	"Пуск Гр5",
	"Пуск Гр6",
	"Пуск Гр7",
	"Пуск Гр8",
	"Пуск Гр1",
	"Запущен"
};

extern const prog_char pdz_stad_cl_str[3][16] PROGMEM;
const prog_char pdz_stad_cl_str[3][16]=
{
	"Останов ВД",
	"Останов ПП",
	"Дежурный"
};

void Pdz1_show_lcd()
{
	LCD_abc((char*)pdz_name_str[0],0);
	LCD_uind(Pdz1.read_t_sub_st(),11,5);
	LCD_uind(Pdz1.sub_st,5,2);

//	if(Pdz1.stad==PDZ_ST_WORK) LCD_abc((char*)pdz_stad_op_str[Pdz1.sub_st],20);//16
//	else if(Pdz1.stad==PDZ_ST_STOP) LCD_abc((char*)pdz_stad_cl_str[Pdz1.sub_st],20);//16
}



void Pdz1_drv()
{
	uint8_t new_st=Pdz1.stad;

	if(scafe_fl&SCAFE_STOP_PDZ)	{

	}
	else {

	}

	if((!(fire_floor==0xff))||(fire_fl&FIRE_FL_M_ALL)) new_st=PDZ_ST_WORK;
	else new_st=PDZ_ST_STOP;

	if(new_st!=Pdz1.stad) Pdz1.to_stad(new_st,0);

	if(Pdz1.stad==PDZ_ST_WORK) Pdz1_work();
	else Pdz1_stop();
}
