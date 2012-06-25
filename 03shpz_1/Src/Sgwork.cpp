#include "Sgwork.h"
#include "Etaz.h"
#include "Nls.h"
#include "Pdz.h"
#include "Test.h"

#define time_fire 5

extern uint8_t MSK[8];
#include "../../Devs/Dev_moe.h"

extern NET_OUTPUT_STRUCT1 data_from_slave1;
extern NET_INPUT_STRUCT1 data_for_slave1;

extern NET_BFPP_OUTPUT_STRUCT bfpp_out;
extern NET_BFPP_INPUT_STRUCT bfpp_in;

extern uint8_t uiNetCounter;

uint16_t scafe_fl;
uint16_t fire_fl;

uint16_t TestMT;
uint8_t TastMSK;
uint8_t TechFlag;

uint16_t net_fl;
uint8_t scafe_net;

extern uint8_t WaitWhenIronIsReady;
uint16_t i;

uint8_t LampMirg;

extern SysTime time;

#if s03shpz_1
uint8_t* VZK_arr[][3]=
{
    (uint8_t*)&mVZK_1_1,           (uint8_t*)&kVZK_1_1,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_2,           (uint8_t*)&kVZK_1_2,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_3,           (uint8_t*)&kVZK_1_3,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_4,           (uint8_t*)&kVZK_1_4,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_5,           (uint8_t*)&kVZK_1_5,           (uint8_t*)&OP_VZK_GR1,

    (uint8_t*)&mVZK_1_6,           (uint8_t*)&kVZK_1_6,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_7,           (uint8_t*)&kVZK_1_7,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_8,           (uint8_t*)&kVZK_1_8,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_9,           (uint8_t*)&kVZK_1_9,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_10,          (uint8_t*)&kVZK_1_10,          (uint8_t*)&OP_VZK_GR1,

    (uint8_t*)&mVZK_1_11,          (uint8_t*)&kVZK_1_11,          (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_12,          (uint8_t*)&kVZK_1_12,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_13,          (uint8_t*)&kVZK_1_13,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_14,          (uint8_t*)&kVZK_1_14,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_15,          (uint8_t*)&kVZK_1_15,          (uint8_t*)&OP_VZK_GR2,

    (uint8_t*)&mVZK_1_16,          (uint8_t*)&kVZK_1_16,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_17,          (uint8_t*)&kVZK_1_17,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_18,          (uint8_t*)&kVZK_1_18,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_19,          (uint8_t*)&kVZK_1_19,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_20,          (uint8_t*)&kVZK_1_20,          (uint8_t*)&OP_VZK_GR2,

    (uint8_t*)&mVZK_1_21,          (uint8_t*)&kVZK_1_21,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_22,          (uint8_t*)&kVZK_1_22,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_23,          (uint8_t*)&kVZK_1_23,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_24,          (uint8_t*)&kVZK_1_24,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_25,          (uint8_t*)&kVZK_1_25,          (uint8_t*)&OP_VZK_GR3,

    (uint8_t*)&mVZK_1_26,          (uint8_t*)&kVZK_1_26,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_27,          (uint8_t*)&kVZK_1_27,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_28,          (uint8_t*)&kVZK_1_28,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_29,          (uint8_t*)&kVZK_1_29,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_30,          (uint8_t*)&kVZK_1_30,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_31,          (uint8_t*)&kVZK_1_31,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_32,          (uint8_t*)&kVZK_1_32,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_33,          (uint8_t*)&kVZK_1_33,          (uint8_t*)&OP_VZK_GR3,
    //
    (uint8_t*)&mVZK_1_34,          (uint8_t*)&kVZK_1_34,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_35,          (uint8_t*)&kVZK_1_35,          (uint8_t*)&OP_VZK_GR3,
};
#endif
#if SHPZ_6
uint8_t* VZK_arr[][3]=
{
    (uint8_t*)&mVZK_1_1,           (uint8_t*)&kVZK_1_1,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_2,           (uint8_t*)&kVZK_1_2,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_3,           (uint8_t*)&kVZK_1_3,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_4,           (uint8_t*)&kVZK_1_4,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_5,           (uint8_t*)&kVZK_1_5,           (uint8_t*)&OP_VZK_GR1,

    (uint8_t*)&mVZK_1_6,           (uint8_t*)&kVZK_1_6,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_7,           (uint8_t*)&kVZK_1_7,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_8,           (uint8_t*)&kVZK_1_8,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_9,           (uint8_t*)&kVZK_1_9,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_10,          (uint8_t*)&kVZK_1_10,          (uint8_t*)&OP_VZK_GR1,

    (uint8_t*)&mVZK_1_11,          (uint8_t*)&kVZK_1_11,          (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_12,          (uint8_t*)&kVZK_1_12,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_13,          (uint8_t*)&kVZK_1_13,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_14,          (uint8_t*)&kVZK_1_14,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_15,          (uint8_t*)&kVZK_1_15,          (uint8_t*)&OP_VZK_GR2,

    (uint8_t*)&mVZK_1_16,          (uint8_t*)&kVZK_1_16,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_17,          (uint8_t*)&kVZK_1_17,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_18,          (uint8_t*)&kVZK_1_18,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_19,          (uint8_t*)&kVZK_1_19,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_20,          (uint8_t*)&kVZK_1_20,          (uint8_t*)&OP_VZK_GR2,

    (uint8_t*)&mVZK_1_21,          (uint8_t*)&kVZK_1_21,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_22,          (uint8_t*)&kVZK_1_22,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_23,          (uint8_t*)&kVZK_1_23,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_24,          (uint8_t*)&kVZK_1_24,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_25,          (uint8_t*)&kVZK_1_25,          (uint8_t*)&OP_VZK_GR3,

    (uint8_t*)&mVZK_1_26,          (uint8_t*)&kVZK_1_26,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_27,          (uint8_t*)&kVZK_1_27,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_28,          (uint8_t*)&kVZK_1_28,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_29,          (uint8_t*)&kVZK_1_29,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_30,          (uint8_t*)&kVZK_1_30,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_31,          (uint8_t*)&kVZK_1_31,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_32,          (uint8_t*)&kVZK_1_32,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_33,          (uint8_t*)&kVZK_1_33,          (uint8_t*)&OP_VZK_GR3,
    //
    (uint8_t*)&mVZK_1_34,          (uint8_t*)&kVZK_1_34,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_35,          (uint8_t*)&kVZK_1_35,          (uint8_t*)&OP_VZK_GR3,
};
#endif
#if SHPZ_9
uint8_t* VZK_arr[][3]=
{
    (uint8_t*)&mVZK_1_1,           (uint8_t*)&kVZK_1_1,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_2,           (uint8_t*)&kVZK_1_2,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_3,           (uint8_t*)&kVZK_1_3,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_4,           (uint8_t*)&kVZK_1_4,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_5,           (uint8_t*)&kVZK_1_5,           (uint8_t*)&OP_VZK_GR1,

    (uint8_t*)&mVZK_1_6,           (uint8_t*)&kVZK_1_6,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_7,           (uint8_t*)&kVZK_1_7,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_8,           (uint8_t*)&kVZK_1_8,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_9,           (uint8_t*)&kVZK_1_9,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_10,          (uint8_t*)&kVZK_1_10,          (uint8_t*)&OP_VZK_GR1,

    (uint8_t*)&mVZK_1_11,          (uint8_t*)&kVZK_1_11,          (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_12,          (uint8_t*)&kVZK_1_12,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_13,          (uint8_t*)&kVZK_1_13,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_14,          (uint8_t*)&kVZK_1_14,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_15,          (uint8_t*)&kVZK_1_15,          (uint8_t*)&OP_VZK_GR2,

    (uint8_t*)&mVZK_1_16,          (uint8_t*)&kVZK_1_16,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_17,          (uint8_t*)&kVZK_1_17,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_18,          (uint8_t*)&kVZK_1_18,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_19,          (uint8_t*)&kVZK_1_19,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_20,          (uint8_t*)&kVZK_1_20,          (uint8_t*)&OP_VZK_GR2,

    (uint8_t*)&mVZK_1_21,          (uint8_t*)&kVZK_1_21,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_22,          (uint8_t*)&kVZK_1_22,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_23,          (uint8_t*)&kVZK_1_23,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_24,          (uint8_t*)&kVZK_1_24,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_25,          (uint8_t*)&kVZK_1_25,          (uint8_t*)&OP_VZK_GR3,

    (uint8_t*)&mVZK_1_26,          (uint8_t*)&kVZK_1_26,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_27,          (uint8_t*)&kVZK_1_27,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_28,          (uint8_t*)&kVZK_1_28,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_29,          (uint8_t*)&kVZK_1_29,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_30,          (uint8_t*)&kVZK_1_30,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_31,          (uint8_t*)&kVZK_1_31,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_32,          (uint8_t*)&kVZK_1_32,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_33,          (uint8_t*)&kVZK_1_33,          (uint8_t*)&OP_VZK_GR3,
    //
    (uint8_t*)&mVZK_1_34,          (uint8_t*)&kVZK_1_34,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_35,          (uint8_t*)&kVZK_1_35,          (uint8_t*)&OP_VZK_GR3,
};
#endif
#if SHPZ_14
uint8_t* VZK_arr[][3]=
{
    (uint8_t*)&mVZK_1_1,           (uint8_t*)&kVZK_1_1,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_2,           (uint8_t*)&kVZK_1_2,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_3,           (uint8_t*)&kVZK_1_3,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_4,           (uint8_t*)&kVZK_1_4,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_5,           (uint8_t*)&kVZK_1_5,           (uint8_t*)&OP_VZK_GR1,

    (uint8_t*)&mVZK_1_6,           (uint8_t*)&kVZK_1_6,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_7,           (uint8_t*)&kVZK_1_7,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_8,           (uint8_t*)&kVZK_1_8,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_9,           (uint8_t*)&kVZK_1_9,           (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_10,          (uint8_t*)&kVZK_1_10,          (uint8_t*)&OP_VZK_GR1,

    (uint8_t*)&mVZK_1_11,          (uint8_t*)&kVZK_1_11,          (uint8_t*)&OP_VZK_GR1,
    (uint8_t*)&mVZK_1_12,          (uint8_t*)&kVZK_1_12,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_13,          (uint8_t*)&kVZK_1_13,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_14,          (uint8_t*)&kVZK_1_14,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_15,          (uint8_t*)&kVZK_1_15,          (uint8_t*)&OP_VZK_GR2,

    (uint8_t*)&mVZK_1_16,          (uint8_t*)&kVZK_1_16,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_17,          (uint8_t*)&kVZK_1_17,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_18,          (uint8_t*)&kVZK_1_18,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_19,          (uint8_t*)&kVZK_1_19,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_20,          (uint8_t*)&kVZK_1_20,          (uint8_t*)&OP_VZK_GR2,

    (uint8_t*)&mVZK_1_21,          (uint8_t*)&kVZK_1_21,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_22,          (uint8_t*)&kVZK_1_22,          (uint8_t*)&OP_VZK_GR2,
    (uint8_t*)&mVZK_1_23,          (uint8_t*)&kVZK_1_23,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_24,          (uint8_t*)&kVZK_1_24,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_25,          (uint8_t*)&kVZK_1_25,          (uint8_t*)&OP_VZK_GR3,

    (uint8_t*)&mVZK_1_26,          (uint8_t*)&kVZK_1_26,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_27,          (uint8_t*)&kVZK_1_27,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_28,          (uint8_t*)&kVZK_1_28,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_29,          (uint8_t*)&kVZK_1_29,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_30,          (uint8_t*)&kVZK_1_30,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_31,          (uint8_t*)&kVZK_1_31,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_32,          (uint8_t*)&kVZK_1_32,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_33,          (uint8_t*)&kVZK_1_33,          (uint8_t*)&OP_VZK_GR3,
    //
    (uint8_t*)&mVZK_1_34,          (uint8_t*)&kVZK_1_34,          (uint8_t*)&OP_VZK_GR3,
    (uint8_t*)&mVZK_1_35,          (uint8_t*)&kVZK_1_35,          (uint8_t*)&OP_VZK_GR3,
};
#endif

//uint32_t i;
void all_ind()
{
	if (!sec_tik) mReady^=0xf0;//лампочка "Готов"
//    for (i=0;i<(35);i++) {
//		if (*VZK_arr[i][2]) {
//            if (*VZK_arr[i][1]) *VZK_arr[i][0]=red_lamp; else *VZK_arr[i][0]=red_b_lamp;
//		}
//		else {
//            if (*VZK_arr[i][1]) *VZK_arr[i][0]=green_b_lamp; else *VZK_arr[i][0]=green_lamp;
//		}
//	}

    if (((kKNOP_FLOORE_1__1)&&(kKNOP_FLOORE_1__2))) {
            mFIRE_KNOP_1=red_lamp;
    }
    else {
        if ((kKNOP_FLOORE_1__1+kKNOP_FLOORE_1__2)==0) {
            mFIRE_KNOP_1=null_lamp;
        }
        else {
            mFIRE_KNOP_1=yellow_lamp;
        }
    }

    if (((kKNOP_FLOORE_2__1)&&(kKNOP_FLOORE_2__2))) {
            mFIRE_KNOP_2=red_lamp;
    }
    else {
        if ((kKNOP_FLOORE_2__1+kKNOP_FLOORE_2__2)==0) {
            mFIRE_KNOP_2=null_lamp;
        }
        else {
            mFIRE_KNOP_2=yellow_lamp;
        }
    }

    if (((kKNOP_FLOORE_3__1)&&(kKNOP_FLOORE_3__2))) {
            mFIRE_KNOP_3=red_lamp;
    }
    else {
        if ((kKNOP_FLOORE_3__1+kKNOP_FLOORE_3__2)==0) {
            mFIRE_KNOP_3=null_lamp;
        }
        else {
            mFIRE_KNOP_3=yellow_lamp;
        }
    }

    if (fire_fl&(FIRE_FL_S_PK1|FIRE_FL_S_PK1_RAZ)) {
        if (fire_fl&FIRE_FL_S_PK1_RAZ) mFIRE_FL_KN1=red_lamp; else mFIRE_FL_KN1=red_b_lamp;
    }
    else {
        mFIRE_FL_KN1=null_lamp;
    }

    if (fire_fl&(FIRE_FL_S_PK2|FIRE_FL_S_PK2_RAZ)) {
        if (fire_fl&FIRE_FL_S_PK2_RAZ) mFIRE_FL_KN2=red_lamp; else mFIRE_FL_KN2=red_b_lamp;
    }
    else {
        mFIRE_FL_KN2=null_lamp;
    }

    if (fire_fl&(FIRE_FL_S_PK3|FIRE_FL_S_PK3_RAZ)) {
        if (fire_fl&FIRE_FL_S_PK3_RAZ) mFIRE_FL_KN3=red_lamp; else mFIRE_FL_KN3=red_b_lamp;
    }
    else {
        mFIRE_FL_KN3=null_lamp;
    }

    if (uiNetCounter<35) LED_FIELD[35]=green_lamp; else LED_FIELD[35]=red_lamp;

	if(WaitWhenIronIsReady) return;
}

#include "Dev_kog.h"
uint8_t dev_option;
void Work_init()
{
	net_fl=0;
	fire_fl=0;
}

extern void pisk_drv();//см. ниже
extern void pause_pisk();//см. ниже
extern uint8_t fire_floor;
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

uint8_t counter_pk1,counter_pk2,counter_pk1_razr,counter_pk2_razr,counter_sps1,counter_sps2;
uint8_t counter_pk3,counter_pk4,counter_pk3_razr,counter_pk4_razr,counter_sps3,counter_sps4;
uint8_t counter_sps_all;
void fnFireFromPK1()
{
    if (kKNOP_FLOORE_1__1&&kKNOP_FLOORE_1__2) {
        if (counter_pk1) {
            if (!sec_tik) counter_pk1--;
        }
        else {
            fire_fl|=FIRE_FL_S_PK1;
        }
    }
    else {
        counter_pk1=time_fire;
    }

    if (fire_fl&FIRE_FL_S_PK1) {
        data_from_slave1.status|=FIRE_FL_1;
    }
    else {
        data_from_slave1.status&=~FIRE_FL_1;
    }
}

void fnFireFromPK2()
{
    if (kKNOP_FLOORE_2__1&&kKNOP_FLOORE_2__2) {
        if (counter_pk2) {
            if (!sec_tik) counter_pk2--;
        }
        else {
            fire_fl|=FIRE_FL_S_PK2;
        }
    }
    else {
        counter_pk2=time_fire;
    }

    if (fire_fl&FIRE_FL_S_PK2) {
        data_from_slave1.status|=FIRE_FL_2;
    }
    else {
        data_from_slave1.status&=~FIRE_FL_2;
    }
}

void fnFireFromPK3()
{
    if (kKNOP_FLOORE_3__1&&kKNOP_FLOORE_3__2) {
        if (counter_pk3) {
            if (!sec_tik) counter_pk3--;
        }
        else {
            fire_fl|=FIRE_FL_S_PK3;
        }
    }
    else {
        counter_pk3=time_fire;
    }

    if (fire_fl&FIRE_FL_S_PK3) {
        data_from_slave1.status|=FIRE_FL_3;
    }
    else {
        data_from_slave1.status&=~FIRE_FL_3;
    }
}

void fnFireFromPK1_razr()
{
    if (data_for_slave1.flag&FIRE_FL_PK_RAZR1) {
        if (counter_pk1_razr) {
            if (!sec_tik) counter_pk1_razr--;
        }
        else {
            fire_fl|=FIRE_FL_S_PK1_RAZ;
        }
    }
    else {
        counter_pk1_razr=time_fire;
    }

}
void fnFireFromPK2_razr()
{
    if (data_for_slave1.flag&FIRE_FL_PK_RAZR2) {
        if (counter_pk2_razr) {
            if (!sec_tik) counter_pk2_razr--;
        }
        else {
            fire_fl|=FIRE_FL_S_PK2_RAZ;
        }
    }
    else {
        counter_pk2_razr=time_fire;
    }
}
void fnFireFromPK3_razr()
{
    if (data_for_slave1.flag&FIRE_FL_PK_RAZR3) {
        if (counter_pk3_razr) {
            if (!sec_tik) counter_pk3_razr--;
        }
        else {
            fire_fl|=FIRE_FL_S_PK3_RAZ;
        }
    }
    else {
        counter_pk3_razr=time_fire;
    }
}

void fnFireFromSPS1()
{
    if (data_for_slave1.flag&FIRE_FL_SPS1) {
        if (counter_sps1) {
            if (!sec_tik) counter_sps1--;
        }
        else {
            fire_fl|=FIRE_FL_S_SPS1;
        }
    }
    else {
        counter_sps1=time_fire;
    }

}

void fnFireFromSPS2()
{
    if (data_for_slave1.flag&FIRE_FL_SPS2) {
        if (counter_sps2) {
            if (!sec_tik) counter_sps2--;
        }
        else {
            fire_fl|=FIRE_FL_S_SPS2;
        }
    }
    else {
        counter_sps2=time_fire;
    }
}

void fnFireFromSPS3()
{
    if (data_for_slave1.flag&FIRE_FL_SPS3) {
        if (counter_sps3) {
            if (!sec_tik) counter_sps3--;
        }
        else {
            fire_fl|=FIRE_FL_S_SPS3;
        }
    }
    else {
        counter_sps3=time_fire;
    }
}

void fnFireFromMasterAll()
{
    if (data_for_slave1.flag&FIRE_FL_ALL) {
        if (counter_sps_all) {
            if (!sec_tik) counter_sps_all--;
        }
        else {
            fire_fl|=FIRE_FL_S_ALL;
        }
    }
    else {
        counter_sps_all=time_fire;
    }
}

void Work_drv()
{
//========================================================================================
        if (data_for_slave1.flag&FIRE_FL_STOP_PDZ) {
            fire_fl=FIRE_FL_STOP_PDZ;
        }
        else {
            if (fire_fl&FIRE_FL_STOP_PDZ) {
                if (stop_pdz_counter) {
                    if (!sec_tik) stop_pdz_counter--;
                    fire_fl=FIRE_FL_STOP_PDZ;
                    data_from_slave1.status=0x0000;
                }
                else {
                    fire_fl&=~FIRE_FL_STOP_PDZ;
                }
            }
            else {
                stop_pdz_counter=time_fire;
                fnFireFromPK1();
                fnFireFromPK2();
                fnFireFromPK3();
                fnFireFromPK1_razr();
                fnFireFromPK2_razr();
                fnFireFromPK3_razr();
                fnFireFromSPS1();
                fnFireFromSPS2();
                fnFireFromSPS3();
                fnFireFromMasterAll();
            }
        }
/*
VZK view
*/
    for(i=0;i<35;i++) {
        //----------------------------
        if (*VZK_arr[i][1]) {
			data_from_slave1.VZK_FL1[i/8]|=(1<<(i%8));
		}
		else {
			data_from_slave1.VZK_FL1[i/8]&=~(1<<(i%8));
		}
    }
//========================================================================================

	pisk_drv();
	pause_pisk();
}

uint16_t pisk,pisk_cpy;
void check_avar_pisk()
{
	if(scafe_fl&(FIRE_ZONE|FIRE_ZONE_PK)) pisk|=(1<<0);
	else {
		if(!(KTEST)) {

		}//OP_ZUMER=1;
		else {
//			OP_ZUMER=0;
			pisk&=~(1<<0);
		}
	}
}

extern void set_sound();
extern void clr_sound();
void pause_pisk()
{
	if(KEY_NO/*||(!KTEST)*/)//сброс звука
	{
		pisk=0;
		check_avar_pisk();
		pisk_cpy=pisk;
		tech_fl&=~SOUND;
//		OP_ZUMER=0;
	}
}
void pisk_drv()
{
	check_avar_pisk();
	if(!pisk)
	{
		pisk_cpy=pisk;
		tech_fl&=~SOUND;
//		OP_ZUMER=0;
	}
	else if(pisk!=pisk_cpy)
	{
		tech_fl|=SOUND;
//		OP_ZUMER=1;
	}
}
