#include "SHPZ_02.h"

#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"
#include "../../Devs/Dev_kog_net.h"

extern uint16_t fire_fl;
extern uint8_t fire_floor;

uint8_t net_status_counter_02[FLOOR_NUM_02];

extern NET_OUTPUT_STRUCT1 data_from_slave02;
extern NET_INPUT_STRUCT1 data_for_slave02;
extern NET_OUTPUT_STRUCT1 data_from_slave3;
extern NET_INPUT_STRUCT1 data_for_slave3;
//extern const prog_char strKPD181[] PROGMEM;
const prog_char strV_2[]="B2";
const prog_char strSHDU1[]="ÙÄÓ1";
const prog_char strSHDU2[]="ÙÄÓ2";
const prog_char strZOV_0[]="ÇÎÂ0";
const prog_char strZOV_1[]="ÇÎÂ1";
const prog_char strZOV_2[]="ÇÎÂ2";
const prog_char strZOV_3[]="ÇÎÂ3";
const prog_char strVZK_0[]="ÂÇÊ0";
const prog_char strVZK_1[]="ÂÇÊ1";
const prog_char strVZK_2[]="ÂÇÊ2";
const prog_char strVZK_3[]="ÂÇÊ3";

KOG_NET KPD21   (strV_2,
                (uint8_t*)&data_from_slave02.devs_net_stat[0],
                (uint8_t*)&data_for_slave02.devs_net_cmd[0],
                (uint8_t*)&mRRR,
                 0);
//ZOVT_NET <74+80*17,strZOV_0,&data_from_slave02,&data_for_slave02,0,NET_WORK_SHPZ02> ZOV_0;
//KOGT_NET <0+80*0,strVZK_0,&data_from_slave02,&data_for_slave02,1,NET_WORK_SHPZ02> VZK_0;
//
//ZOVT_NET <42+80*15,strZOV_1,&data_from_slave02,&data_for_slave02,2,NET_WORK_SHPZ02> ZOV_1;
//KOGT_NET <0+80*0,strVZK_1,&data_from_slave02,&data_for_slave02,3,NET_WORK_SHPZ02> VZK_1;
//
//ZOVT_NET <50+80*15,strZOV_2,&data_from_slave02,&data_for_slave02,4,NET_WORK_SHPZ02> ZOV_2;
//KOGT_NET <0+80*0,strVZK_2,&data_from_slave02,&data_for_slave02,5,NET_WORK_SHPZ02> VZK_2;
//
//ZOVT_NET <58+80*15,strZOV_3,&data_from_slave02,&data_for_slave02,6,NET_WORK_SHPZ02> ZOV_3;
//KOGT_NET <0+80*0,strVZK_3,&data_from_slave02,&data_for_slave02,7,NET_WORK_SHPZ02> VZK_3;
//
//KOGT_NET <20+80*14,strV_2,&data_from_slave02,&data_for_slave02,8,NET_WORK_SHPZ02> V_2;
//KOGT_NET <20+80*14,strSHDU1,&data_from_slave02,&data_for_slave02,9,NET_WORK_SHPZ02> SHDU1;
//KOGT_NET <20+80*14,strSHDU2,&data_from_slave02,&data_for_slave02,10,NET_WORK_SHPZ02> SHDU2;

TDevObject* pDevs_arr_02[]=
{
    &KPD21
//	&ZOV_0,
//	&VZK_0,
//
//	&ZOV_1,
//	&VZK_1,
//
//	&ZOV_2,
//	&VZK_2,
//
//	&ZOV_3,
//	&VZK_3,
//
//
//	&V_2,
//	&SHDU1,
//	&SHDU2,
};

uint8_t* VZK_arr_02[]=
{
    (uint8_t*)&mVZK_0_14,
    (uint8_t*)&mVZK_0_15,
    (uint8_t*)&mVZK_0_16,
    (uint8_t*)&mVZK_0_17,
    (uint8_t*)&mVZK_0_18,

    (uint8_t*)&mVZK_0_19,
    (uint8_t*)&mVZK_0_20,
    (uint8_t*)&mVZK_0_21,
    (uint8_t*)&mVZK_0_22,
    (uint8_t*)&mVZK_0_23,

    (uint8_t*)&mVZK_0_24,
    (uint8_t*)&mVZK_0_25,
    (uint8_t*)&mVZK_1_6,
    (uint8_t*)&mVZK_1_7,
    (uint8_t*)&mVZK_1_8,

    (uint8_t*)&mVZK_1_9,
    (uint8_t*)&mVZK2_2_8,
    (uint8_t*)&mVZK2_2_9,
    (uint8_t*)&mVZK2_2_10,
    (uint8_t*)&mVZK2_2_11,

    (uint8_t*)&mVZK3_3_6,
    (uint8_t*)&mVZK3_3_7,
};

