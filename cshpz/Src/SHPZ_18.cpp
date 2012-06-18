#include "SHPZ_18.h"
//#include <avr/delay.h>
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"

extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

uint8_t net_status_counter_18[FLOOR_NUM_18];


extern NET_OUTPUT_STRUCT1 data_from_slave18;
extern NET_INPUT_STRUCT1 data_for_slave18;
//typedef char PROGMEM prog_char_moe;
extern const prog_char dev_name_str[][5] PROGMEM;
#define MSK_NUMER_MOE 2
//extern const prog_char strKPD181[] PROGMEM;
const prog_char strKPD181[]="ÊÏÄ181";
const prog_char strKPD182[]="ÊÏÄ182";
const prog_char strKPD191[]="ÊÏÄ191";
const prog_char strKPD192[]="ÊÏÄ192";
const prog_char strPP218[]="ÏÏ218";
const prog_char strPP219[]="ÏÏ219";
const prog_char strZOV18[]="ÇÎÂ18";
const prog_char strZOV19[]="ÇÎÂ19";
const prog_char strDVR[]="ÄÂÐ";
const prog_char strVZK181[]="ÂÇÊ1";
const prog_char strVZK182[]="ÂÇÊ2";
const prog_char strVZK183[]="ÂÇÊ3";
const prog_char strVZK191[]="ÂÇÊ4";
const prog_char strVZK192[]="ÂÇÊ5";
const prog_char strVZK193[]="ÂÇÊ6";
//MOE <76,MSK_NUMER_MOE,2,OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,dev_name_str_moe> GR4;
MOE_NET <23+80*2,strKPD181,&data_from_slave18,&data_for_slave18,0,NET_WORK_SHPZ18> KPD181;
MOE_NET <61+80*3,strKPD182,&data_from_slave18,&data_for_slave18,1,NET_WORK_SHPZ18> KPD182;
KOGT_NET <28+80*2,strPP218,&data_from_slave18,&data_for_slave18,2,NET_WORK_SHPZ18> PP218;
ZOVT_NET <27+80*2,strZOV18,&data_from_slave18,&data_for_slave18,3,NET_WORK_SHPZ18> ZOV18;
KOGT_NET <0+80*0,strVZK181,&data_from_slave18,&data_for_slave18,4,NET_WORK_SHPZ18> VZK181;
KOGT_NET <0+80*0,strVZK182,&data_from_slave18,&data_for_slave18,5,NET_WORK_SHPZ18> VZK182;
KOGT_NET <0+80*0,strVZK183,&data_from_slave18,&data_for_slave18,6,NET_WORK_SHPZ18> VZK183;


MOE_NET <39+80*2,strKPD191,&data_from_slave18,&data_for_slave18,7,NET_WORK_SHPZ18> KPD191;
MOE_NET <77+80*3,strKPD192,&data_from_slave18,&data_for_slave18,8,NET_WORK_SHPZ18> KPD192;
KOGT_NET <36+80*2,strPP219,&data_from_slave18,&data_for_slave18,9,NET_WORK_SHPZ18> PP219;
ZOVT_NET <35+80*2,strZOV19,&data_from_slave18,&data_for_slave18,10,NET_WORK_SHPZ18> ZOV19;
KOGT_NET <0+80*0,strVZK191,&data_from_slave18,&data_for_slave18,11,NET_WORK_SHPZ18> VZK191;
KOGT_NET <0+80*0,strVZK192,&data_from_slave18,&data_for_slave18,12,NET_WORK_SHPZ18> VZK192;
KOGT_NET <0+80*0,strVZK193,&data_from_slave18,&data_for_slave18,13,NET_WORK_SHPZ18> VZK193;
KOGT_NET <18+80*2,strDVR,&data_from_slave18,&data_for_slave18,14,NET_WORK_SHPZ18> DVR;


TDevObject* pDevs_arr_18[]=
{
	&KPD181,
	&KPD182,
	&PP218,
	&ZOV18,
	&VZK181,

	&VZK182,
	&VZK183,
	&KPD191,
	&KPD192,
	&PP219,

	&ZOV19,
	&VZK191,
	&VZK192,
	&VZK193,
	&DVR,
};


uint8_t* VZK_arr_18[]=
{
    (uint8_t*)&mVZK_18_1,
    (uint8_t*)&mVZK_18_2,
    (uint8_t*)&mVZK_18_3,
    (uint8_t*)&mVZK_18_4,
    (uint8_t*)&mVZK_18_5,

    (uint8_t*)&mVZK_18_6,
    (uint8_t*)&mVZK_18_7,
    (uint8_t*)&mVZK_18_8,
    (uint8_t*)&mVZK_18_9,
    (uint8_t*)&mVZK_18_10,

    (uint8_t*)&mVZK_18_11,
    (uint8_t*)&mVZK_18_12,
    (uint8_t*)&mVZK_18_13,
    (uint8_t*)&mVZK_18_14,
    (uint8_t*)&mVZK_18_15,

    (uint8_t*)&mVZK_18_16,
    (uint8_t*)&mVZK_18_17,
    (uint8_t*)&mVZK_18_18,
    (uint8_t*)&mVZK_18_19,
    (uint8_t*)&mVZK_18_20,

    (uint8_t*)&mVZK_18_21,
    (uint8_t*)&mVZK_18_22,
    (uint8_t*)&mVZK_18_23,
    (uint8_t*)&mVZK_18_24,
    (uint8_t*)&mVZK_18_25,

    (uint8_t*)&mVZK_18_26,
    (uint8_t*)&mVZK_18_27,
    (uint8_t*)&mVZK_18_28,
    (uint8_t*)&mVZK_19_1,
    (uint8_t*)&mVZK_19_2,
    (uint8_t*)&mVZK_19_3,
    (uint8_t*)&mVZK_19_4,
    (uint8_t*)&mVZK_19_5,

    (uint8_t*)&mVZK_19_6,
    (uint8_t*)&mVZK_19_7,
    (uint8_t*)&mVZK_19_8,
    (uint8_t*)&mVZK_19_9,
    (uint8_t*)&mVZK_19_10,

    (uint8_t*)&mVZK_19_11,
    (uint8_t*)&mVZK_19_12,
    (uint8_t*)&mVZK_19_13,
    (uint8_t*)&mVZK_19_14,
    (uint8_t*)&mVZK_19_15,

    (uint8_t*)&mVZK_19_16,
    (uint8_t*)&mVZK_19_17,
    (uint8_t*)&mVZK_19_18,
    (uint8_t*)&mVZK_19_19,
    (uint8_t*)&mVZK_19_20,

    (uint8_t*)&mVZK_19_21,
    (uint8_t*)&mVZK_19_22,
    (uint8_t*)&mVZK_19_23,
    (uint8_t*)&mVZK_19_24,
    (uint8_t*)&mVZK_19_25,

    (uint8_t*)&mVZK_19_26,
    (uint8_t*)&mVZK_19_27,
    (uint8_t*)&mVZK_19_28,
};

