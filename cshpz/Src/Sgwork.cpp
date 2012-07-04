#include "Sgwork.h"
#include "Etaz.h"
#include "Nls.h"
#include "Pdz.h"
#include "Test.h"
#include "SHPZ_16.h"
#include "SHPZ_18.h"

//#define time_fire 5

extern uint8_t MSK[8];
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_zov_t.h"

extern NET_OUTPUT_STRUCT1 data_from_slave02;
extern NET_INPUT_STRUCT1 data_for_slave02;

extern NET_OUTPUT_STRUCT1 data_from_slave3;
extern NET_INPUT_STRUCT1 data_for_slave3;

extern NET_OUTPUT_STRUCT1 data_from_slave6;
extern NET_INPUT_STRUCT1 data_for_slave6;

extern NET_OUTPUT_STRUCT1 data_from_slave9;
extern NET_INPUT_STRUCT1 data_for_slave9;

extern NET_OUTPUT_STRUCT1 data_from_slave11;
extern NET_INPUT_STRUCT1 data_for_slave11;

extern NET_OUTPUT_STRUCT1 data_from_slave14;
extern NET_INPUT_STRUCT1 data_for_slave14;

extern NET_OUTPUT_STRUCT1 data_from_slave16;
extern NET_INPUT_STRUCT1 data_for_slave16;

extern NET_OUTPUT_STRUCT1 data_from_slave18;
extern NET_INPUT_STRUCT1 data_for_slave18;

extern NET_OUTPUT_STRUCT1 data_from_slave20;
extern NET_INPUT_STRUCT1 data_for_slave20;

extern NET_OUTPUT_STRUCT1 data_from_slave21;
extern NET_INPUT_STRUCT1 data_for_slave21;

extern uint8_t NetPackInfo[NUM_OF_SCAF];//
uint16_t scafe_fl;
uint16_t fire_fl;
uint16_t alarm_fl XBSS;


uint16_t TestMT;
uint8_t TastMSK;
uint8_t TechFlag;

uint16_t net_fl;
uint8_t scafe_net;

extern uint8_t WaitWhenIronIsReady;
uint16_t i;

uint8_t LampMirg;

extern SysTime time;

uint8_t* NET_LED[]=
{
    (uint8_t*)&mSHPZ02,
    (uint8_t*)&mSHPZ3,
    (uint8_t*)&mSHPZ6,
    (uint8_t*)&mSHPZ9,
    (uint8_t*)&mSHPZ11,

    (uint8_t*)&mSHPZ14,
    (uint8_t*)&mSHPZ16,
    (uint8_t*)&mSHPZ18,
    (uint8_t*)&mSHPZ20,
    (uint8_t*)&mSHPZ21,
};

//extern void Shpz_Center_Ind();
extern void Shpz_02_Ind();
//extern void Shpz_3_Ind();
//extern void Shpz_6_Ind();
//extern void Shpz_9_Ind();
//extern void Shpz_11_Ind();
//extern void Shpz_14_Ind();
//extern void Shpz_16_Ind();
//extern void Shpz_18_Ind();
void all_ind()
{
	if (!sec_tik) mReady^=0xf0;//лампочка "Готов"

//    Shpz_Center_Ind();
    Shpz_02_Ind();
//    Shpz_3_Ind();
//    Shpz_6_Ind();
//    Shpz_9_Ind();
//    Shpz_11_Ind();
//    Shpz_14_Ind();
//    Shpz_16_Ind();
//    Shpz_18_Ind();

    for (i=0;i<NUM_OF_SCAF;i++) {
        if (net_fl&(1<<i)) *NET_LED[i]=red_lamp; else *NET_LED[i]=green_lamp;
    }

    mNULL_LAMP=null_lamp;

	if(WaitWhenIronIsReady) return;
}
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;
extern uint8_t fire_floor4;
uint8_t dev_option;
void Work_init()
{
	net_fl=0xffff;
	fire_floor=0xff;
	fire_floor1=0xff;
	fire_floor2=0xff;
	fire_floor3=0xff;
	fire_floor4=0xff;
}

