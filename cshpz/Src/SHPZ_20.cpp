#include "SHPZ_20.h"
#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"

extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

uint8_t net_status_counter_20[FLOOR_NUM_20];

extern NET_OUTPUT_STRUCT1 data_from_slave20;
extern NET_INPUT_STRUCT1 data_for_slave20;
//extern const prog_char strKPD181[] PROGMEM;

const prog_char strKPD20[]="йод20";
const prog_char strVZK20[]="бгй20";
const prog_char strDU232[]="дс232";
const prog_char strDU231[]="дс231";
const prog_char strDU221[]="дс221";
const prog_char strDU211[]="дс211";
const prog_char strPP282[]="оо282";
const prog_char strPP2152[]="оо2152";
const prog_char strPP212[]="оо212";
const prog_char strPP2201[]="оо2201";
const prog_char strV1[]="б14";
const prog_char strV203[]="б203";
const prog_char strZOV20[]="гнб20";
const prog_char strGAZ20[]="цюг20";
const prog_char strLIFT[]="кхтр";

//MOE <76,MSK_NUMER_MOE,2,OPT_CHECK_PRESS|OPT_CHECK_MP|OPT_CHECK_OS,dev_name_str_moe> GR4;
MOE_NET <61+80*1,strKPD20,&data_from_slave20,&data_for_slave20,0,NET_WORK_SHPZ20> KPD20;
KOGT_NET<57+80*0,strVZK20,&data_from_slave20,&data_for_slave20,1,NET_WORK_SHPZ20> VZK20;
KOGT_NET<69+80*1,strDU232,&data_from_slave20,&data_for_slave20,2,NET_WORK_SHPZ20> DU232;
KOGT_NET<23+80*0,strDU231,&data_from_slave20,&data_for_slave20,3,NET_WORK_SHPZ20> DU231;
KOGT_NET<22+80*0,strDU221,&data_from_slave20,&data_for_slave20,4,NET_WORK_SHPZ20> DU221;
KOGT_NET<21+80*0,strDU211,&data_from_slave20,&data_for_slave20,5,NET_WORK_SHPZ20> DU211;
KOGT_NET<61+80*0,strPP282,&data_from_slave20,&data_for_slave20,6,NET_WORK_SHPZ20> PP282;
KOGT_NET<62+80*0,strPP2152,&data_from_slave20,&data_for_slave20,7,NET_WORK_SHPZ20> PP2152;
KOGT_NET<63+80*0,strPP212,&data_from_slave20,&data_for_slave20,8,NET_WORK_SHPZ20> PP212;
KOGT_NET<16+80*1,strPP2201,&data_from_slave20,&data_for_slave20,9,NET_WORK_SHPZ20> PP2201;
KOGT_NET<59+80*0,strV1,&data_from_slave20,&data_for_slave20,10,NET_WORK_SHPZ20> V1;
KOGT_NET<60+80*0,strV203,&data_from_slave20,&data_for_slave20,11,NET_WORK_SHPZ20> V203;

ZOVT_NET <67+80*0,strZOV20,&data_from_slave20,&data_for_slave20,12,NET_WORK_SHPZ20> ZOV20;
ZOVT_NET <68+80*0,strGAZ20,&data_from_slave20,&data_for_slave20,13,NET_WORK_SHPZ20> GAZ20;
ZOVT_NET <69+80*0,strLIFT,&data_from_slave20,&data_for_slave20,14,NET_WORK_SHPZ20> LIFT20;
//-------------------------
//MOE > KPD20;
//KOGT <> VZK20;
//KOGT <> DU232;
//KOGT <> DU231;
//KOGT <> DU221;
//KOGT <> DU211;
//KOGT <> PP282;
//KOGT <> PP2152;
//KOGT <> PP212;
//KOGT <> PP2201;
//
//KOGT <> V1;
//KOGT <> V203;
//
//ZOVT <> ZOV20;
//ZOVT <> GAZ20;
//ZOVT <> LIFT;

TDevObject* pDevs_arr_20[]=
{
	&KPD20,
	&VZK20,
	&DU232,
	&DU231,
	&DU221,

	&DU211,
	&PP282,
	&PP2152,
	&PP212,
	&PP2201,

	&V1,
	&V203,
	&ZOV20,
	&GAZ20,
	&LIFT20,
};



extern uint16_t i;
void Shpz_20_Ind()
{


}

void Shpz_20_Work()
{
    for (i=0;i<FLOOR_NUM_20;i++) {
        if (fire_fl&(FIRE_FL_M_PK3|FIRE_FL_M_SPS3)){
            if (fire_fl&FIRE_FL_M_PK3) {
                if (fire_floor3==(20+i)) data_for_slave20.flag|=(1<<i); else data_for_slave20.flag&=~(1<<i);
            }
            if (fire_fl&FIRE_FL_M_SPS3) {
                if (fire_floor3==(20+i)) data_for_slave20.flag|=(1<<(i+4)); else data_for_slave20.flag&=~(1<<(i+4));
            }
        }
        else {
            if (data_from_slave20.status&(1<<i)) {
                if (net_status_counter_20[i]) {
                    if (!sec_tik) net_status_counter_20[i]--;
                }
                else
                {
                    if (!(fire_floor==20+i)) alarm_fl|=0x0001;
                    fire_floor=20+i;
                    if (fire_floor3==0xff) fire_floor3=20+i;
                    fire_fl=FIRE_FL_M_PK3;
                }
            }
            else
            {
                net_status_counter_20[i]=COUNTER_NET_STATUS;
            }
        }
    }
}

void Shpz_20_StopPdz()
{
    net_status_counter_20[0]=COUNTER_NET_STATUS;
    net_status_counter_20[1]=COUNTER_NET_STATUS;
    net_status_counter_20[2]=COUNTER_NET_STATUS;
    for (i=0;i<FLOOR_NUM_20;i++) {
        data_from_slave20.status&=~(1<<i);
    }
}

