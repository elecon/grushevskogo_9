#include "Test.h"
#include <avr/delay.h>
#include "Sgwork.h"
SysTime time;
int16_t sys_set_flag;
int16_t sys_set_flag_copy;
uint8_t read_time_counter;
extern uint8_t BCD(uint8_t _byte, uint8_t io);
extern void WriteSetIIC(uint16_t _value, uint16_t _adr);
extern uint16_t ReadSetIIC(uint16_t _adr);
void WhatTimeIsItNow()
{
	Start_iic();
	Tr_iic_byte(0xA0);//10100000 select iic write
	Tr_iic_byte(0x03);//addr
	Start_iic();
	Tr_iic_byte(0xA1);
	time.min=BCD(Rd_iic_byte(1),1);
	time.hour=BCD(Rd_iic_byte(1)&0x3f,1);
	time.day=BCD(Rd_iic_byte(1)&0x3f,1);
	time.month=BCD(Rd_iic_byte(0)&0x1f,1);
	Stop_iic();
	read_time_counter=30;
}

void check_iic_status()
{
	tech_fl&=~DEFAULT_SET;
	Start_iic();
	if(!Tr_iic_byte(0xA2))//10100010 select iic write
	{
		tech_fl|=NO_IIC;
		Stop_iic();
	}
	else{
	Tr_iic_byte(0x00);//first addr
	Tr_iic_byte(0x10);//second addr
	Start_iic();
	Tr_iic_byte(0xA3);
	sys_set_flag=(int16_t)Rd_iic_byte(0);
	if(sys_set_flag) tech_fl|=DEFAULT_SET;
	Stop_iic();
	_delay_us(2);
	if(tech_fl&DEFAULT_SET)
	{
		_delay_ms(10);
		Start_iic();
		Tr_iic_byte(0xA2);//10100010 select iic write
		Tr_iic_byte(0x00);//first addr
		Tr_iic_byte(0x10);//second addr
		Tr_iic_byte(0);
		Stop_iic();
		sys_set_flag=0;
		sys_set_flag_copy=0;
		_delay_ms(10);
	}}
	//запись в таймер
	Start_iic();
	Tr_iic_byte(0xA0);//10100000 select iic write
	Tr_iic_byte(0x00);//addr
	Tr_iic_byte(0x08);
	Stop_iic();
	_delay_us(4);
	WhatTimeIsItNow();
}
extern const prog_char sys_set_restart_str[] PROGMEM;
const prog_char sys_set_restart_str[]="Заводск. уставки";
void show_restart_set()
{
	getpm_dig(&sys_set_flag,0,0,1);
	LCD_abc((char*)sys_set_restart_str,0);
	LCD_uind(sys_set_flag,20,1);//16
	if(!(tech_fl&IIC_BUSY))
	if(sys_set_flag!=sys_set_flag_copy)
	{
		tech_fl|=IIC_BUSY;
		Start_iic();
		Tr_iic_byte(0xA2);//10100010 select iic write
		Tr_iic_byte(0x00);//first addr
		Tr_iic_byte(0x10);//second addr
		Tr_iic_byte(sys_set_flag);
		Stop_iic();
		sys_set_flag_copy=sys_set_flag;
	}
}

uint8_t BCD(uint8_t _byte, uint8_t io)//io=0 - из числа  в БЦД; 1 - из БЦД в число
{
	uint8_t temp;
	if(io)
	{
		temp=_byte>>4;
		temp*=10;

		temp+=(_byte&0xf);
		return temp;
	}
	else
	{
		temp =(_byte/10);
		temp<<=4;
		temp+=(_byte%10);
		return temp;
    }
}

int16_t time_set_selector;//переменная для хранения уставок времени
uint8_t time_set_flag;
#define SET_DAY		0x01
#define SET_MONTH	0x02
#define SET_HOUR	0x04
#define SET_MIN		0x08

