#include "SHPZ_6.h"
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"

extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

uint8_t net_status_counter_6[FLOOR_NUM_6];

extern NET_OUTPUT_STRUCT1 data_from_slave6;
extern NET_INPUT_STRUCT1 data_for_slave6;
//extern const prog_char strKPD181[] PROGMEM;

const prog_char strKPD51[]="ÊÏÄ51";
const prog_char strKPD52[]="ÊÏÄ52";
const prog_char strKPD61[]="ÊÏÄ61";
const prog_char strKPD62[]="ÊÏÄ62";
const prog_char strKPD71[]="ÊÏÄ71";
const prog_char strKPD72[]="ÊÏÄ72";
const prog_char strPP5[]="ÏÏ5";
const prog_char strPP6[]="ÏÏ6";
const prog_char strPP7[]="ÏÏ7";
const prog_char strZOV5[]="ÇÎÂ5";
const prog_char strZOV6[]="ÇÎÂ6";
const prog_char strZOV7[]="ÇÎÂ7";
const prog_char strVZK5[]="ÂÇÊ5";
const prog_char strVZK6[]="ÂÇÊ6";
const prog_char strVZK7[]="ÂÇÊ7";

//MOE <76,MSK_NUMER_MOE,2,OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,dev_name_str_moe> GR4;
MOE_NET < 5+80*12,strKPD51,&data_from_slave6,&data_for_slave6,0,NET_WORK_SHPZ6> KPD51;
MOE_NET <47+80*13,strKPD52,&data_from_slave6,&data_for_slave6,1,NET_WORK_SHPZ6> KPD52;
KOGT_NET<4+80*12,strPP5,&data_from_slave6,&data_for_slave6,2,NET_WORK_SHPZ6> PP5;
ZOVT_NET <3+80*12,strZOV5,&data_from_slave6,&data_for_slave6,3,NET_WORK_SHPZ6> ZOV5;
KOGT_NET <0+80*0,strVZK5,&data_from_slave6,&data_for_slave6,4,NET_WORK_SHPZ6> VZK5;

MOE_NET <13+80*12,strKPD61,&data_from_slave6,&data_for_slave6,5,NET_WORK_SHPZ6> KPD61;
MOE_NET <55+80*13,strKPD62,&data_from_slave6,&data_for_slave6,6,NET_WORK_SHPZ6> KPD62;
KOGT_NET <12+80*12,strPP6,&data_from_slave6,&data_for_slave6,7,NET_WORK_SHPZ6> PP6;
ZOVT_NET <11+80*12,strZOV6,&data_from_slave6,&data_for_slave6,8,NET_WORK_SHPZ6> ZOV6;
KOGT_NET <0+80*0,strVZK6,&data_from_slave6,&data_for_slave6,9,NET_WORK_SHPZ6> VZK6;

MOE_NET <29+80*12,strKPD71,&data_from_slave6,&data_for_slave6,10,NET_WORK_SHPZ6> KPD71;
MOE_NET <71+80*13,strKPD72,&data_from_slave6,&data_for_slave6,11,NET_WORK_SHPZ6> KPD72;
KOGT_NET <28+80*12,strPP7,&data_from_slave6,&data_for_slave6,12,NET_WORK_SHPZ6> PP7;
ZOVT_NET <27+80*12,strZOV7,&data_from_slave6,&data_for_slave6,13,NET_WORK_SHPZ6> ZOV7;
KOGT_NET <0+80*0,strVZK7,&data_from_slave6,&data_for_slave6,14,NET_WORK_SHPZ6> VZK7;

TDevObject* pDevs_arr_6[]=
{
	&KPD51,
	&KPD52,
	&PP5,
	&ZOV5,
	&VZK5,

	&KPD61,
	&KPD62,
	&PP6,
	&ZOV6,
	&VZK6,

    &KPD71,
	&KPD72,
	&PP7,
	&ZOV7,
	&VZK7,
};

