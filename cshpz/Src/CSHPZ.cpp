#include "CSHPZ.h"

#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_zov_t.h"
#include "../../Devs/Dev_moe.h"

extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

//const prog_char strKPD[]="ÊÏÄ";
const prog_char strKPD01[]="ÊÏÄ01";
const prog_char strKPD02[]="ÊÏÄ02";
const prog_char strKPD11[]="ÊÏÄ11";
const prog_char strKPD12[]="ÊÏÄ12";
const prog_char strPP001[]="ÏÏ001";
const prog_char strPP01[]="ÏÏ01";
const prog_char strZOV0[]="ÇÎÂ0";
const prog_char strVZK0[]="ÂÇÊ0";
const prog_char strPP1[]="ÏÏ1";
const prog_char strZOV1[]="ÇÎÂ1";
const prog_char strVZK1[]="ÂÇÊ1";

MOE <13+80*16,24+32*0,      0,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD01> KPD01;
MOE <55+80*17,25+32*0,      1,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD02> KPD02;
KOGT <12+80*16,1+32*0,     13,             OPT_CHECK_PRESS|OPT_CHECK_OS,    strPP001>   PP001;
KOGT <20+80*16,2+32*0,     14,             OPT_CHECK_PRESS|OPT_CHECK_OS,    strPP01>   PP01;
ZOVT <19+80*16,5+32*1,       6, 0,                                           strZOV0> ZOV0;
KOGT <0+80*0,5+32*1,       4,                               OPT_CHECK_OS,  strVZK0> VZK0;

MOE <29+80*16,26+32*0,      2,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD11> KPD11;
MOE <71+80*17,27+32*0,      3,  OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,  strKPD12> KPD12;
KOGT <28+80*16,0+32*0,     12,             OPT_CHECK_PRESS|OPT_CHECK_OS,    strPP1>   PP1;
ZOVT <27+80*16,5+32*1,      6, 0,                                           strZOV1> ZOV1;
KOGT <0+80*0,5+32*1,       5,                               OPT_CHECK_OS,  strVZK1> VZK1;
TDevObject* pDevs_arr_Center[]=
{
	&KPD01,
	&KPD02,
	&PP001,
	&PP001,
	&ZOV0,

	&VZK0,
	&KPD11,
	&KPD12,
	&PP1,
	&ZOV1,

	&VZK1,
};


