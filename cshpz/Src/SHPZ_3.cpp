#include "SHPZ_3.h"
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"
#include "../../Devs/Dev_kog_net.h"

extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

uint8_t net_status_counter_3[FLOOR_NUM_3];

extern NET_OUTPUT_STRUCT1 data_from_slave3;
extern NET_INPUT_STRUCT1 data_for_slave3;
//extern const prog_char strKPD181[] PROGMEM;
//uint8_t rrrr=1;
const prog_char strKPD21[]="ÊÏÄ21";
const prog_char strKPD22[]="ÊÏÄ22";
const prog_char strKPD31[]="ÊÏÄ31";
const prog_char strKPD32[]="ÊÏÄ32";
const prog_char strKPD41[]="ÊÏÄ41";
const prog_char strKPD42[]="ÊÏÄ42";
const prog_char strPP2[]="ÏÏ2";
const prog_char strPP3[]="ÏÏ3";
const prog_char strPP4[]="ÏÏ4";
const prog_char strZOV2[]="ÇÎÂ2";
const prog_char strZOV3[]="ÇÎÂ3";
const prog_char strZOV4[]="ÇÎÂ4";
const prog_char strVZK2[]="ÂÇÊ2";
const prog_char strVZK3[]="ÂÇÊ3";
const prog_char strVZK4[]="ÂÇÊ4";

KOG_NET KPD22(strKPD21,
               (uint8_t*)&data_from_slave3.devs_net_stat[0],
               (uint8_t*)&data_for_slave3.devs_net_cmd[0],
               (uint8_t*)&mRRR//,
               //rrrr
               );
//MOE <76,MSK_NUMER_MOE,2,OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,dev_name_str_moe> GR4;
MOE_NET < 5+80*14,strKPD21,&data_from_slave3,&data_for_slave3,0,NET_WORK_SHPZ3> KPD21;
//MOE_NET <47+80*15,strKPD22,&data_from_slave3,&data_for_slave3,1,NET_WORK_SHPZ3> KPD22;
//KOGT_NET<4+80*14,strPP2,&data_from_slave3,&data_for_slave3,2,NET_WORK_SHPZ3> PP2;
//ZOVT_NET <3+80*14,strZOV2,&data_from_slave3,&data_for_slave3,3,NET_WORK_SHPZ3> ZOV2;
//KOGT_NET <0+80*0,strVZK2,&data_from_slave3,&data_for_slave3,4,NET_WORK_SHPZ3> VZK2;
//
//MOE_NET <21+80*14,strKPD31,&data_from_slave3,&data_for_slave3,5,NET_WORK_SHPZ3> KPD31;
//MOE_NET <63+80*15,strKPD32,&data_from_slave3,&data_for_slave3,6,NET_WORK_SHPZ3> KPD32;
//KOGT_NET <20+80*14,strPP3,&data_from_slave3,&data_for_slave3,7,NET_WORK_SHPZ3> PP3;
//ZOVT_NET <19+80*14,strZOV3,&data_from_slave3,&data_for_slave3,8,NET_WORK_SHPZ3> ZOV3;
//KOGT_NET <0+80*0,strVZK3,&data_from_slave3,&data_for_slave3,9,NET_WORK_SHPZ3> VZK3;
//
//MOE_NET <29+80*14,strKPD41,&data_from_slave3,&data_for_slave3,10,NET_WORK_SHPZ3> KPD41;
//MOE_NET <71+80*15,strKPD42,&data_from_slave3,&data_for_slave3,11,NET_WORK_SHPZ3> KPD42;
//KOGT_NET <28+80*14,strPP4,&data_from_slave3,&data_for_slave3,12,NET_WORK_SHPZ3> PP4;
//ZOVT_NET <27+80*14,strZOV4,&data_from_slave3,&data_for_slave3,13,NET_WORK_SHPZ3> ZOV4;
//KOGT_NET <0+80*0,strVZK4,&data_from_slave3,&data_for_slave3,14,NET_WORK_SHPZ3> VZK4;

TDevObject* pDevs_arr_3[]=
{
	&KPD21,
//	&KPD22,
//	&PP2,
//	&ZOV2,
//	&VZK2,
//
//	&KPD31,
//	&KPD32,
//	&PP3,
//	&ZOV3,
//	&VZK3,
//
//    &KPD41,
//	&KPD42,
//	&PP4,
//	&ZOV4,
//	&VZK4,
};

