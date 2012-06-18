#include "SHPZ_9.h"
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"

extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

uint8_t net_status_counter_9[FLOOR_NUM_9];

extern NET_OUTPUT_STRUCT1 data_from_slave9;
extern NET_INPUT_STRUCT1 data_for_slave9;
//extern const prog_char strKPD181[] PROGMEM;

const prog_char strKPD81[]="ÊÏÄ81";
const prog_char strKPD82[]="ÊÏÄ82";
const prog_char strKPD91[]="ÊÏÄ91";
const prog_char strKPD92[]="ÊÏÄ92";
const prog_char strKPD101[]="ÊÏÄ101";
const prog_char strKPD102[]="ÊÏÄ102";
const prog_char strPP8[]="ÏÏ8";
const prog_char strPP9[]="ÏÏ9";
const prog_char strPP10[]="ÏÏ10";
const prog_char strZOV8[]="ÇÎÂ8";
const prog_char strZOV9[]="ÇÎÂ9";
const prog_char strZOV10[]="ÇÎÂ10";
const prog_char strVZK8[]="ÂÇÊ8";
const prog_char strVZK9[]="ÂÇÊ9";
const prog_char strVZK10[]="ÂÇÊ10";

//MOE <76,MSK_NUMER_MOE,2,OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,dev_name_str_moe> GR4;
MOE_NET <14+80*10,strKPD81,&data_from_slave9,&data_for_slave9,0,NET_WORK_SHPZ9> KPD81;
MOE_NET <54+80*11,strKPD82,&data_from_slave9,&data_for_slave9,1,NET_WORK_SHPZ9> KPD82;
KOGT_NET<12+80*10,strPP8,&data_from_slave9,&data_for_slave9,2,NET_WORK_SHPZ9> PP8;
ZOVT_NET<11+80*10,strZOV8,&data_from_slave9,&data_for_slave9,3,NET_WORK_SHPZ9> ZOV8;
KOGT_NET <0+80*0,strVZK8,&data_from_slave9,&data_for_slave9,4,NET_WORK_SHPZ9> VZK8;

MOE_NET <30+80*10,strKPD91,&data_from_slave9,&data_for_slave9,5,NET_WORK_SHPZ9> KPD91;
MOE_NET <70+80*11,strKPD92,&data_from_slave9,&data_for_slave9,6,NET_WORK_SHPZ9> KPD92;
KOGT_NET <28+80*10,strPP9,&data_from_slave9,&data_for_slave9,7,NET_WORK_SHPZ9> PP9;
ZOVT_NET <27+80*10,strZOV9,&data_from_slave9,&data_for_slave9,8,NET_WORK_SHPZ9> ZOV9;
KOGT_NET <0+80*0,strVZK9,&data_from_slave9,&data_for_slave9,9,NET_WORK_SHPZ9> VZK9;

MOE_NET < 6+80*8,strKPD101,&data_from_slave9,&data_for_slave9,10,NET_WORK_SHPZ9> KPD101;
MOE_NET <46+80*9,strKPD102,&data_from_slave9,&data_for_slave9,11,NET_WORK_SHPZ9> KPD102;
KOGT_NET <4+80*8,strPP10,&data_from_slave9,&data_for_slave9,12,NET_WORK_SHPZ9> PP10;
ZOVT_NET <3+80*8,strZOV10,&data_from_slave9,&data_for_slave9,13,NET_WORK_SHPZ9> ZOV10;
KOGT_NET <0+80*0,strVZK10,&data_from_slave9,&data_for_slave9,14,NET_WORK_SHPZ9> VZK10;

TDevObject* pDevs_arr_9[]=
{
	&KPD81,
	&KPD82,
	&PP8,
	&ZOV8,
	&VZK8,

	&KPD91,
	&KPD92,
	&PP9,
	&ZOV9,
	&VZK9,

    &KPD101,
	&KPD102,
	&PP10,
	&ZOV10,
	&VZK10,
};