extern void pisk_drv();//см. ниже
extern void pause_pisk();//см. ниже

uint8_t weit_zone_1, weit_zone_2, weit_zone_3,weit_zone_4, weit_zone_5;// затримка СПС по зонах
uint8_t stop_pdz_counter;
uint8_t fire_copy;
uint8_t net_floor;
static uint8_t wait_poz1=0;
static uint8_t wait_poz2=0;
static uint8_t wait_poz3=0;
static uint8_t wait_poz4=0;
#define DELAY_TIME 3
//extern uint8_t fire_floor;
uint8_t i_mt,i_msk,i_msk_fil;
//extern uint8_t MSK_FIELD[2][33];
uint8_t MSK_FIL[8];
uint16_t OS_MT_TEST;
uint16_t MT_TEST;
uint16_t TestMTResult;
uint8_t TestMSK,TestMSKResult;
extern uint8_t cur_msk_selector;
extern uint8_t uiNetCounter;
uint8_t FIRE_SPS_K_COUNTER[NUM_OF_FLOOR];
uint8_t FIRE_SPS_K_COUNTER_0[4];
uint8_t FIRE_ZONE_COUNTER[4];
uint8_t ODIN=0xff;
uint8_t* FIRE_SPS_K[]={
     (uint8_t*)&kFIRE_FLOOR_0,
     (uint8_t*)&kFIRE_FLOOR_1,
     (uint8_t*)&kFIRE_FLOOR_2,
     (uint8_t*)&kFIRE_FLOOR_3,
     (uint8_t*)&kFIRE_FLOOR_4,

     (uint8_t*)&kFIRE_FLOOR_5,
     (uint8_t*)&kFIRE_FLOOR_6,
     (uint8_t*)&kFIRE_FLOOR_7,
     (uint8_t*)&kFIRE_FLOOR_8,
     (uint8_t*)&kFIRE_FLOOR_9,

     (uint8_t*)&kFIRE_FLOOR_10,
     (uint8_t*)&kFIRE_FLOOR_11,
     (uint8_t*)&kFIRE_FLOOR_12,
     (uint8_t*)&kFIRE_FLOOR_13,
     (uint8_t*)&kFIRE_FLOOR_14,

     (uint8_t*)&kFIRE_FLOOR_15,
     (uint8_t*)&kFIRE_FLOOR_16,
     (uint8_t*)&kFIRE_FLOOR_17,
     (uint8_t*)&kFIRE_FLOOR_18,
     (uint8_t*)&kFIRE_FLOOR_19,
     (uint8_t*)&ODIN,
};
uint8_t* FIRE_SPS_K_0[]={
     (uint8_t*)&kFIRE_FLOOR_0_0,
     (uint8_t*)&kFIRE_FLOOR_1_0,
     (uint8_t*)&kFIRE_FLOOR_2_0,
     (uint8_t*)&kFIRE_FLOOR_3_0,
};

uint8_t* arrFIRE_ZONE[]={
     (uint8_t*)&kFIRE_ZONE_1,
     (uint8_t*)&kFIRE_ZONE_2,
     (uint8_t*)&kFIRE_ZONE_3,
     (uint8_t*)&kFIRE_ZONE_4,
};

uint16_t* FIRE_FLAGS[]=
{
    (uint16_t*)&data_for_slave02.flag,
    (uint16_t*)&data_for_slave3.flag,
    (uint16_t*)&data_for_slave6.flag,
    (uint16_t*)&data_for_slave9.flag,
    (uint16_t*)&data_for_slave11.flag,

    (uint16_t*)&data_for_slave14.flag,
    (uint16_t*)&data_for_slave16.flag,
    (uint16_t*)&data_for_slave18.flag,
    (uint16_t*)&data_for_slave20.flag,
    (uint16_t*)&data_for_slave21.flag,
};
//extern void Shpz_Center_Work();
//extern void Shpz_3_StopPdz();
extern void Shpz_02_Work();
extern void Shpz_02_StopPdz();
//extern void Shpz_3_Work();
//extern void Shpz_3_StopPdz();
//extern void Shpz_6_Work();
//extern void Shpz_6_StopPdz();
//extern void Shpz_9_Work();
//extern void Shpz_9_StopPdz();
//extern void Shpz_11_Work();
//extern void Shpz_11_StopPdz();
//extern void Shpz_14_Work();
//extern void Shpz_14_StopPdz();
//extern void Shpz_16_Work();
//extern void Shpz_16_StopPdz();
//extern void Shpz_18_Work();
//extern void Shpz_18_StopPdz();
//extern void Shpz_20_Work();
//extern void Shpz_20_StopPdz();

