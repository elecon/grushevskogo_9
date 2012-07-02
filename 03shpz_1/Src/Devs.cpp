#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_zov_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_kog.h"
#include "Dev_KD.h"
//#include "Dev_VZK.h"
#include <avr/delay.h>
#include "Nls.h"

#define NUM_OF_DEVS 1

extern NET_OUTPUT_STRUCT1 data_from_slave1;
extern NET_INPUT_STRUCT1 data_for_slave1;

extern const prog_char dev_name_str[][5] PROGMEM;
#define MSK_NUMER_MOE 2
extern const prog_char dev_name_str_moe[] PROGMEM;
const prog_char dev_name_str_moe[] = "GR1";
//typedef prog_char1 {prog_char PROGMEM} prog_char2;

#if s03shpz_1
const prog_char strKPD11[]="���21";
const prog_char strKPD12[]="���22";
const prog_char strKPD21[]="���31";
const prog_char strKPD22[]="���32";
const prog_char strKPD31[]="���41";
const prog_char strKPD32[]="���42";

const prog_char strPP1[]="��2";
const prog_char strPP2[]="��3";
const prog_char strPP3[]="��4";
const prog_char strZOV1[]="���2";
const prog_char strZOV2[]="���3";
const prog_char strZOV3[]="���4";
const prog_char strVZK1[]="���2";
const prog_char strVZK2[]="���3";
const prog_char strVZK3[]="���4";
#endif
#if SHPZ_6
const prog_char strKPD11[]="���51";
const prog_char strKPD12[]="���52";
const prog_char strKPD21[]="���61";
const prog_char strKPD22[]="���62";
const prog_char strKPD31[]="���71";
const prog_char strKPD32[]="���72";

const prog_char strPP1[]="��5";
const prog_char strPP2[]="��6";
const prog_char strPP3[]="��7";
const prog_char strZOV1[]="���5";
const prog_char strZOV2[]="���6";
const prog_char strZOV3[]="���7";
const prog_char strVZK1[]="���5";
const prog_char strVZK2[]="���6";
const prog_char strVZK3[]="���7";
#endif
#if SHPZ_9
const prog_char strKPD11[]="���81";
const prog_char strKPD12[]="���82";
const prog_char strKPD21[]="���91";
const prog_char strKPD22[]="���92";
const prog_char strKPD31[]="���101";
const prog_char strKPD32[]="���102";

const prog_char strPP1[]="��8";
const prog_char strPP2[]="��9";
const prog_char strPP3[]="��10";
const prog_char strZOV1[]="���8";
const prog_char strZOV2[]="���9";
const prog_char strZOV3[]="���10";
const prog_char strVZK1[]="���8";
const prog_char strVZK2[]="���9";
const prog_char strVZK3[]="���10";
#endif
#if SHPZ_14
const prog_char strKPD11[]="���131";
const prog_char strKPD12[]="���132";
const prog_char strKPD21[]="���141";
const prog_char strKPD22[]="���142";
const prog_char strKPD31[]="���151";
const prog_char strKPD32[]="���152";

const prog_char strPP1[]="��13";
const prog_char strPP2[]="��14";
const prog_char strPP3[]="��15";
const prog_char strZOV1[]="���13";
const prog_char strZOV2[]="���14";
const prog_char strZOV3[]="���15";
const prog_char strVZK1[]="���13";
const prog_char strVZK2[]="���14";
const prog_char strVZK3[]="���15";
#endif