uint8_t* VZK_arr_6[]=
{
    (uint8_t*)&mVZK_5_1,
    (uint8_t*)&mVZK_5_2,
    (uint8_t*)&mVZK_5_3,
    (uint8_t*)&mVZK_5_4,
    (uint8_t*)&mVZK_5_5,

    (uint8_t*)&mVZK_5_6,
    (uint8_t*)&mVZK_5_7,
    (uint8_t*)&mVZK_5_8,
    (uint8_t*)&mVZK_5_9,
    (uint8_t*)&mVZK_5_10,

    (uint8_t*)&mVZK_5_11,

    (uint8_t*)&mVZK_6_1,
    (uint8_t*)&mVZK_6_2,
    (uint8_t*)&mVZK_6_3,
    (uint8_t*)&mVZK_6_4,
    (uint8_t*)&mVZK_6_5,

    (uint8_t*)&mVZK_6_6,
    (uint8_t*)&mVZK_6_7,



    (uint8_t*)&mVZK_7_1,
    (uint8_t*)&mVZK_7_2,
    (uint8_t*)&mVZK_7_3,
    (uint8_t*)&mVZK_7_4,
    (uint8_t*)&mVZK_7_5,

    (uint8_t*)&mVZK_7_6,
    (uint8_t*)&mVZK_7_7,
    (uint8_t*)&mVZK_7_8,
};

extern uint16_t i;
void Shpz_6_Ind()
{

     if (net_fl&(1<<NET_WORK_SHPZ6)) {
        for (i=0;i<26;i++) {
             *VZK_arr_6[i]=null_lamp;
        }
    }
    else {
        for (i=0;i<11;i++) {
            if (VZK5.stan&KOGT_OP) {
                if (data_from_slave6.VZK_FL1[0]&(1<<i)) *VZK_arr_6[i]=red_lamp; else *VZK_arr_6[i]=red_b_lamp;
            }
            else {
                if (data_from_slave6.VZK_FL1[0]&(1<<i)) *VZK_arr_6[i]=green_b_lamp; else *VZK_arr_6[i]=green_lamp;
            }
        }

        for (i=11;i<18;i++) {
            if (VZK6.stan&KOGT_OP) {
                if (data_from_slave6.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_6[i]=red_lamp; else *VZK_arr_6[i]=red_b_lamp;
            }
            else {
                if (data_from_slave6.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_6[i]=green_b_lamp; else *VZK_arr_6[i]=green_lamp;
            }
        }

        for (i=18;i<26;i++) {
            if (VZK7.stan&KOGT_OP) {
                if (data_from_slave6.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_6[i]=red_lamp; else *VZK_arr_6[i]=red_b_lamp;
            }
            else {
                if (data_from_slave6.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_6[i]=green_b_lamp; else *VZK_arr_6[i]=green_lamp;
            }
        }
    }
}

void Shpz_6_Work()
{
    for (i=0;i<FLOOR_NUM_6;i++) {
        if (fire_fl&(FIRE_FL_M_PK3|FIRE_FL_M_SPS3)){
            if (fire_fl&FIRE_FL_M_PK3) {
                if (fire_floor1==(5+i)) data_for_slave6.flag|=(1<<i); else data_for_slave6.flag&=~(1<<i);
            }
            if (fire_fl&FIRE_FL_M_SPS3) {
                if (fire_floor1==(5+i)) data_for_slave6.flag|=(1<<(i+4)); else data_for_slave6.flag&=~(1<<(i+4));
            }
        }
        else {
            if (data_from_slave6.status&(1<<i)) {
                if (net_status_counter_6[i]) {
                    if (!sec_tik) net_status_counter_6[i]--;
                }
                else
                {
                    if (!(fire_floor==5+i)) alarm_fl|=0x0001;
                    fire_floor=5+i;
                    if (fire_floor1==0xff) fire_floor1=5+i;
                    fire_fl=FIRE_FL_M_PK3;
                }
            }
            else
            {
                net_status_counter_6[i]=COUNTER_NET_STATUS;
            }
        }
    }

}

void Shpz_6_StopPdz()
{
    net_status_counter_6[0]=COUNTER_NET_STATUS;
    net_status_counter_6[1]=COUNTER_NET_STATUS;
    net_status_counter_6[2]=COUNTER_NET_STATUS;
    for (i=0;i<FLOOR_NUM_6;i++) {
        data_from_slave6.status&=~(1<<i);
    }
}