uint8_t time_selector;
uint8_t time_blink;
SysTime time_cpy;
void show_time_set()
{
	time_selector=getpm(time_selector,5);
	if(!time_selector)//показ времени
	{
		if(!time_set_flag)
		{
			time_cpy.min=time.min;
			time_cpy.hour=time.hour;
			time_cpy.day=time.day;
			time_cpy.month=time.month;
		}
		else
		{
			if(!(tech_fl&IIC_BUSY))
			{
				tech_fl|=IIC_BUSY;
				if((time_cpy.min!=time.min)||(time_cpy.hour!=time.hour)||
					(time_cpy.day!=time.day)||(time_cpy.month!=time.month))
				{//запись времени в таймер
					Start_iic();
					Tr_iic_byte(0xA0);//10100000 select iic write
					Tr_iic_byte(0x03);//addr
					Tr_iic_byte(BCD(time_cpy.min,0));
					Tr_iic_byte(BCD(time_cpy.hour,0));
					Tr_iic_byte(BCD(time_cpy.day,0));
					Tr_iic_byte(BCD(time_cpy.month,0));
					Stop_iic();
					time.min=time_cpy.min;
					time.hour=time_cpy.hour;
					time.day=time_cpy.day;
					time.month=time_cpy.month;
				}
				time_set_flag=0;
			}
		}
	}
	else
	{
		//запись временных уставок
		LCD_putc('^',26+(time_selector-1)*3);//22
		switch(time_selector-1)
		{
			case 0:
					if(!(time_set_flag&SET_DAY))
					{
						time_set_selector=(int16_t)(time_cpy.day);
						time_set_flag=SET_DAY;
					}
					getpm_dig(&time_set_selector,0,1,31);
					time_cpy.day=(uint8_t)time_set_selector;
					break;
			case 1:
					if(!(time_set_flag&SET_MONTH))
					{
						time_set_selector=(int16_t)(time_cpy.month);
						time_set_flag=SET_MONTH;
					}
					getpm_dig(&time_set_selector,0,1,12);
					time_cpy.month=(uint8_t)time_set_selector;
					break;
			case 2:
					if(!(time_set_flag&SET_HOUR))
					{
						time_set_selector=(int16_t)(time_cpy.hour);
						time_set_flag=SET_HOUR;
					}
					getpm_dig(&time_set_selector,0,0,23);
					time_cpy.hour=(uint8_t)time_set_selector;
					break;
			case 3:
					if(!(time_set_flag&SET_MIN))
					{
						time_set_selector=(int16_t)(time_cpy.min);
						time_set_flag=SET_MIN;
					}
					getpm_dig(&time_set_selector,0,0,59);
					time_cpy.min=(uint8_t)time_set_selector;
					break;
		}
	}

	LCD_uind(time_cpy.day,5,2|LEAD_ZERO);
	LCD_putc('.',7);
	LCD_uind(time_cpy.month,8,2|LEAD_ZERO);

	LCD_uind(time_cpy.hour,11,2|LEAD_ZERO);
	if(!sec_tik) time_blink^=0xff;
	if(time_blink&1)
	LCD_putc(':',13);
	LCD_uind(time_cpy.min,14,2|LEAD_ZERO);
}

extern const prog_char sys_set_str[3][14] PROGMEM;
const prog_char sys_set_str[3][14]=
{
	"1.Перезапуск",
	"2.Время",
	"Сист. уставки"
};
extern uint8_t cur_menu;
extern Menu* pMenu_arr[];
uint8_t sys_set_counter;
void show_sys_set()
{
	time_selector=0;//обновления указателя уставок времени
	time_set_flag=0;
	sys_set_counter=getpm(sys_set_counter,2);
	pMenu_arr[cur_menu]->next_menu = sys_set_counter+EMenuResSet;//
	LCD_abc((char*)sys_set_str[2],0);
	LCD_putc('>',20);//16
	LCD_abc((char*)sys_set_str[sys_set_counter],21);//17
}

extern uint8_t MSK[8];
#include "Etaz.h"


extern const prog_char test_str[5][6] PROGMEM;
const prog_char test_str[5][6]=
{
	"МСК",
	"NET",
	"МНЕМО",
	"TECT:",
	"NET"
};

uint8_t test_counter;
void show_test()
{
	test_counter=getpm(test_counter,3);
	pMenu_arr[cur_menu]->next_menu = test_counter+EMenuMSKTest;

	LCD_abc((char*)test_str[3],0);
	LCD_putc('>',20);//16
	LCD_abc((char*)test_str[test_counter],21);//17
	scafe_fl&=~MNEMO_WRK;
	scafe_fl&=~(SCAFE_TEST_MT|SCAFE_T_MT_OP);
}