uint8_t* VZK_arr_3[]=
{
    (uint8_t*)&mVZK_2_1,
    (uint8_t*)&mVZK_2_2,
    (uint8_t*)&mVZK_2_3,
    (uint8_t*)&mVZK_2_4,
    (uint8_t*)&mVZK_2_5,

    (uint8_t*)&mVZK_2_6,
    (uint8_t*)&mVZK_2_7,
    (uint8_t*)&mVZK_2_8,
    (uint8_t*)&mVZK_2_9,
    (uint8_t*)&mVZK_2_10,

    (uint8_t*)&mVZK_2_11,

    (uint8_t*)&mVZK_3_1,
    (uint8_t*)&mVZK_3_2,
    (uint8_t*)&mVZK_3_3,
    (uint8_t*)&mVZK_3_4,
    (uint8_t*)&mVZK_3_5,

    (uint8_t*)&mVZK_3_6,
    (uint8_t*)&mVZK_3_7,
    (uint8_t*)&mVZK_3_8,
    (uint8_t*)&mVZK_3_9,
    (uint8_t*)&mVZK_3_10,

    (uint8_t*)&mVZK_3_11,


    (uint8_t*)&mVZK_4_1,
    (uint8_t*)&mVZK_4_2,
    (uint8_t*)&mVZK_4_3,
    (uint8_t*)&mVZK_4_4,
    (uint8_t*)&mVZK_4_5,

    (uint8_t*)&mVZK_4_6,
    (uint8_t*)&mVZK_4_7,
    (uint8_t*)&mVZK_4_8,
    (uint8_t*)&mVZK_4_9,
    (uint8_t*)&mVZK_4_10,

    (uint8_t*)&mVZK_4_11,
};

extern uint16_t i;
void Shpz_3_Ind()
{

     if (net_fl&(1<<NET_WORK_SHPZ3)) {
        for (i=0;i<33;i++) {
             *VZK_arr_3[i]=null_lamp;
        }
    }
    else {
//        for (i=0;i<11;i++) {
//            if (VZK2.stan&KOGT_OP) {
//                if (data_from_slave3.VZK_FL1[0]&(1<<i)) *VZK_arr_3[i]=red_lamp; else *VZK_arr_3[i]=red_b_lamp;
//            }
//            else {
//                if (data_from_slave3.VZK_FL1[0]&(1<<i)) *VZK_arr_3[i]=green_b_lamp; else *VZK_arr_3[i]=green_lamp;
//            }
//        }
//
//        for (i=11;i<22;i++) {
//            if (VZK3.stan&KOGT_OP) {
//                if (data_from_slave3.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_3[i]=red_lamp; else *VZK_arr_3[i]=red_b_lamp;
//            }
//            else {
//                if (data_from_slave3.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_3[i]=green_b_lamp; else *VZK_arr_3[i]=green_lamp;
//            }
//        }
//
//        for (i=22;i<33;i++) {
//            if (VZK4.stan&KOGT_OP) {
//                if (data_from_slave3.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_3[i]=red_lamp; else *VZK_arr_3[i]=red_b_lamp;
//            }
//            else {
//                if (data_from_slave3.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_3[i]=green_b_lamp; else *VZK_arr_3[i]=green_lamp;
//            }
//        }
    }
}

void Shpz_3_Work()
{
//    for (i=0;i<FLOOR_NUM_3;i++) {
//        if (fire_fl&(FIRE_FL_M_PK3|FIRE_FL_M_SPS3)){
//            if (fire_fl&FIRE_FL_M_PK3) {
//                if (fire_floor1==(2+i)) data_for_slave3.flag|=(1<<i); else data_for_slave3.flag&=~(1<<i);
//            }
//            if (fire_fl&FIRE_FL_M_SPS3) {
//                if (fire_floor1==(2+i)) data_for_slave3.flag|=(1<<(i+4)); else data_for_slave3.flag&=~(1<<(i+4));
//            }
//        }
//        else {
//            if (data_from_slave3.status&(1<<i)) {
//                if (net_status_counter_3[i]) {
//                    if (!sec_tik) net_status_counter_3[i]--;
//                }
//                else
//                {
//                    if (!(fire_floor==2+i)) alarm_fl|=0x0001;
//                    fire_floor=2+i;
//                    if (fire_floor1==0xff) fire_floor1=2+i;
//                    fire_fl=FIRE_FL_M_PK3;
//                }
//            }
//            else
//            {
//                net_status_counter_3[i]=COUNTER_NET_STATUS;
//            }
//        }
//    }

}

void Shpz_3_StopPdz()
{
//    net_status_counter_3[0]=COUNTER_NET_STATUS;
//    net_status_counter_3[1]=COUNTER_NET_STATUS;
//    net_status_counter_3[2]=COUNTER_NET_STATUS;
//    for (i=0;i<FLOOR_NUM_3;i++) {
//        data_from_slave3.status&=~(1<<i);
//    }
}