//template <uint16_t LED_NOMER, uint8_t MSK_BIT,uint8_t OUT_BIT,uint16_t OPTIONS,const char *STRING>
//    led     msk       out                     options                 str
//MOE <12+80*0,24+32*1,    0,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD11> KPD11;
//MOE < 4+80*0,25+32*1,    1,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD12> KPD12;
//MOE <50+80*0,26+32*1,    2,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD21> KPD21;
//MOE <42+80*0,27+32*1,    3,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD22> KPD22;
//MOE <55+80*0,28+32*1,    4,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD31> KPD31;
//MOE <47+80*0,29+32*1,    5,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD32> KPD32;
//
//KOGT <19+80*0,13+32*0,  12,             OPT_CHECK_MP|OPT_CHECK_OS,   strPP1> PP1;
//KOGT <57+80*0,14+32*0,  13,             OPT_CHECK_MP|OPT_CHECK_OS,   strPP2> PP2;
//KOGT <62+80*0,15+32*0,  14,             OPT_CHECK_MP|OPT_CHECK_OS,   strPP3> PP3;
//
//ZOVT <27+80*0,5+32*1,   9, 0,                                           strZOV1> ZOV1;
//ZOVT <65+80*0,5+32*1,   10, 0,                                          strZOV2> ZOV2;
//ZOVT <70+80*0,5+32*1,   11, 0,                                          strZOV3> ZOV3;
////ZOVT <73+80*0,5+32*1,   11, 0,                                          strDVR> DVR;
//
//KOGT <32+80*0,5+32*1,   6,                               OPT_CHECK_OS,  strVZK1> VZK1;
//KOGT <32+80*0,5+32*1,   7,                               OPT_CHECK_OS,  strVZK2> VZK2;
//KOGT <32+80*0,5+32*1,   8,                               OPT_CHECK_OS,  strVZK3> VZK3;

extern uint8_t scafe_net;


//KOG( *name, *mn_os, enh_info,	*out, *press, *os, *mp, *ktr)
////-------------------------------------------------------------------------------------------YA6
//VZK GR3						//���� ������� ��������
//	(dev_name_str[0],		//����� ��� ���� ������������ �� LCD
//	(uint8_t*)&mGR1,		//��������� ����������
//	VZK_CHECK_OS,			//������
//	&OP_GR1,                //����� ��
//	0,						//�������� ����� �������� �����
//	0,				        //�������� ����� �������� ��'����
//	0,						//�������� ����� ��������� �������
//	0);						//�������� ����� ��������� ����

//-------------------------------------------------------------------------------------------YA6
KOG KK1						//���� ������� ��������
	(dev_name_str[0],		//����� ��� ���� ������������ �� LCD
	(uint8_t*)&mGR1,		//��������� ����������
	OPT_CHECK_OS,			//������
	&OP_GR1,                //����� ��
	0,						//�������� ����� �������� �����
	&OS_GR1,				//�������� ����� �������� ��'����
	0,						//�������� ����� ��������� �������
	0);						//�������� ����� ��������� ����


TDevObject* pDevs_arr[]=
{
	&KK1,
};
//extern const prog_char dev_name_str[][5] PROGMEM;
const prog_char dev_name_str[][5]=
{
	"��1",
};



#define NUM_OF_DEV_SET 1
int16_t dev_set_iic_copy[NUM_OF_DEV_SET];
Set Dev_set[NUM_OF_DEV_SET];
extern const prog_char dev_set_name_str[NUM_OF_DEV_SET][17] PROGMEM;
const prog_char dev_set_name_str[NUM_OF_DEV_SET][17]=
{
	"� ���� ��������",
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

	//���������� ������� �� ������
	if(!(tech_fl&DEFAULT_SET))//���������� ������� �� �����
	{
		for(i=0;i<NUM_OF_DEV_SET;i++)
		{
			Dev_set[i].value=ReadSetIIC(0x200+i*2);
			dev_set_iic_copy[i]=Dev_set[i].value;
		}
	}
	else //������ ��������� ������� �� ����
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
	{//������ � ��� ������������ ���������
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
		"����",
		"����",
		"����"
	};

    const prog_char error_str[]         = "��:";
	const prog_char press_err_str[]     = "����";
	const prog_char mp_err_str[]        = "��";
	const prog_char ktr_err_str[]       = "���";
	const prog_char os_err_str[]        = "��";
	const prog_char stan_err_str[]      = "C���";
	const prog_char auto_str[]          = "����";
	const prog_char dist_str[]          = "����";
	const prog_char oper_str[]          = "����";
	const prog_char vidk_str[]          = "�i��";
	const prog_char zakr_str[]          = "����";

