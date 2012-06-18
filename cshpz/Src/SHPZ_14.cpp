#include "SHPZ_14.h"

#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"

extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

uint8_t net_status_counter_14[FLOOR_NUM_14];

extern NET_OUTPUT_STRUCT1 data_from_slave14;
extern NET_INPUT_STRUCT1 data_for_slave14;
//extern const prog_char strKPD181[] PROGMEM;

const prog_char strKPD131[]="ÊÏÄ131";
const prog_char strKPD132[]="ÊÏÄ132";
const prog_char strKPD141[]="ÊÏÄ141";
const prog_char strKPD142[]="ÊÏÄ142";
const prog_char strKPD151[]="ÊÏÄ151";
const prog_char strKPD152[]="ÊÏÄ152";
const prog_char strPP13[]="ÏÏ13";
const prog_char strPP14[]="ÏÏ14";
const prog_char strPP15[]="ÏÏ15";
const prog_char strZOV13[]="ÇÎÂ13";
const prog_char strZOV14[]="ÇÎÂ14";
const prog_char strZOV15[]="ÇÎÂ15";
const prog_char strVZK13[]="ÂÇÊ13";
const prog_char strVZK14[]="ÂÇÊ14";
const prog_char strVZK15[]="ÂÇÊ15";

//MOE <76,MSK_NUMER_MOE,2,OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,dev_name_str_moe> GR4;
MOE_NET <14+80*6,strKPD131,&data_from_slave14,&data_for_slave14,0,NET_WORK_SHPZ14> KPD131;
MOE_NET <54+80*7,strKPD132,&data_from_slave14,&data_for_slave14,1,NET_WORK_SHPZ14> KPD132;
KOGT_NET<12+80*6,strPP13,&data_from_slave14,&data_for_slave14,2,NET_WORK_SHPZ14> PP13;
ZOVT_NET <11+80*6,strZOV13,&data_from_slave14,&data_for_slave14,3,NET_WORK_SHPZ14> ZOV13;
KOGT_NET <0+80*0,strVZK13,&data_from_slave14,&data_for_slave14,4,NET_WORK_SHPZ14> VZK13;

MOE_NET <30+80*6,strKPD141,&data_from_slave14,&data_for_slave14,5,NET_WORK_SHPZ14> KPD141;
MOE_NET <70+80*7,strKPD142,&data_from_slave14,&data_for_slave14,6,NET_WORK_SHPZ14> KPD142;
KOGT_NET <28+80*6,strPP14,&data_from_slave14,&data_for_slave14,7,NET_WORK_SHPZ14> PP14;
ZOVT_NET <27+80*6,strZOV14,&data_from_slave14,&data_for_slave14,8,NET_WORK_SHPZ14> ZOV14;
KOGT_NET <0+80*0,strVZK14,&data_from_slave14,&data_for_slave14,9,NET_WORK_SHPZ14> VZK14;

MOE_NET < 6+80*4,strKPD151,&data_from_slave14,&data_for_slave14,10,NET_WORK_SHPZ14> KPD151;
MOE_NET <46+80*5,strKPD152,&data_from_slave14,&data_for_slave14,11,NET_WORK_SHPZ14> KPD152;
KOGT_NET <4+80*4,strPP15,&data_from_slave14,&data_for_slave14,12,NET_WORK_SHPZ14> PP15;
ZOVT_NET <3+80*4,strZOV15,&data_from_slave14,&data_for_slave14,13,NET_WORK_SHPZ14> ZOV15;
KOGT_NET <0+80*0,strVZK15,&data_from_slave14,&data_for_slave14,14,NET_WORK_SHPZ14> VZK15;

TDevObject* pDevs_arr_14[]=
{
	&KPD131,
	&KPD132,
	&PP13,
	&ZOV13,
	&VZK13,

	&KPD141,
	&KPD142,
	&PP14,
	&ZOV14,
	&VZK14,

    &KPD151,
	&KPD152,
	&PP15,
	&ZOV15,
	&VZK15,
};