uint8_t test2_counter;

extern const prog_char test_str2[5][6] PROGMEM;
const prog_char test_str2[5][6]=
{
	"МСК",
	"MT",
	"NET",
	"МНЕМО",
	"TECT:",
};
extern const prog_char Test2Str[] PROGMEM;
const prog_char Test2Str[]="TEST 2";
void show_test2()
{
	test2_counter=getpm(test2_counter,3);
	pMenu_arr[cur_menu]->next_menu = test2_counter+EMenuMSKTest2;
//
	LCD_abc((char*)Test2Str,0);
	LCD_putc('>',20);//16
	LCD_abc((char*)test_str2[test2_counter],21);//17
	TechFlag&=~TEST_MT;
//	scafe_fl&=~MNEMO_WRK;
//	scafe_fl&=~(SCAFE_TEST_MT|SCAFE_T_MT_OP);
}
extern uint8_t NetPackInfo2[3];
extern uint8_t Uart1Counter;
extern uint8_t mnemo_counter;
const prog_char Test2NetStr[]="merega";
const prog_char Test2NetCounStr[]="mn_coun";
extern uint8_t FOR_ME_SUMMA,FOR_ME_SUMMA2,FOR_ME_SUMMA3;
extern uint8_t Shota;
void show_net_test2()
{
	LCD_abc((char*)Test2NetStr,0);
	LCD_uind(NetPackInfo2[0+ZSUV],8,2|LEAD_ZERO);
	LCD_uind(NetPackInfo2[1+ZSUV],11,2|LEAD_ZERO);
	LCD_uind(NetPackInfo2[2+ZSUV],14,2|LEAD_ZERO);
	//LCD_uind(NetPackInfo2[1],14,2|LEAD_ZERO);
	LCD_abc((char*)Test2NetCounStr,20);
	LCD_uind(FOR_ME_SUMMA,	28,2|LEAD_ZERO);
	LCD_uind(Shota,			31,2|LEAD_ZERO);
	LCD_uind(FOR_ME_SUMMA2,	34,2|LEAD_ZERO);

	//	FOR_ME_SUMMA
}

extern const prog_char msk_test_str[2][6] PROGMEM;
const prog_char msk_test_str[2][6]=
{
	"МСК1:",
	"МСК2:",
};

void show_msk_test()
{
	LCD_abc((char*)msk_test_str[0],0);
	LCD_uind16(MSK[3],5,2|LEAD_ZERO);
	LCD_uind16(MSK[2],8,2|LEAD_ZERO);
	LCD_uind16(MSK[1],11,2|LEAD_ZERO);
	LCD_uind16(MSK[0],14,2|LEAD_ZERO);

	LCD_abc((char*)msk_test_str[1],20);//16
	LCD_uind16(MSK[7],25,2|LEAD_ZERO);//21
	LCD_uind16(MSK[6],28,2|LEAD_ZERO);//24
	LCD_uind16(MSK[5],31,2|LEAD_ZERO);//27
	LCD_uind16(MSK[4],34,2|LEAD_ZERO);//30
}
extern uint8_t TestMSK;
extern const prog_char MSK_OK_str[] PROGMEM;
const prog_char MSK_OK_str[]="MSK ПЕРЕВIРЕНА";
extern const prog_char MSK_ERR_str[] PROGMEM;
const prog_char MSK_ERR_str[]="MSK ERROR";
void show_msk_test2()
{
	uint8_t i;
	//TechFlag|=TEST_MSK;
	if (TestMSKResult==0xff) LCD_abc((char*)MSK_OK_str,0); else LCD_abc((char*)MSK_ERR_str,0);

	for (i=0;i<8;i++) {
		if (TestMSKResult&(1<<i)) LCD_uind(1,i+20,1|LEAD_ZERO); 	else LCD_uind(0,i+20,1|LEAD_ZERO);
	}
	//LCD_uind(TEST_MSK,25,2|LEAD_ZERO);
	//LCD_uind(TestMSKResult,20,2|LEAD_ZERO);
}