uint8_t* VZK_arr_9[]=
{
    (uint8_t*)&mVZK_8_1,
    (uint8_t*)&mVZK_8_2,
    (uint8_t*)&mVZK_8_3,
    (uint8_t*)&mVZK_8_4,
    (uint8_t*)&mVZK_8_5,

    (uint8_t*)&mVZK_8_6,
    (uint8_t*)&mVZK_8_7,
    (uint8_t*)&mVZK_8_8,
    (uint8_t*)&mVZK_8_9,
    (uint8_t*)&mVZK_8_10,

    (uint8_t*)&mVZK_8_11,

    (uint8_t*)&mVZK_9_1,
    (uint8_t*)&mVZK_9_2,
    (uint8_t*)&mVZK_9_3,
    (uint8_t*)&mVZK_9_4,
    (uint8_t*)&mVZK_9_5,

    (uint8_t*)&mVZK_9_6,
    (uint8_t*)&mVZK_9_7,
    (uint8_t*)&mVZK_9_8,
    (uint8_t*)&mVZK_9_9,
    (uint8_t*)&mVZK_9_10,

    (uint8_t*)&mVZK_9_11,
    (uint8_t*)&mVZK_9_12,


    (uint8_t*)&mVZK_10_1,
    (uint8_t*)&mVZK_10_2,
    (uint8_t*)&mVZK_10_3,
    (uint8_t*)&mVZK_10_4,
    (uint8_t*)&mVZK_10_5,

    (uint8_t*)&mVZK_10_6,
    (uint8_t*)&mVZK_10_7,
};

extern uint16_t i;
void Shpz_9_Ind()
{

     if (net_fl&(1<<NET_WORK_SHPZ9)) {
        for (i=0;i<30;i++) {
             *VZK_arr_9[i]=null_lamp;
        }
    }
    else {
        for (i=0;i<11;i++) {
            if (VZK8.stan&KOGT_OP) {
                if (data_from_slave9.VZK_FL1[0]&(1<<i)) *VZK_arr_9[i]=red_lamp; else *VZK_arr_9[i]=red_b_lamp;
            }
            else {
                if (data_from_slave9.VZK_FL1[0]&(1<<i)) *VZK_arr_9[i]=green_b_lamp; else *VZK_arr_9[i]=green_lamp;
            }
        }

        for (i=11;i<23;i++) {
            if (VZK9.stan&KOGT_OP) {
                if (data_from_slave9.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_9[i]=red_lamp; else *VZK_arr_9[i]=red_b_lamp;
            }
            else {
                if (data_from_slave9.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_9[i]=green_b_lamp; else *VZK_arr_9[i]=green_lamp;
            }
        }

        for (i=23;i<30;i++) {
            if (VZK10.stan&KOGT_OP) {
                if (data_from_slave9.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_9[i]=red_lamp; else *VZK_arr_9[i]=red_b_lamp;
            }
            else {
                if (data_from_slave9.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_9[i]=green_b_lamp; else *VZK_arr_9[i]=green_lamp;
            }
        }
    }
}

void Shpz_9_Work()
{
    for (i=0;i<FLOOR_NUM_9;i++) {
        if (fire_fl&(FIRE_FL_M_PK3|FIRE_FL_M_SPS3)){
            if (fire_fl&FIRE_FL_M_PK3) {
                if (fire_floor2==(8+i)) data_for_slave9.flag|=(1<<i); else data_for_slave9.flag&=~(1<<i);
            }
            if (fire_fl&FIRE_FL_M_SPS3) {
                if (fire_floor2==(8+i)) data_for_slave9.flag|=(1<<(i+4)); else data_for_slave9.flag&=~(1<<(i+4));
            }
        }
        else {
            if (data_from_slave9.status&(1<<i)) {
                if (net_status_counter_9[i]) {
                    if (!sec_tik) net_status_counter_9[i]--;
                }
                else
                {
                    if (!(fire_floor==8+i)) alarm_fl|=0x0001;
                    fire_floor=8+i;
                    if (fire_floor2==0xff) fire_floor2=8+i;
                    fire_fl=FIRE_FL_M_PK3;
                }
            }
            else
            {
                net_status_counter_9[i]=COUNTER_NET_STATUS;
            }
        }
    }

}

void Shpz_9_StopPdz()
{
    net_status_counter_9[0]=COUNTER_NET_STATUS;
    net_status_counter_9[1]=COUNTER_NET_STATUS;
    net_status_counter_9[2]=COUNTER_NET_STATUS;
    for (i=0;i<FLOOR_NUM_9;i++) {
        data_from_slave9.status&=~(1<<i);
    }
}