uint8_t* VZK_arr_14[]=
{
    (uint8_t*)&mVZK_13_1,
    (uint8_t*)&mVZK_13_2,
    (uint8_t*)&mVZK_13_3,
    (uint8_t*)&mVZK_13_4,
    (uint8_t*)&mVZK_13_5,

    (uint8_t*)&mVZK_13_6,
    (uint8_t*)&mVZK_13_7,
    (uint8_t*)&mVZK_13_8,
    (uint8_t*)&mVZK_13_9,

    (uint8_t*)&mVZK_14_1,
    (uint8_t*)&mVZK_14_2,
    (uint8_t*)&mVZK_14_3,
    (uint8_t*)&mVZK_14_4,
    (uint8_t*)&mVZK_14_5,

    (uint8_t*)&mVZK_14_6,
    (uint8_t*)&mVZK_14_7,

    (uint8_t*)&mVZK_15_1,
    (uint8_t*)&mVZK_15_2,
    (uint8_t*)&mVZK_15_3,
    (uint8_t*)&mVZK_15_4,
    (uint8_t*)&mVZK_15_5,

    (uint8_t*)&mVZK_15_6,
    (uint8_t*)&mVZK_15_7,
    (uint8_t*)&mVZK_15_8,
    (uint8_t*)&mVZK_15_9,
    (uint8_t*)&mVZK_15_10,

    (uint8_t*)&mVZK_15_11,
};

extern uint16_t i;
void Shpz_14_Ind()
{

     if (net_fl&(1<<NET_WORK_SHPZ14)) {
        for (i=0;i<32;i++) {
             *VZK_arr_14[i]=null_lamp;
        }
    }
    else {
        for (i=0;i<9;i++) {
            if (VZK13.stan&KOGT_OP) {
                if (data_from_slave14.VZK_FL1[0]&(1<<i)) *VZK_arr_14[i]=red_lamp; else *VZK_arr_14[i]=red_b_lamp;
            }
            else {
                if (data_from_slave14.VZK_FL1[0]&(1<<i)) *VZK_arr_14[i]=green_b_lamp; else *VZK_arr_14[i]=green_lamp;
            }
        }

        for (i=9;i<16;i++) {
            if (VZK14.stan&KOGT_OP) {
                if (data_from_slave14.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_14[i]=red_lamp; else *VZK_arr_14[i]=red_b_lamp;
            }
            else {
                if (data_from_slave14.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_14[i]=green_b_lamp; else *VZK_arr_14[i]=green_lamp;
            }
        }

        for (i=16;i<27;i++) {
            if (VZK15.stan&KOGT_OP) {
                if (data_from_slave14.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_14[i]=red_lamp; else *VZK_arr_14[i]=red_b_lamp;
            }
            else {
                if (data_from_slave14.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_14[i]=green_b_lamp; else *VZK_arr_14[i]=green_lamp;
            }
        }
    }
}

void Shpz_14_Work()
{
    for (i=0;i<FLOOR_NUM_14;i++) {
        if (fire_fl&(FIRE_FL_M_PK3|FIRE_FL_M_SPS3)){
            if (fire_fl&FIRE_FL_M_PK3) {
                if (fire_floor2==(13+i)) data_for_slave14.flag|=(1<<i); else data_for_slave14.flag&=~(1<<i);
            }
            if (fire_fl&FIRE_FL_M_SPS3) {
                if (fire_floor2==(13+i)) data_for_slave14.flag|=(1<<(i+4)); else data_for_slave14.flag&=~(1<<(i+4));
            }
        }
        else {
            if (data_from_slave14.status&(1<<i)) {
                if (net_status_counter_14[i]) {
                    if (!sec_tik) net_status_counter_14[i]--;
                }
                else
                {
                    if (!(fire_floor==13+i)) alarm_fl|=0x0001;
                    fire_floor=13+i;
                    if (fire_floor2==0xff) fire_floor2=13+i;
                    fire_fl=FIRE_FL_M_PK3;
                }
            }
            else
            {
                net_status_counter_14[i]=COUNTER_NET_STATUS;
            }
        }
    }

}

void Shpz_14_StopPdz()
{
    net_status_counter_14[0]=COUNTER_NET_STATUS;
    net_status_counter_14[1]=COUNTER_NET_STATUS;
    net_status_counter_14[2]=COUNTER_NET_STATUS;
    for (i=0;i<FLOOR_NUM_14;i++) {
        data_from_slave14.status&=~(1<<i);
    }
}

