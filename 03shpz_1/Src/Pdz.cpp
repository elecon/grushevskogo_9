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


extern uint16_t fire_sps;
extern uint16_t fire_sb;
extern uint16_t fire_net;
uint16_t fire_zone;
#include "Dev_kog.h"
#include "Dev_VZK.h"
#include "Dev_KD.h"
//extern KOG VD;
//extern KD KD1,KD2,KD3,KD4;
//extern VZK GR1,GR2,GR3,GR4,GR5,GR6,GR7,GR8;
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_zov_t.h"
#include "../../Devs/Dev_moe.h"
//extern ZOVT<LED_NOMER, MSK_BIT,OUT_BIT,OPTIONS,STRING> ZOV18;
extern MOE <12+80*0,24+32*1,    0,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD11> KPD11;
extern MOE < 4+80*0,25+32*1,    1,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD12> KPD12;
extern MOE <50+80*0,26+32*1,    2,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD21> KPD21;
extern MOE <42+80*0,27+32*1,    3,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD22> KPD22;
extern MOE <55+80*0,28+32*1,    4,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD31> KPD31;
extern MOE <47+80*0,29+32*1,    5,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD32> KPD32;

extern KOGT <19+80*0,13+32*0,  12,             OPT_CHECK_PRESS|OPT_CHECK_OS,   strPP1> PP1;
extern KOGT <57+80*0,14+32*0,  13,             OPT_CHECK_PRESS|OPT_CHECK_OS,   strPP2> PP2;
extern KOGT <62+80*0,15+32*0,  14,             OPT_CHECK_PRESS|OPT_CHECK_OS,   strPP3> PP3;

extern ZOVT <27+80*0,5+32*1,   9, 0,                                           strZOV1> ZOV1;
extern ZOVT <65+80*0,5+32*1,   10, 0,                                          strZOV2> ZOV2;
extern ZOVT <70+80*0,5+32*1,   11, 0,                                          strZOV3> ZOV3;
//ZOVT <73+80*0,5+32*1,   11, 0,                                          strDVR> DVR;

extern KOGT <32+80*0,5+32*1,   6,                               OPT_CHECK_OS,  strVZK1> VZK1;
extern KOGT <32+80*0,5+32*1,   7,                               OPT_CHECK_OS,  strVZK2> VZK2;
extern KOGT <32+80*0,5+32*1,   8,                               OPT_CHECK_OS,  strVZK3> VZK3;


void Pdz1_stop()
{
	switch(Pdz1.sub_st)
	{
		case 0://останов вентилятора
            ZOV1.auto_close();
            ZOV2.auto_close();
            ZOV3.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,1);
		break;
		case 1://останов вентилятора
			VZK1.auto_close();
			VZK2.auto_close();
			VZK3.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,2);
		break;
		case 2://останов вентилятора
			PP1.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,3);
		break;
		case 3://останов вентилятора
			PP2.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,4);
		break;
		case 4://останов вентилятора
			PP3.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,5);
		break;
		case 5://останов вентилятора
			KPD11.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,6);
		break;
		case 6://останов вентилятора
			KPD12.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,7);
		break;
		case 7://останов вентилятора
			KPD21.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,8);
		break;
		case 8://останов вентилятора
			KPD22.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,9);
		break;
		case 9://останов вентилятора
			KPD31.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,10);
		break;
		case 10://останов вентилятора
			KPD32.auto_close();
			if(Pdz1.read_t_sub_st()>1)//переход через 3 сек
				Pdz1.to_stad(PDZ_ST_STOP,11);
		break;
		case 11://полный останов
		break;
   }
}

void Pdz1_work()
{
	switch(Pdz1.sub_st)
	{
		case 0:
            ZOV1.auto_open();
            ZOV2.auto_open();
            ZOV3.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,1);
		break;
		case 1:
			VZK1.auto_open();
			VZK2.auto_open();
			VZK3.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,2);
		break;
		case 2:
			PP1.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,3);
		break;
		case 3:
			PP2.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,4);
		break;
		case 4:
			PP3.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,5);
		break;
		case 5:
			if (fire_fl&(FIRE_FL_S_PK1_RAZ|FIRE_FL_S_SPS1)) KPD11.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,6);
		break;
		case 6:
			if (fire_fl&(FIRE_FL_S_PK1_RAZ|FIRE_FL_S_SPS1)) KPD12.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,7);
		break;
		case 7:
			if (fire_fl&(FIRE_FL_S_PK2_RAZ|FIRE_FL_S_SPS2)) KPD21.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,8);
		break;
		case 8:
			if (fire_fl&(FIRE_FL_S_PK2_RAZ|FIRE_FL_S_SPS2)) KPD22.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,9);
		break;
		case 9:
			if (fire_fl&(FIRE_FL_S_PK3_RAZ|FIRE_FL_S_SPS3)) KPD31.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,10);
		break;
		case 10:
			if (fire_fl&(FIRE_FL_S_PK3_RAZ|FIRE_FL_S_SPS3)) KPD32.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,11);
		break;
		case 11:
                Pdz1.to_stad(PDZ_ST_WORK,0);
		break;
	}
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
extern uint16_t fire_fl;
void Pdz1_show_lcd()
{
	LCD_abc((char*)pdz_name_str[0],0);
	LCD_uind(Pdz1.read_t_sub_st(),11,5);
	if (KEY_NO) fire_fl|=FIRE_FL_STOP_PDZ;

	if(Pdz1.stad==PDZ_ST_WORK) LCD_abc((char*)pdz_stad_op_str[Pdz1.sub_st],20);//16
	else if(Pdz1.stad==PDZ_ST_STOP) LCD_abc((char*)pdz_stad_cl_str[Pdz1.sub_st],20);//16
}


uint8_t fire_floor;
void Pdz1_drv()
{
	uint8_t new_st=Pdz1.stad;

	if(scafe_fl&SCAFE_STOP_PDZ)	{

	}
	else {

	}

	if(fire_fl&(    FIRE_FL_S_PK1_RAZ|
                    FIRE_FL_S_PK2_RAZ|
                    FIRE_FL_S_PK3_RAZ|
                    FIRE_FL_S_SPS1|
                    FIRE_FL_S_SPS2|
                    FIRE_FL_S_SPS3|
                    FIRE_FL_S_ALL)) new_st=PDZ_ST_WORK;
	else new_st=PDZ_ST_STOP;

	if(new_st!=Pdz1.stad) Pdz1.to_stad(new_st,0);

	if(Pdz1.stad==PDZ_ST_WORK) Pdz1_work();
	else Pdz1_stop();
}
