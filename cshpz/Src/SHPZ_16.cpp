#include "SHPZ_16.h"
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"


extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

uint8_t net_status_counter_16[FLOOR_NUM_16];

extern NET_OUTPUT_STRUCT1 data_from_slave16;
extern NET_INPUT_STRUCT1 data_for_slave16;
//extern const prog_char strKPD181[] PROGMEM;

const prog_char strKPD161[]="ÊÏÄ161";
const prog_char strKPD162[]="ÊÏÄ162";
const prog_char strKPD171[]="ÊÏÄ171";
const prog_char strKPD172[]="ÊÏÄ172";
const prog_char strPP216[]="ÏÏ216";
const prog_char strPP217[]="ÏÏ217";
const prog_char strZOV16[]="ÇÎÂ16";
const prog_char strZOV17[]="ÇÎÂ17";
const prog_char strDVR16[]="ÄÂÐ16";
const prog_char strVZK161[]="ÂÇÊ161";
const prog_char strVZK162[]="ÂÇÊ162";
const prog_char strVZK163[]="ÂÇÊ163";
const prog_char strVZK171[]="ÂÇÊ171";
const prog_char strVZK172[]="ÂÇÊ172";
const prog_char strVZK173[]="ÂÇÊ173";
//MOE <76,MSK_NUMER_MOE,2,OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,dev_name_str_moe> GR4;
MOE_NET <23+80*4,strKPD161,&data_from_slave16,&data_for_slave16,0,NET_WORK_SHPZ16> KPD161;
MOE_NET <61+80*5,strKPD162,&data_from_slave16,&data_for_slave16,1,NET_WORK_SHPZ16> KPD162;
KOGT_NET <28+80*4,strPP216,&data_from_slave16,&data_for_slave16,2,NET_WORK_SHPZ16> PP216;
ZOVT_NET <27+80*4,strZOV16,&data_from_slave16,&data_for_slave16,3,NET_WORK_SHPZ16> ZOV16;
KOGT_NET <0+80*0,strVZK161,&data_from_slave16,&data_for_slave16,4,NET_WORK_SHPZ16> VZK161;
KOGT_NET <0+80*0,strVZK162,&data_from_slave16,&data_for_slave16,5,NET_WORK_SHPZ16> VZK162;
KOGT_NET <0+80*0,strVZK163,&data_from_slave16,&data_for_slave16,6,NET_WORK_SHPZ16> VZK163;


MOE_NET <39+80*4,strKPD171,&data_from_slave16,&data_for_slave16,7,NET_WORK_SHPZ16> KPD171;
MOE_NET <77+80*5,strKPD172,&data_from_slave16,&data_for_slave16,8,NET_WORK_SHPZ16> KPD172;
KOGT_NET <36+80*4,strPP217,&data_from_slave16,&data_for_slave16,9,NET_WORK_SHPZ16> PP217;
ZOVT_NET <35+80*4,strZOV17,&data_from_slave16,&data_for_slave16,10,NET_WORK_SHPZ16> ZOV17;
KOGT_NET <0+80*0,strVZK171,&data_from_slave16,&data_for_slave16,11,NET_WORK_SHPZ16> VZK171;
KOGT_NET <0+80*0,strVZK172,&data_from_slave16,&data_for_slave16,12,NET_WORK_SHPZ16> VZK172;
KOGT_NET <0+80*0,strVZK173,&data_from_slave16,&data_for_slave16,13,NET_WORK_SHPZ16> VZK173;
KOGT_NET <18+80*4,strDVR16,&data_from_slave16,&data_for_slave16,14,NET_WORK_SHPZ16> DVR16;


TDevObject* pDevs_arr_16[]=
{
	&KPD161,
	&KPD162,
	&PP216,
	&ZOV16,
	&VZK161,

	&VZK162,
	&VZK163,
	&KPD171,
	&KPD172,
	&PP217,

	&ZOV17,
	&VZK171,
	&VZK172,
	&VZK173,
	&DVR16,
};

uint8_t* VZK_arr_16[]=
{
    (uint8_t*)&mVZK_16_1,
    (uint8_t*)&mVZK_16_2,
    (uint8_t*)&mVZK_16_3,
    (uint8_t*)&mVZK_16_4,
    (uint8_t*)&mVZK_16_5,

    (uint8_t*)&mVZK_16_6,
    (uint8_t*)&mVZK_16_7,
    (uint8_t*)&mVZK_16_8,
    (uint8_t*)&mVZK_16_9,
    (uint8_t*)&mVZK_16_10,

    (uint8_t*)&mVZK_16_11,
    (uint8_t*)&mVZK_16_12,
    (uint8_t*)&mVZK_16_13,
    (uint8_t*)&mVZK_16_14,
    (uint8_t*)&mVZK_16_15,

    (uint8_t*)&mVZK_16_16,
    (uint8_t*)&mVZK_16_17,
    (uint8_t*)&mVZK_16_18,
    (uint8_t*)&mVZK_16_19,
    (uint8_t*)&mVZK_16_20,

    (uint8_t*)&mVZK_16_21,
    (uint8_t*)&mVZK_16_22,
    (uint8_t*)&mVZK_16_23,
    (uint8_t*)&mVZK_16_24,
    (uint8_t*)&mVZK_16_25,

    (uint8_t*)&mVZK_16_26,
    (uint8_t*)&mVZK_16_27,
    (uint8_t*)&mVZK_16_28,
    (uint8_t*)&mVZK_17_1,
    (uint8_t*)&mVZK_17_2,
    (uint8_t*)&mVZK_17_3,
    (uint8_t*)&mVZK_17_4,
    (uint8_t*)&mVZK_17_5,

    (uint8_t*)&mVZK_17_6,
    (uint8_t*)&mVZK_17_7,
    (uint8_t*)&mVZK_17_8,
    (uint8_t*)&mVZK_17_9,
    (uint8_t*)&mVZK_17_10,

    (uint8_t*)&mVZK_17_11,
    (uint8_t*)&mVZK_17_12,
    (uint8_t*)&mVZK_17_13,
    (uint8_t*)&mVZK_17_14,
    (uint8_t*)&mVZK_17_15,

    (uint8_t*)&mVZK_17_16,
    (uint8_t*)&mVZK_17_17,
    (uint8_t*)&mVZK_17_18,
    (uint8_t*)&mVZK_17_19,
    (uint8_t*)&mVZK_17_20,

    (uint8_t*)&mVZK_17_21,
    (uint8_t*)&mVZK_17_22,
    (uint8_t*)&mVZK_17_23,
    (uint8_t*)&mVZK_17_24,
    (uint8_t*)&mVZK_17_25,

    (uint8_t*)&mVZK_17_26,
    (uint8_t*)&mVZK_17_27,
    (uint8_t*)&mVZK_17_28,
};