extern uint16_t i;
void Shpz_02_Ind()
{

//     if (net_fl&(1<<NET_WORK_SHPZ02)) {
//        for (i=0;i<22;i++) {
//             *VZK_arr_02[i]=null_lamp;
//        }
//    }
//    else {
//        for (i=0;i<12;i++) {
//            if (VZK_0.stan&KOGT_OP) {
//                if (data_from_slave02.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_02[i]=red_lamp; else *VZK_arr_02[i]=red_b_lamp;
//            }
//            else {
//                if (data_from_slave02.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_02[i]=green_b_lamp; else *VZK_arr_02[i]=green_lamp;
//            }
//        }
//
//        for (i=12;i<16;i++) {
//            if (VZK_1.stan&KOGT_OP) {
//                if (data_from_slave02.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_02[i]=red_lamp; else *VZK_arr_02[i]=red_b_lamp;
//            }
//            else {
//                if (data_from_slave02.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_02[i]=green_b_lamp; else *VZK_arr_02[i]=green_lamp;
//            }
//        }
//
//        for (i=16;i<20;i++) {
//            if (VZK_2.stan&KOGT_OP) {
//                if (data_from_slave02.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_02[i]=red_lamp; else *VZK_arr_02[i]=red_b_lamp;
//            }
//            else {
//                if (data_from_slave02.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_02[i]=green_b_lamp; else *VZK_arr_02[i]=green_lamp;
//            }
//        }
//
//        for (i=20;i<22;i++) {
//            if (VZK_3.stan&KOGT_OP) {
//                if (data_from_slave02.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_02[i]=red_lamp; else *VZK_arr_02[i]=red_b_lamp;
//            }
//            else {
//                if (data_from_slave02.VZK_FL1[i/8]&(1<<(i%8))) *VZK_arr_02[i]=green_b_lamp; else *VZK_arr_02[i]=green_lamp;
//            }
//        }
//    }
}

void Shpz_02_Work()
{
//    for (i=0;i<FLOOR_NUM_02;i++) {
//        if (fire_fl&(FIRE_FL_M_PK3|FIRE_FL_M_SPS3)){
//            if (fire_fl&FIRE_FL_M_PK3) {
//                if (fire_floor1==(0+i)) data_for_slave02.flag|=(1<<i); else data_for_slave02.flag&=~(1<<i);
//            }
//            if (fire_fl&FIRE_FL_M_SPS3) {
//                if (fire_floor1==(0+i)) data_for_slave02.flag|=(1<<(i+4)); else data_for_slave02.flag&=~(1<<(i+4));
//            }
//        }
//        else {
//            if (data_from_slave02.status&(1<<i)) {
//                if (net_status_counter_02[i]) {
//                    if (!sec_tik) net_status_counter_02[i]--;
//                }
//                else
//                {
//                    if (!(fire_floor==0+i)) alarm_fl|=0x0001;
//                    fire_floor=0+i;
//                    if (fire_floor1==0xff) fire_floor1=0+i;
//                    fire_fl=FIRE_FL_M_PK3;
//                }
//            }
//            else
//            {
//                net_status_counter_02[i]=COUNTER_NET_STATUS;
//            }
//        }
//    }

}

void Shpz_02_StopPdz()
{
//    net_status_counter_02[0]=COUNTER_NET_STATUS;
//    net_status_counter_02[1]=COUNTER_NET_STATUS;
//    net_status_counter_02[2]=COUNTER_NET_STATUS;
//    net_status_counter_02[3]=COUNTER_NET_STATUS;
//    for (i=0;i<FLOOR_NUM_02;i++) {
//        data_from_slave02.status&=~(1<<i);
//    }
}