void Work_drv()
{
//========================================================================================
    for (i=0;i<NUM_OF_SCAF;i++) {
        if (NetPackInfo[i]>20) {
            net_fl|=(1<<i);
        }
        else {
            net_fl&=~(1<<i);
        }
    }

//    for (i=0;i<NUM_OF_FLOOR;i++) {
//        if (!(*FIRE_SPS_K[i])) {
//            if (FIRE_SPS_K_COUNTER[i]) {
//
//            }
//            else {
//                fire_floor=i;
//                if (i<8) fire_floor1=i;
//                else if (i<16) fire_floor2=i;
//                else fire_floor3=i;
//                fire_fl=FIRE_FL_M_SPS3;
//            }
//        }
//        else {
//            FIRE_SPS_K_COUNTER[i]=5;
//        }
//        if (i<4) {
//            if (!(*FIRE_SPS_K_0[i])) {
//                if (FIRE_SPS_K_COUNTER_0[i]) {
//
//                }
//                else {
//                    fire_floor=i;
//                    fire_floor4=i;
//                    fire_fl=FIRE_FL_M_SPS3;
//                }
//            }
//            else {
//                FIRE_SPS_K_COUNTER_0[i]=5;
//            }
//        }
//    }

    if (kSTOP_PDZ) {
        fire_fl=FIRE_FL_M_STOP_PDZ;
        stop_pdz_counter=5;
        fire_floor=0xff;
        fire_floor1=0xff;
        fire_floor2=0xff;
        fire_floor3=0xff;
        fire_floor4=0xff;
        alarm_fl=0x0000;
    }
    else {
        if (fire_fl&FIRE_FL_M_STOP_PDZ) {
            if (stop_pdz_counter) {
                if (!sec_tik) stop_pdz_counter--;
                for(i=0;i<10;i++){
                    *FIRE_FLAGS[i]=FIRE_FL_STOP_PDZ;
                }
                fire_floor=0xff;
                Shpz_02_StopPdz();
//                Shpz_3_StopPdz();
//                Shpz_6_StopPdz();
//                Shpz_9_StopPdz();
//                Shpz_11_StopPdz();
//                Shpz_14_StopPdz();
//                Shpz_16_StopPdz();
//                Shpz_18_StopPdz();
//                Shpz_20_StopPdz();
            }
            else {
                for(i=0;i<10;i++){
                    *FIRE_FLAGS[i]&=~FIRE_FL_STOP_PDZ;
                }
                fire_fl=0x0000;
                fire_floor=0xff;
                fire_floor1=0xff;
                fire_floor2=0xff;
                fire_floor3=0xff;
                fire_floor4=0xff;
                alarm_fl=0x0000;
                fire_fl&=~FIRE_FL_M_STOP_PDZ;
            }
        }
        else {
            for (i=0;i<NUM_OF_FLOOR;i++) {
                if (!(*FIRE_SPS_K[i])) {
                    if (FIRE_SPS_K_COUNTER[i]) {
                        if (!sec_tik) FIRE_SPS_K_COUNTER[i]--;
                    }
                    else {
                        if (!(fire_floor==i)) alarm_fl|=0x0001;
                        fire_floor=i;
                        if (i<8) {if (fire_floor1==0xff) fire_floor1=i;}
                        else if (i<16) {if (fire_floor2==0xff) fire_floor2=i;}
                        else if (fire_floor3==0xff) fire_floor3=i;
                        fire_fl=FIRE_FL_M_SPS3;
                    }
                }
                else {
                    FIRE_SPS_K_COUNTER[i]=5;
                }
                if (i<4) {
                    if (!(*FIRE_SPS_K_0[i])) {
                        if (FIRE_SPS_K_COUNTER_0[i]) {
                            if (!sec_tik) FIRE_SPS_K_COUNTER_0[i]--;
                        }
                        else {
                            if (!(fire_floor==i)) alarm_fl|=0x0001;
                            fire_floor=i;
                            fire_floor1=i;
                            fire_fl=FIRE_FL_M_SPS3;
                        }
                    }
                    else {
                        FIRE_SPS_K_COUNTER_0[i]=5;
                    }
                }
                if (i<4) {
                    if (!(*arrFIRE_ZONE[i])) {
                        if (FIRE_ZONE_COUNTER[i]) {
                            if (!sec_tik) FIRE_ZONE_COUNTER[i]--;
                        }
                        else {
                            if (!(fire_fl&FIRE_FL_M_ALL)) alarm_fl|=0x0001;
                            fire_fl=FIRE_FL_M_ALL;
                        }
                    }
                    else {
                        FIRE_ZONE_COUNTER[i]=5;
                    }
                }
            }
//            Shpz_Center_Work();
            Shpz_02_Work();
//            Shpz_3_Work();
//            Shpz_6_Work();
//            Shpz_9_Work();
//            Shpz_11_Work();
//            Shpz_14_Work();
//            Shpz_16_Work();
//            Shpz_18_Work();
//            Shpz_20_Work();

            if ((!(fire_floor==0xff))||(fire_fl&FIRE_FL_M_ALL)) {
                for(i=0;i<10;i++){
                   *FIRE_FLAGS[i]|=FIRE_FL_ALL;
                }
            }
            if (!(fire_floor1==0xff)) {
                *FIRE_FLAGS[8]|=FIRE_FL_SPS1;
                *FIRE_FLAGS[9]|=FIRE_FL_SPS1;
            }
            if (!(fire_floor2==0xff)) {
                *FIRE_FLAGS[8]|=FIRE_FL_SPS2;
                *FIRE_FLAGS[9]|=FIRE_FL_SPS2;
            }
            if (!(fire_floor3==0xff)) {
                *FIRE_FLAGS[8]|=FIRE_FL_SPS3;
                *FIRE_FLAGS[9]|=FIRE_FL_SPS3;
            }
        }
    }
//========================================================================================
	pisk_drv();
	//pause_pisk();
}

