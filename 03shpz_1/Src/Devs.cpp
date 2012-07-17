#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_zov_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_kog.h"
//#include "Dev_KD.h"
//#include "Dev_VZK.h"
#include <avr/delay.h>
#include "Nls.h"

#define NUM_OF_DEVS 5

extern NET_OUTPUT_STRUCT1 data_from_slave1;
extern NET_INPUT_STRUCT1 data_for_slave1;


#define MSK_NUMER_MOE 2
extern const prog_char dev_name_str_moe[] PROGMEM;
const prog_char dev_name_str_moe[] = "GR1";
//typedef prog_char1 {prog_char PROGMEM} prog_char2;

#if s03shpz_1
const prog_char strKPD11[]="КПД21";
const prog_char strKPD12[]="КПД22";
const prog_char strKPD21[]="КПД31";
const prog_char strKPD22[]="КПД32";
const prog_char strKPD31[]="КПД41";
const prog_char strKPD32[]="КПД42";

const prog_char strPP1[]="ПП2";
const prog_char strPP2[]="ПП3";
const prog_char strPP3[]="ПП4";
const prog_char strZOV1[]="ЗОВ2";
const prog_char strZOV2[]="ЗОВ3";
const prog_char strZOV3[]="ЗОВ4";
const prog_char strVZK1[]="ВЗК2";
const prog_char strVZK2[]="ВЗК3";
const prog_char strVZK3[]="ВЗК4";
#endif


extern uint8_t scafe_net;
const uint16_t Dev_constr_info[]={
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    //5
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    //10
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    //15
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    //20
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    //25
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    //30
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    //35
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    OPT_CHECK_OS|OPT_CHECK_MP,
    //40
};
const uint8_t Dev_constr[][6]={
//  led     MT      OS      dP      mp      ktr
    40  ,   0   ,   36  ,   1   ,   1   ,   0   ,
    41  ,   1   ,   1   ,   2   ,   2   ,   0   ,
    42  ,   2   ,   36  ,   3   ,   3   ,   0   ,
    44  ,   3   ,   36  ,   4   ,   4   ,   0   ,
    45  ,   4   ,   36  ,   5   ,   5   ,   0   ,
//5 led     MT      OS      dP      mp      ktr
    61  ,   5   ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
//10led     MT      OS      dP      mp      ktr
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
//15led     MT      OS      dP      mp      ktr
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
//20led     MT      OS      dP      mp      ktr
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
//25led     MT      OS      dP      mp      ktr
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
//30led     MT      OS      dP      mp      ktr
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
//35led     MT      OS      dP      mp      ktr
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
    32  ,   36  ,   36  ,   0   ,   0   ,   0   ,
//40led     MT      OS      dP      mp      ktr
};
//KOG( *name, *mn_os, enh_info,	*out, *press, *os, *mp, *ktr)


////-------------------------------------------------------------------------------------------YA6
//KOG Dev1						//клас місцевих пристроїв
//	(dev_name_str[0],		//назва яка буде відображитися на LCD
//	(uint8_t*)&mGR1,		//свытлодіод мнемосхеми
//	OPT_CHECK_OS|OPT_CHECK_MP,//статус
//	&OP_GR1,                //вихід МТ
//	0,						//контроль стану перепаду тиску
//	&OS_GR1,				//контроль стану зворотній зв'язок
//	0,						//контроль стану магнітного пускача
//	0);						//контроль стану теплового реле

KogNum Dev1(0);
KogNum Dev2(1);
KogNum Dev3(2);
KogNum Dev4(3);
KogNum Dev5(4);
KogNum Dev6(5);
KogNum Dev7(6);
KogNum Dev8(7);
KogNum Dev9(8);
KogNum Dev10(9);
KogNum Dev11(10);
KogNum Dev12(11);
KogNum Dev13(12);
KogNum Dev14(13);
KogNum Dev15(14);
KogNum Dev16(15);
KogNum Dev17(16);
KogNum Dev18(17);
KogNum Dev19(18);
KogNum Dev20(19);
KogNum Dev21(20);
KogNum Dev22(21);
KogNum Dev23(22);
KogNum Dev24(23);
KogNum Dev25(24);
KogNum Dev26(25);
KogNum Dev27(26);
KogNum Dev28(27);
KogNum Dev29(28);
KogNum Dev30(29);
KogNum Dev31(30);
KogNum Dev32(31);
KogNum Dev33(32);
KogNum Dev34(33);
KogNum Dev35(34);
KogNum Dev36(35);
KogNum Dev37(36);
KogNum Dev38(37);
KogNum Dev39(38);
KogNum Dev40(39);

TDevObject* pDevs_arr[]=
{
	&Dev1,
	&Dev2,
	&Dev3,
	&Dev4,
	&Dev5,

	&Dev6,
	&Dev7,
	&Dev8,
	&Dev9,
	&Dev10,

	&Dev11,
	&Dev12,
	&Dev13,
	&Dev14,
	&Dev15,

	&Dev16,
	&Dev17,
	&Dev18,
	&Dev19,
	&Dev20,

	&Dev21,
	&Dev22,
	&Dev23,
	&Dev24,
	&Dev25,

	&Dev26,
	&Dev27,
	&Dev28,
	&Dev29,
	&Dev30,

	&Dev31,
	&Dev32,
	&Dev33,
	&Dev34,
	&Dev35,

	&Dev36,
	&Dev37,
	&Dev38,
	&Dev39,
	&Dev40,
};
//extern const prog_char dev_name_str[][5] PROGMEM;
const prog_char dev_name_str[][5]=
{
	"Гр1",
	"Гр2",
	"Гр3",
	"Гр4",
	"Гр5",
//	5
	"Гр6",
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
//	10
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
//	15
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
//	20
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
//	25
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
//	30
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
//	35
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
	"Гр1",
//	40
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
    //GR1.name=dev_name_str[0];
    //GR1.out=OUT_GRUPPA[0];

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
uint8_t DevsCounterFilter[NUM_OF_DEVS];
uint8_t DevsFilterTemp[NUM_OF_DEVS];
void Dev_drv()
{
	uint8_t i;
	for(i=0;i<NUM_OF_DEVS;i++)
	{
		pDevs_arr[i]->drv();
		pDevs_arr[i]->show_mnem();
		data_from_slave1.devs_net_stat[i]=pDevs_arr[i]->stan;
		if (DevsFilterTemp[i] == data_for_slave1.devs_net_cmd[i]) {
            if (DevsCounterFilter[i]<5){
                if (!sec_tik) {
                    DevsCounterFilter[i]++;
                }
            }
            else {
                DevsFilterTemp[i]=data_for_slave1.devs_net_cmd[i];
                pDevs_arr[i]->stad|=data_for_slave1.devs_net_cmd[i];
            }
		}
		else {
            DevsFilterTemp[i]=data_for_slave1.devs_net_cmd[i];
            DevsCounterFilter[i]=0;
		}
	}
}

uint8_t _cur_dev;
extern const prog_char strNoDevs[] PROGMEM;
const prog_char strNoDevs[]="No devs";
void show_devs()
{
	_cur_dev=getpm(_cur_dev,NUM_OF_DEVS);
	pDevs_arr[_cur_dev]->show_lcd();
//    LCD_abc((char*)strNoDevs,0);
}

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
	const prog_char noll_str[]          = "0";
	const prog_char one_str[]          = "1";

