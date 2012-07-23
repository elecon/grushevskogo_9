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
	"���"
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
	"������ ����, �",
	"���������� ����"
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

	//���������� ������� �� ������
	if(!(tech_fl&DEFAULT_SET))//���������� ������� �� �����
	{
		for(i=0;i<NUM_OF_PDZ_SET;i++)
		{
			Pdz_set[i].value=ReadSetIIC(0x100+i*2);
			pdz_set_iic_copy[i]=Pdz_set[i].value;
		}
	}
	else //������ ��������� ������� �� ����
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
	{//������ � ��� ������������ ���������
		tech_fl|=IIC_BUSY;
		WriteSetIIC(Pdz_set[_cur_pdz_set].value,0x100+_cur_pdz_set*2);
		pdz_set_iic_copy[_cur_pdz_set]=Pdz_set[_cur_pdz_set].value;
	}
}



extern uint16_t fire_sps;
extern uint16_t fire_sb;
extern uint16_t fire_net;
uint16_t fire_zone;



void Pdz1_stop()
{
	switch(Pdz1.sub_st)
	{
		case 0://������� �����������
//            ZOV1.auto_close();
//            ZOV2.auto_close();
//            ZOV3.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,1);
		break;
		case 1://������� �����������
//			VZK1.auto_close();
//			VZK2.auto_close();
//			VZK3.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,2);
		break;
		case 2://������� �����������
//			PP1.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,3);
		break;
		case 3://������� �����������
//			PP2.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,4);
		break;
		case 4://������� �����������
//			PP3.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,5);
		break;
		case 5://������� �����������
//			KPD11.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,6);
		break;
		case 6://������� �����������
//			KPD12.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,7);
		break;
		case 7://������� �����������
//			KPD21.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,8);
		break;
		case 8://������� �����������
//			KPD22.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,9);
		break;
		case 9://������� �����������
//			KPD31.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,10);
		break;
		case 10://������� �����������
//			KPD32.auto_close();
			if(Pdz1.read_t_sub_st()>1)//������� ����� 3 ���
				Pdz1.to_stad(PDZ_ST_STOP,11);
		break;
		case 11://������ �������
		break;
   }
}


void Pdz1_work()
{
	switch(Pdz1.sub_st)
	{
		case 0:
//            ZOV1.auto_open();
//            ZOV2.auto_open();
//            ZOV3.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,1);
		break;
		case 1:
//			VZK1.auto_open();
//			VZK2.auto_open();
//			VZK3.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,2);
		break;
		case 2:
//			PP1.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,3);
		break;
		case 3:
//			PP2.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,4);
		break;
		case 4:
//			PP3.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,5);
		break;
		case 5:
//			if (fire_fl&(FIRE_FL_S_PK1_RAZ|FIRE_FL_S_SPS1)) KPD11.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,6);
		break;
		case 6:
//			if (fire_fl&(FIRE_FL_S_PK1_RAZ|FIRE_FL_S_SPS1)) KPD12.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,7);
		break;
		case 7:
//			if (fire_fl&(FIRE_FL_S_PK2_RAZ|FIRE_FL_S_SPS2)) KPD21.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,8);
		break;
		case 8:
//			if (fire_fl&(FIRE_FL_S_PK2_RAZ|FIRE_FL_S_SPS2)) KPD22.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,9);
		break;
		case 9:
//			if (fire_fl&(FIRE_FL_S_PK3_RAZ|FIRE_FL_S_SPS3)) KPD31.auto_open();
			if(Pdz1.read_t_sub_st()>Pdz_set[0].value)	Pdz1.to_stad(PDZ_ST_WORK,10);
		break;
		case 10:
//			if (fire_fl&(FIRE_FL_S_PK3_RAZ|FIRE_FL_S_SPS3)) KPD32.auto_open();
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
	"���� ��1",
	"���� ��2",
	"���� ��3",
	"���� ��4",
	"���� ��5",
	"���� ��6",
	"���� ��7",
	"���� ��8",
	"���� ��1",
	"�������"
};

extern const prog_char pdz_stad_cl_str[3][16] PROGMEM;
const prog_char pdz_stad_cl_str[3][16]=
{
	"������� ��",
	"������� ��",
	"��������"
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