uint16_t pisk,pisk_cpy;
uint8_t pisk_counter;
void check_avar_pisk()
{
	if(alarm_fl&0x0001) {
        alarm_fl=0x0000;
        pisk|=(1<<0);
	}
	else {
        if(!KTEST) {
            if (pisk_counter) {
                if (!sec_tik) pisk_counter--;
            }
            else {
                //OP_ZUMER=1;
                //tech_fl|=SOUND;
                pisk|=(1<<0);
            }
        }//OP_ZUMER=1;
        else {
            if (pisk_counter) {

            }
            else {
                //tech_fl&=~SOUND;
                //OP_ZUMER=0;
                pisk=0;
            }
            pisk_counter=5;
        }
	}
	 if (fire_fl&FIRE_FL_M_STOP_PDZ) pisk&=~(1<<0);
}

extern void set_sound();
extern void clr_sound();
void pause_pisk()
{
	if(KEY_NO||(!KTEST))//сброс звука
	{
		pisk=0;
		//check_avar_pisk();
		pisk_cpy=pisk;
		tech_fl&=~SOUND;
		alarm_fl&=~0x0001;
		OP_ZUMER=0;
	}
}
void pisk_drv()
{
	if (pisk_counter) if (pisk&(1<<0)) pause_pisk();
	check_avar_pisk();

	if(!pisk)
	{
		pisk_cpy=pisk;
		tech_fl&=~SOUND;
		OP_ZUMER=0;
	}
	else if(pisk!=pisk_cpy)
	{
		tech_fl|=SOUND;
		OP_ZUMER=1;
	}


}