extern const prog_char mnemo_str[7][5] PROGMEM;
const prog_char mnemo_str[7][5]=
{
	"ПОЛЕ",
	"АВТО",
	"ЧЕРН",
	"КРАС",
	"ЖЕЛТ",
	"ЗЕЛН",
	"ОСТН"
};
uint8_t mnemo_test_counter;
void show_mnemo_test()
{
	mnemo_test_counter=getpm(mnemo_test_counter,NUM_OF_MNEMO);
	scafe_fl|=MNEMO_WRK;
	if(KEY_4) scafe_fl^=FIELD;
	if(KEY_1) scafe_fl^=FREEZ;
	if(KEY_7) {scafe_fl&=~(RED|GREEN|YELLOW);}
	if(KEY_8) {scafe_fl&=~(GREEN|YELLOW);scafe_fl|=RED;}
	if(KEY_9) {scafe_fl&=~(GREEN|RED);scafe_fl|=YELLOW;}
	if(KEY_NO) {scafe_fl&=~(RED|YELLOW);scafe_fl|=GREEN;}

	if(scafe_fl&FIELD) LCD_abc((char*)mnemo_str[0],0);
	else LCD_abc((char*)mnemo_str[1],0);

	if(scafe_fl&FREEZ) LCD_abc((char*)mnemo_str[6],10);

	if(!(scafe_fl&(RED|GREEN|YELLOW))) LCD_abc((char*)mnemo_str[2],5);
	else if(scafe_fl&RED) LCD_abc((char*)mnemo_str[3],5);
	else if(scafe_fl&YELLOW) LCD_abc((char*)mnemo_str[4],5);
	else LCD_abc((char*)mnemo_str[5],5);

	LCD_uind16(mnemo_test_counter,20,2|LEAD_ZERO);//16
}
//---------------------------------------------------------------------------
/*
extern uint8_t NetPackInfo[cur_net_pack];
void show_net_test()
{
	test_counter=getpm(test_counter,2);
	pMenu_arr[cur_menu]->next_menu = test_counter+14;

	LCD_abc((char*)test_net_str[2],0);
	LCD_putc('>',20);//16
	LCD_abc((char*)NetPackInfo[test_counter],21);//17
//	scafe_fl&=~MNEMO_WRK;
}

const prog_char test_net_str[2][6]=
{
	"SH1",
	"SH2",
};
*/

//---------------------------------------------------------------------------
//отработка сообщений
#define NUM_OF_MESSAGE 15//17


uint16_t message_addr;
uint16_t message_addr_old;
void Message_init()
{
	message_addr=ReadSetIIC(0x500);
	message_addr_old=message_addr;
}