uint8_t* VZK_arr_Center[][3]=
{
    (uint8_t*)&mVZK_0_1,    (uint8_t*)&kVZK_0_1,    (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_0_2,    (uint8_t*)&kVZK_0_2,    (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_0_3,    (uint8_t*)&kVZK_0_3,    (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_0_4,    (uint8_t*)&kVZK_0_4,    (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_0_5,    (uint8_t*)&kVZK_0_5,    (uint8_t*)&OP_VZK0,

    (uint8_t*)&mVZK_0_6,    (uint8_t*)&kVZK_0_6,    (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_0_7,    (uint8_t*)&kVZK_0_7,    (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_0_8,    (uint8_t*)&kVZK_0_8,    (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_0_9,    (uint8_t*)&kVZK_0_9,    (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_0_10,   (uint8_t*)&kVZK_0_10,   (uint8_t*)&OP_VZK0,

    (uint8_t*)&mVZK_C_11,   (uint8_t*)&kVZK_0_11,   (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_C_12,   (uint8_t*)&kVZK_0_12,   (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_C_13,   (uint8_t*)&kVZK_0_13,   (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_C_14,   (uint8_t*)&kVZK_0_14,   (uint8_t*)&OP_VZK0,
    (uint8_t*)&mVZK_C_15,   (uint8_t*)&kVZK_0_15,   (uint8_t*)&OP_VZK0,

    (uint8_t*)&mVZK_1_1,    (uint8_t*)&kVZK_1_1,    (uint8_t*)&OP_VZK1,
    (uint8_t*)&mVZK_1_2,    (uint8_t*)&kVZK_1_2,    (uint8_t*)&OP_VZK1,
    (uint8_t*)&mVZK_1_3,    (uint8_t*)&kVZK_1_3,    (uint8_t*)&OP_VZK1,
    (uint8_t*)&mVZK_1_4,    (uint8_t*)&kVZK_1_4,    (uint8_t*)&OP_VZK1,
    (uint8_t*)&mVZK_1_5,    (uint8_t*)&kVZK_1_5,    (uint8_t*)&OP_VZK1,
};

uint8_t* Fire_arr_Led[][2]=
{
    (uint8_t*)&mFIRE_PK0_C,    (uint8_t*)&mFIRE_SPS0_C,
    (uint8_t*)&mFIRE_PK1_C,    (uint8_t*)&mFIRE_SPS1_C,
    (uint8_t*)&mFIRE_PK2_C,    (uint8_t*)&mFIRE_SPS2_C,
    (uint8_t*)&mFIRE_PK3_C,    (uint8_t*)&mFIRE_SPS3_C,
    (uint8_t*)&mFIRE_PK4_C,    (uint8_t*)&mFIRE_SPS4_C,

    (uint8_t*)&mFIRE_PK5_C,    (uint8_t*)&mFIRE_SPS5_C,
    (uint8_t*)&mFIRE_PK6_C,    (uint8_t*)&mFIRE_SPS6_C,
    (uint8_t*)&mFIRE_PK7_C,    (uint8_t*)&mFIRE_SPS7_C,
    (uint8_t*)&mFIRE_PK8_C,    (uint8_t*)&mFIRE_SPS8_C,
    (uint8_t*)&mFIRE_PK9_C,    (uint8_t*)&mFIRE_SPS9_C,

    (uint8_t*)&mFIRE_PK10_C,    (uint8_t*)&mFIRE_SPS10_C,
    (uint8_t*)&mFIRE_PK11_C,    (uint8_t*)&mFIRE_SPS11_C,
    (uint8_t*)&mFIRE_PK12_C,    (uint8_t*)&mFIRE_SPS12_C,
    (uint8_t*)&mFIRE_PK13_C,    (uint8_t*)&mFIRE_SPS13_C,
    (uint8_t*)&mFIRE_PK14_C,    (uint8_t*)&mFIRE_SPS14_C,

    (uint8_t*)&mFIRE_PK15_C,    (uint8_t*)&mFIRE_SPS15_C,
    (uint8_t*)&mFIRE_PK16_C,    (uint8_t*)&mFIRE_SPS16_C,
    (uint8_t*)&mFIRE_PK17_C,    (uint8_t*)&mFIRE_SPS17_C,
    (uint8_t*)&mFIRE_PK18_C,    (uint8_t*)&mFIRE_SPS18_C,
    (uint8_t*)&mFIRE_PK19_C,    (uint8_t*)&mFIRE_SPS19_C,
};
extern uint16_t i;

void Shpz_Center_Ind()
{
    for (i=0;i<20;i++) {
		if (*VZK_arr_Center[i][2]) {
            if (*VZK_arr_Center[i][1]) *VZK_arr_Center[i][0]=red_lamp; else *VZK_arr_Center[i][0]=red_b_lamp;
		}
		else {
            if (*VZK_arr_Center[i][1]) *VZK_arr_Center[i][0]=green_b_lamp; else *VZK_arr_Center[i][0]=green_lamp;
		}
	}

	for (i=0;i<20;i++) {
        if (fire_floor==i) {
            if (fire_fl&FIRE_FL_M_PK3) *Fire_arr_Led[i][0]=red_lamp; else *Fire_arr_Led[i][0]=null_lamp;
            if (fire_fl&FIRE_FL_M_SPS3) *Fire_arr_Led[i][1]=red_lamp; else *Fire_arr_Led[i][1]=null_lamp;
        }
        else {
            *Fire_arr_Led[i][0]=null_lamp;
            *Fire_arr_Led[i][1]=null_lamp;
        }
	}
}


uint8_t counter_pk1,counter_pk2;

void fnFireFromPK1()
{
    if (kKNOP_FLOORE_1__1&&kKNOP_FLOORE_1__2) {
        if (counter_pk1) {
            if (!sec_tik) counter_pk1--;
        }
        else {
            if (!(fire_floor==0)) alarm_fl|=0x0001;
            fire_floor=0;
            if (fire_floor1==0xff) fire_floor1=0;
            fire_fl=FIRE_FL_M_PK1;
        }
    }
    else {
        counter_pk1=time_fire;
    }
}

void fnFireFromPK2()
{
    if (kKNOP_FLOORE_2__1&&kKNOP_FLOORE_2__2) {
        if (counter_pk2) {
            if (!sec_tik) counter_pk2--;
        }
        else {
            if (!(fire_floor==1)) alarm_fl|=0x0001;
            fire_floor=1;
            if (fire_floor1==0xff) fire_floor1=1;
            fire_fl=FIRE_FL_M_PK1;
        }
    }
    else {
        counter_pk2=time_fire;
    }
}

void Shpz_Center_Work()
{
    fnFireFromPK1();
    fnFireFromPK2();
}