extern uint16_t i;
void Shpz_18_Ind()
{

     if (net_fl&(1<<NET_WORK_SHPZ18)) {
        for (i=0;i<28;i++) {
             *VZK_arr_18[i]=null_lamp;
             *VZK_arr_18[i+28]=null_lamp;
        }
    }
    else {
        for (i=0;i<5;i++) {
            if (VZK181.stan&KOGT_OP) {
                if (data_from_slave18.VZK_FL1[0]&(1<<i)) *VZK_arr_18[i]=red_lamp; else *VZK_arr_18[i]=red_b_lamp;
            }
            else {
                if (data_from_slave18.VZK_FL1[0]&(1<<i)) *VZK_arr_18[i]=green_b_lamp; else *VZK_arr_18[i]=green_lamp;
            }
        }

        for (i=5;i<18;i++) {
            if (VZK182.stan&KOGT_OP) {
                if (data_from_slave18.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_18[i]=red_lamp; else *VZK_arr_18[i]=red_b_lamp;
            }
            else {
                if (data_from_slave18.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_18[i]=green_b_lamp; else *VZK_arr_18[i]=green_lamp;
            }
        }

        for (i=18;i<28;i++) {
            if (VZK183.stan&KOGT_OP) {
                if (data_from_slave18.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_18[i]=red_lamp; else *VZK_arr_18[i]=red_b_lamp;
            }
            else {
                if (data_from_slave18.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_18[i]=green_b_lamp; else *VZK_arr_18[i]=green_lamp;
            }
        }

        for (i=0;i<5;i++) {
            if (VZK191.stan&KOGT_OP) {
                if (data_from_slave18.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_18[i+28]=red_lamp; else *VZK_arr_18[i+28]=red_b_lamp;
            }
            else {
                if (data_from_slave18.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_18[i+28]=green_b_lamp; else *VZK_arr_18[i+28]=green_lamp;
            }
        }

        for (i=5;i<15;i++) {
            if (VZK192.stan&KOGT_OP) {
                if (data_from_slave18.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_18[i+28]=red_lamp; else *VZK_arr_18[i+28]=red_b_lamp;
            }
            else {
                if (data_from_slave18.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_18[i+28]=green_b_lamp; else *VZK_arr_18[i+28]=green_lamp;
            }
        }

        for (i=15;i<28;i++) {
            if (VZK193.stan&KOGT_OP) {
                if (data_from_slave18.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_18[i+28]=red_lamp; else *VZK_arr_18[i+28]=red_b_lamp;
            }
            else {
                if (data_from_slave18.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_18[i+28]=green_b_lamp; else *VZK_arr_18[i+28]=green_lamp;
            }
        }
    }

}

void Shpz_18_Work()
{
    for (i=0;i<FLOOR_NUM_18;i++) {
        if (fire_fl&(FIRE_FL_M_PK3|FIRE_FL_M_SPS3)){
            if (fire_fl&FIRE_FL_M_PK3) {
                if (fire_floor3==(18+i)) data_for_slave18.flag|=(1<<i); else data_for_slave18.flag&=~(1<<i);
            }
            if (fire_fl&FIRE_FL_M_SPS3) {
                if (fire_floor3==(18+i)) data_for_slave18.flag|=(1<<(i+4)); else data_for_slave18.flag&=~(1<<(i+4));
            }
        }
        else {
            if (data_from_slave18.status&(1<<i)) {
                if (net_status_counter_18[i]) {
                    if (!sec_tik) net_status_counter_18[i]--;
                }
                else
                {
                    if (!(fire_floor==18+i)) alarm_fl|=0x0001;
                    fire_floor=18+i;
                    if (fire_floor3==0xff) fire_floor3=18+i;
                    fire_fl=FIRE_FL_M_PK3;
                }
            }
            else
            {
                net_status_counter_18[i]=COUNTER_NET_STATUS;
            }
        }
    }

}

void Shpz_18_StopPdz()
{
    net_status_counter_18[0]=COUNTER_NET_STATUS;
    net_status_counter_18[1]=COUNTER_NET_STATUS;
    for (i=0;i<FLOOR_NUM_18;i++) {
        data_from_slave18.status&=~(1<<i);
    }
}