extern uint8_t fire_floor;
extern uint16_t net_fl;//флаги наличия шкафов в сети
//extern uint16_t fire_sps;
//extern uint16_t fire_sb;
//extern uint16_t fire_net;
//extern uint16_t fire_vzk;
uint8_t message_arch_byte[NUM_OF_MESSAGE];//информация об ошибке
uint8_t message_arch_byte_cpy[NUM_OF_MESSAGE];
//uint8_t floor;
void Message_drv()
{


	uint8_t i;
	if(!sec_tik)
	{
		if(!read_time_counter)
		{
			if(!(tech_fl&IIC_BUSY))
			{
				tech_fl|=IIC_BUSY;
				WhatTimeIsItNow();
			}
		}
		else read_time_counter--;
	}

	if(tech_fl&IIC_BUSY) return;//нет смысла крутить драйвер, всеравно ничего не запишем
	//сбор информации о системе для записи в сообщения
	//------------------------------------
		if(fire_fl&FIRE_FL_S_PK1) message_arch_byte[1]=1;
	else message_arch_byte[1]=0;
	if(fire_fl&FIRE_FL_S_PK2) message_arch_byte[2]=1;
	else message_arch_byte[2]=0;
	if(fire_fl&FIRE_FL_S_PK3) message_arch_byte[3]=1;
	else message_arch_byte[3]=0;
	if(fire_fl&FIRE_FL_S_PK4) message_arch_byte[4]=1;
	else message_arch_byte[4]=0;

	if(fire_fl&FIRE_FL_S_SPS1) message_arch_byte[5]=1;
	else message_arch_byte[5]=0;
	if(fire_fl&FIRE_FL_S_SPS2) message_arch_byte[6]=1;
	else message_arch_byte[6]=0;
	if(fire_fl&FIRE_FL_S_SPS3) message_arch_byte[7]=1;
	else message_arch_byte[7]=0;
	if(fire_fl&FIRE_FL_S_SPS4) message_arch_byte[8]=1;
	else message_arch_byte[8]=0;

	if(fire_fl&FIRE_FL_S_PK1_RAZ) message_arch_byte[9]=1;
	else message_arch_byte[9]=0;
	if(fire_fl&FIRE_FL_S_PK2_RAZ) message_arch_byte[10]=1;
	else message_arch_byte[10]=0;
	if(fire_fl&FIRE_FL_S_PK3_RAZ) message_arch_byte[11]=1;
	else message_arch_byte[11]=0;
	if(fire_fl&FIRE_FL_S_PK4_RAZ) message_arch_byte[12]=1;
	else message_arch_byte[12]=0;

	if(fire_fl&FIRE_FL_S_ALL) message_arch_byte[13]=1;
	else message_arch_byte[13]=0;
	if(fire_fl&FIRE_FL_S_STOP_PDZ) message_arch_byte[14]=1;
	else message_arch_byte[14]=0;
	//------------------------------------
//	if(scafe_fl&SCAFE_FIRE_KEY) message_arch_byte[3]=fire_floor;
//	else message_arch_byte[3]=0;
	//------------------------------------
//	if(scafe_fl&SCAFE_FIRE_NET) message_arch_byte[4]=fire_floor;
//	else message_arch_byte[4]=0;
	//------------------------------------
//	if(scafe_fl&SCAFE_FIRE_VZK) message_arch_byte[5]=fire_floor;
//	else message_arch_byte[5]=0;
/*	//------------------------------------
	if(net_fl&Sh1) message_arch_byte[6]=0;
	else message_arch_byte[6]=1;
	//------------------------------------
	if(net_fl&Sh2) message_arch_byte[7]=0;
	else message_arch_byte[7]=1;
	//------------------------------------
	if(net_fl&Sh3) message_arch_byte[8]=0;
	else message_arch_byte[8]=0;
	//------------------------------------
	if(net_fl&Sh4) message_arch_byte[9]=0;
	else message_arch_byte[9]=1;
	//------------------------------------
	if(net_fl&Sh5) message_arch_byte[10]=0;
	else message_arch_byte[10]=1;
	//------------------------------------
	if(net_fl&Sh6) message_arch_byte[11]=0;
	else message_arch_byte[11]=1;
	//------------------------------------
	if(net_fl&Sh7) message_arch_byte[12]=0;
	else message_arch_byte[12]=1;
	//------------------------------------
	if(net_fl&Sh8) message_arch_byte[13]=0;
	else message_arch_byte[13]=1;
	//------------------------------------
	if(net_fl&Sh9) message_arch_byte[14]=0;
	else message_arch_byte[14]=1;
	//------------------------------------
	if(net_fl&ShA) message_arch_byte[15]=0;
	else message_arch_byte[15]=1;
	//------------------------------------
	if(net_fl&ShB) message_arch_byte[16]=0;
	else message_arch_byte[16]=1;
*/	//------------------------------------
//	message_arch_byte[2]=floor;//(fire_floor);
	//------------------------------------
//	message_arch_byte[3]=fire_sb;
	//------------------------------------
//	message_arch_byte[4]=fire_net;
	//------------------------------------
//	message_arch_byte[5]=fire_vzk;
	//------------------------------------
//	message_arch_byte[6]=(uint8_t)PP7.enh_info;
	//------------------------------------
	//------------------------------------
	if(message_addr>0x1ff0) message_addr=0x0510;
	if(message_addr<0x0510) message_addr=0x0510;
	for(i=0;i<NUM_OF_MESSAGE;i++)
	{
		if(!(tech_fl&IIC_BUSY))
		if(message_arch_byte[i]!=message_arch_byte_cpy[i])
		{
			tech_fl|=IIC_BUSY;
			message_arch_byte_cpy[i]=message_arch_byte[i];
			Start_iic();
			Tr_iic_byte(0xA2);
			Tr_iic_byte((uint8_t)(message_addr>>8));
			Tr_iic_byte((uint8_t)(message_addr&0xff));
			Tr_iic_byte(time.hour);
			Tr_iic_byte(time.min);
			Tr_iic_byte(time.day);
			Tr_iic_byte(time.month);
			Tr_iic_byte(i);
			Tr_iic_byte(message_arch_byte[i]);
			Stop_iic();
			message_addr+=0x10;
			return;
		}
	}
	if(!(tech_fl&IIC_BUSY))
	if(message_addr!=message_addr_old)
	{
		tech_fl|=IIC_BUSY;
		message_addr_old=message_addr;
		WriteSetIIC(message_addr, 0x500);
	}
}