extern uint16_t i;
void Shpz_16_Ind()
{

     if (net_fl&(1<<NET_WORK_SHPZ16)) {
        for (i=0;i<28;i++) {
             *VZK_arr_16[i]=null_lamp;
             *VZK_arr_16[i+28]=null_lamp;
        }
    }
    else {
        for (i=0;i<5;i++) {
            if (VZK161.stan&KOGT_OP) {
                if (data_from_slave16.VZK_FL1[0]&(1<<i)) *VZK_arr_16[i]=red_lamp; else *VZK_arr_16[i]=red_b_lamp;
            }
            else {
                if (data_from_slave16.VZK_FL1[0]&(1<<i)) *VZK_arr_16[i]=green_b_lamp; else *VZK_arr_16[i]=green_lamp;
            }
        }

        for (i=5;i<18;i++) {
            if (VZK162.stan&KOGT_OP) {
                if (data_from_slave16.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_16[i]=red_lamp; else *VZK_arr_16[i]=red_b_lamp;
            }
            else {
                if (data_from_slave16.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_16[i]=green_b_lamp; else *VZK_arr_16[i]=green_lamp;
            }
        }

        for (i=18;i<28;i++) {
            if (VZK163.stan&KOGT_OP) {
                if (data_from_slave16.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_16[i]=red_lamp; else *VZK_arr_16[i]=red_b_lamp;
            }
            else {
                if (data_from_slave16.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_16[i]=green_b_lamp; else *VZK_arr_16[i]=green_lamp;
            }
        }

        for (i=0;i<5;i++) {
            if (VZK171.stan&KOGT_OP) {
                if (data_from_slave16.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_16[i+28]=red_lamp; else *VZK_arr_16[i+28]=red_b_lamp;
            }
            else {
                if (data_from_slave16.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_16[i+28]=green_b_lamp; else *VZK_arr_16[i+28]=green_lamp;
            }
        }

        for (i=5;i<15;i++) {
            if (VZK172.stan&KOGT_OP) {
                if (data_from_slave16.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_16[i+28]=red_lamp; else *VZK_arr_16[i+28]=red_b_lamp;
            }
            else {
                if (data_from_slave16.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_16[i+28]=green_b_lamp; else *VZK_arr_16[i+28]=green_lamp;
            }
        }

        for (i=15;i<28;i++) {
            if (VZK173.stan&KOGT_OP) {
                if (data_from_slave16.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_16[i+28]=red_lamp; else *VZK_arr_16[i+28]=red_b_lamp;
            }
            else {
                if (data_from_slave16.VZK_FL2[i/8]&(1<<(i%8))) *VZK_arr_16[i+28]=green_b_lamp; else *VZK_arr_16[i+28]=green_lamp;
            }
        }
    }
}

void Shpz_16_Work()
{
    for (i=0;i<FLOOR_NUM_16;i++) {
        if (fire_fl&(FIRE_FL_M_PK3|FIRE_FL_M_SPS3)){
            if (fire_fl&FIRE_FL_M_PK3) {
                if (fire_floor3==(16+i)) data_for_slave16.flag|=(1<<i); else data_for_slave16.flag&=~(1<<i);
            }
            if (fire_fl&FIRE_FL_M_SPS3) {
                if (fire_floor3==(16+i)) data_for_slave16.flag|=(1<<(i+4)); else data_for_slave16.flag&=~(1<<(i+4));
            }
        }
        else {
            if (data_from_slave16.status&(1<<i)) {
                if (net_status_counter_16[i]) {
                    if (!sec_tik) net_status_counter_16[i]--;
                }
                else
                {
                    if (!(fire_floor==16+i)) alarm_fl|=0x0001;
                    fire_floor=16+i;
                    if (fire_floor3==0xff) fire_floor3=16+i;
                    fire_fl=FIRE_FL_M_PK3;
                }
            }
            else
            {
                net_status_counter_16[i]=COUNTER_NET_STATUS;
            }
        }
    }

}

void Shpz_16_StopPdz()
{
    net_status_counter_16[0]=COUNTER_NET_STATUS;
    net_status_counter_16[1]=COUNTER_NET_STATUS;
    for (i=0;i<FLOOR_NUM_16;i++) {
        data_from_slave16.status&=~(1<<i);
    }
}
