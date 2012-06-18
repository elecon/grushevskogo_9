#include "SHPZ_11.h"
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"

extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

uint8_t net_status_counter_11[FLOOR_NUM_11];


extern NET_OUTPUT_STRUCT1 data_from_slave11;
extern NET_INPUT_STRUCT1 data_for_slave11;
//typedef char PROGMEM prog_char_moe;
extern const prog_char dev_name_str[][5] PROGMEM;
#define MSK_NUMER_MOE 2
//extern const prog_char strKPD181[] PROGMEM;
const prog_char strKPD111[]="ÊÏÄ111";
const prog_char strKPD112[]="ÊÏÄ112";
const prog_char strKPD121[]="ÊÏÄ121";
const prog_char strKPD122[]="ÊÏÄ122";
const prog_char strPP11[]="ÏÏ11";
const prog_char strPP12[]="ÏÏ12";
const prog_char strZOV11[]="ÇÎÂ11";
const prog_char strZOV12[]="ÇÎÂ12";
const prog_char strVZK11[]="ÂÇÊ11";
const prog_char strVZK12[]="ÂÇÊ12";
;
//MOE <76,MSK_NUMER_MOE,2,OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,dev_name_str_moe> GR4;
MOE_NET <22+80*8,strKPD111,&data_from_slave11,&data_for_slave11,0,NET_WORK_SHPZ11> KPD111;
MOE_NET <62+80*9,strKPD112,&data_from_slave11,&data_for_slave11,1,NET_WORK_SHPZ11> KPD112;
KOGT_NET <20+80*8,strPP11,&data_from_slave11,&data_for_slave11,2,NET_WORK_SHPZ11> PP11;
ZOVT_NET <19+80*8,strZOV11,&data_from_slave11,&data_for_slave11,3,NET_WORK_SHPZ11> ZOV11;
KOGT_NET <0+80*0,strVZK11,&data_from_slave11,&data_for_slave11,4,NET_WORK_SHPZ11> VZK11;

MOE_NET <38+80*8,strKPD121,&data_from_slave11,&data_for_slave11,5,NET_WORK_SHPZ11> KPD121;
MOE_NET <78+80*9,strKPD122,&data_from_slave11,&data_for_slave11,6,NET_WORK_SHPZ11> KPD122;
KOGT_NET <36+80*8,strPP12,&data_from_slave11,&data_for_slave11,7,NET_WORK_SHPZ11> PP12;
ZOVT_NET <35+80*8,strZOV12,&data_from_slave11,&data_for_slave11,8,NET_WORK_SHPZ11> ZOV12;
KOGT_NET <0+80*0,strVZK12,&data_from_slave11,&data_for_slave11,9,NET_WORK_SHPZ11> VZK12;



TDevObject* pDevs_arr_11[]=
{
	&KPD111,
	&KPD112,
	&PP11,
	&ZOV11,
	&VZK11,

	&KPD121,
	&KPD122,
	&PP12,
	&ZOV12,
	&VZK12,

};


uint8_t* VZK_arr_11[]=
{
    (uint8_t*)&mVZK_11_1,
    (uint8_t*)&mVZK_11_2,
    (uint8_t*)&mVZK_11_3,
    (uint8_t*)&mVZK_11_4,
    (uint8_t*)&mVZK_11_5,

    (uint8_t*)&mVZK_11_6,

    (uint8_t*)&mVZK_12_1,
    (uint8_t*)&mVZK_12_2,
    (uint8_t*)&mVZK_12_3,
    (uint8_t*)&mVZK_12_4,
    (uint8_t*)&mVZK_12_5,

    (uint8_t*)&mVZK_12_6,
    (uint8_t*)&mVZK_12_7,
    (uint8_t*)&mVZK_12_8,
    (uint8_t*)&mVZK_12_9,
    (uint8_t*)&mVZK_12_10,
};

extern uint16_t i;
void Shpz_11_Ind()
{

     if (net_fl&(1<<NET_WORK_SHPZ11)) {
        for (i=0;i<16;i++) {
             *VZK_arr_11[i]=null_lamp;
             //*VZK_arr_11[i+28]=null_lamp;
        }
    }
    else {
        for (i=0;i<6;i++) {
            if (VZK11.stan&KOGT_OP) {
                if (data_from_slave11.VZK_FL1[0]&(1<<i)) *VZK_arr_11[i]=red_lamp; else *VZK_arr_11[i]=red_b_lamp;
            }
            else {
                if (data_from_slave11.VZK_FL1[0]&(1<<i)) *VZK_arr_11[i]=green_b_lamp; else *VZK_arr_11[i]=green_lamp;
            }
        }

        for (i=6;i<16;i++) {
            if (VZK12.stan&KOGT_OP) {
                if (data_from_slave11.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_11[i]=red_lamp; else *VZK_arr_11[i]=red_b_lamp;
            }
            else {
                if (data_from_slave11.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_11[i]=green_b_lamp; else *VZK_arr_11[i]=green_lamp;
            }
        }
    }
}

void Shpz_11_Work()
{
    for (i=0;i<FLOOR_NUM_11;i++) {
        if (fire_fl&(FIRE_FL_M_PK3|FIRE_FL_M_SPS3)){
            if (fire_fl&FIRE_FL_M_PK3) {
                if (fire_floor2==(11+i)) data_for_slave11.flag|=(1<<i); else data_for_slave11.flag&=~(1<<i);
            }
            if (fire_fl&FIRE_FL_M_SPS3) {
                if (fire_floor2==(11+i)) data_for_slave11.flag|=(1<<(i+4)); else data_for_slave11.flag&=~(1<<(i+4));
            }
        }
        else {
            if (data_from_slave11.status&(1<<i)) {
                if (net_status_counter_11[i]) {
                    if (!sec_tik) net_status_counter_11[i]--;
                }
                else
                {
                    if (!(fire_floor==11+i)) alarm_fl|=0x0001;
                    fire_floor=11+i;
                    if (fire_floor2==0xff) fire_floor2=11+i;
                    fire_fl=FIRE_FL_M_PK3;
                }
            }
            else
            {
                net_status_counter_11[i]=COUNTER_NET_STATUS;
            }
        }
    }

}

void Shpz_11_StopPdz()
{
    net_status_counter_11[0]=COUNTER_NET_STATUS;
    net_status_counter_11[1]=COUNTER_NET_STATUS;
    for (i=0;i<FLOOR_NUM_11;i++) {
        data_from_slave11.status&=~(1<<i);
    }
}