extern const prog_char message_str[NUM_OF_MESSAGE][15] PROGMEM;
const prog_char message_str[NUM_OF_MESSAGE][15]=
{
	"Старт системы",
	"Кн1 наж.",
	"Кн2 наж.",
	"Кн3 наж.",
	"Кн4 наж.",
	"Пож.СПС1",
	"Пож.СПС2",
	"Пож.СПС3",
	"Пож.СПС4",
	"Пож.Кн1",
	"Пож.Кн2",
	"Пож.Кн3",
	"Пож.Кн4",
	"Пож.Заг.",
	"Стоп ПДЗ",
};

uint16_t message_addr_cpy;
uint16_t message_addr_cpy1;
uint8_t message_code;
uint8_t message_par;
SysTime time_message;
void read_message_from_iic()
{
	Start_iic();
	Tr_iic_byte(0xA2);//10100110 select iic write
	Tr_iic_byte((uint8_t)(message_addr_cpy1>>8));//addr_cpy
	Tr_iic_byte((uint8_t)(message_addr_cpy1&0xff));//addr_cpy
	Start_iic();
	Tr_iic_byte(0xA3);
	time_message.hour=Rd_iic_byte(1);
	time_message.min=Rd_iic_byte(1);
	time_message.day=Rd_iic_byte(1);
	time_message.month=Rd_iic_byte(1);
	message_code=Rd_iic_byte(1);
	message_par=Rd_iic_byte(0);
	Stop_iic();
}

extern const prog_char no_arch_str[] PROGMEM;
const prog_char no_arch_str[]="нет архива";
extern const prog_char no_iic_str[] PROGMEM;
const prog_char no_iic_str[]="Ошибка И2С";
void show_message()
{
	if(tech_fl&NO_IIC)
	{
		LCD_abc((char*)no_iic_str,0);
		return;
	}
	if(!(tech_fl&IIC_BUSY))
	{
		if(KEY_5)
		{//up message
			tech_fl|=IIC_BUSY;
			if(message_addr_cpy1<0x1ff0) message_addr_cpy1+=0x10;
			else message_addr_cpy1=0x0510;
			read_message_from_iic();
		}
		if(KEY_2)
		{
			tech_fl|=IIC_BUSY;
			if(message_addr_cpy1>0x0510) message_addr_cpy1-=0x10;
			else message_addr_cpy1=0x1ff0;
			read_message_from_iic();
		}
	}

		if(!(tech_fl&IIC_BUSY))
		if(message_addr_cpy!=message_addr-0x10)
		{
			tech_fl|=IIC_BUSY;
			message_addr_cpy=message_addr-0x10;
			message_addr_cpy1=message_addr-0x10;
			read_message_from_iic();
		}
	if(message_code>NUM_OF_MESSAGE)
	{
		LCD_abc((char*)no_arch_str,20);//16
	}
	else
	{
		LCD_uind(time_message.hour,0,2|LEAD_ZERO);
		LCD_putc(':',2);
		LCD_uind(time_message.min,3,2|LEAD_ZERO);
		LCD_uind(time_message.day,6,2|LEAD_ZERO);
		LCD_putc('.',8);
		LCD_uind(time_message.month,9,2|LEAD_ZERO);
		LCD_abc((char*)message_str[message_code],20);//16
		LCD_uind16(message_par,34,2|LEAD_ZERO);//30
	}
	LCD_ind((((int16_t)(message_addr-message_addr_cpy1)-0x10)/0x10)+1,12,4|LEAD_ZERO);
}
