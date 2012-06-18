#include "SHPZ_21.h"
#include "SHPZ_20.h"

#include "../../Devs/Dev_kog_t.h"
#include "../../Devs/Dev_moe.h"
#include "../../Devs/Dev_zov_t.h"


extern uint16_t fire_fl;
extern uint8_t fire_floor;
extern uint8_t fire_floor1;
extern uint8_t fire_floor2;
extern uint8_t fire_floor3;

//uint8_t net_status_counter_21[FLOOR_NUM_21];

extern NET_OUTPUT_STRUCT1 data_from_slave21;
extern NET_INPUT_STRUCT1 data_for_slave21;

const prog_char strDU222[]="дс222";
const prog_char strDU231_21[]="дс231";
const prog_char strDU212[]="дс212";
const prog_char strDU221_21[]="дс221";

const prog_char strPP213[]="оо213";
const prog_char strPP214[]="оо214";
const prog_char strPP215[]="оо215";

const prog_char strV2[]="б2";
const prog_char strV221[]="б221";
const prog_char strV231[]="б231";

//extern const prog_char strLIFT[];
//const prog_char strLIFT[]="кхтр";

KOGT_NET<62+80*1,strDU222,&data_from_slave21,&data_for_slave21,     0,NET_WORK_SHPZ21> DU222;
KOGT_NET< 0+80*0,strDU231_21,&data_from_slave21,&data_for_slave21,  1,NET_WORK_SHPZ21> DU231_21;
KOGT_NET<63+80*1,strDU212,&data_from_slave21,&data_for_slave21,     2,NET_WORK_SHPZ21> DU212;
KOGT_NET< 0+80*0,strDU221_21,&data_from_slave21,&data_for_slave21,  3,NET_WORK_SHPZ21> DU221_21;

KOGT_NET<19+80*1,strPP213,&data_from_slave21,&data_for_slave21,     4,NET_WORK_SHPZ21> PP213;
KOGT_NET<20+80*1,strPP214,&data_from_slave21,&data_for_slave21,     5,NET_WORK_SHPZ21> PP214;
KOGT_NET<21+80*1,strPP215,&data_from_slave21,&data_for_slave21,     6,NET_WORK_SHPZ21> PP215;

KOGT_NET<22+80*1,strV2,&data_from_slave21,&data_for_slave21,        7,NET_WORK_SHPZ21> V2;
KOGT_NET< 0+80*0,strV221,&data_from_slave21,&data_for_slave21,      8,NET_WORK_SHPZ21> V221;
KOGT_NET< 0+80*0,strV231,&data_from_slave21,&data_for_slave21,      9,NET_WORK_SHPZ21> V231;
ZOVT_NET<64+80*0,strLIFT,&data_from_slave21,&data_for_slave21,     10,NET_WORK_SHPZ21> LIFT21;


TDevObject* pDevs_arr_21[]=
{

	&DU222,
	&DU231_21,
	&DU212,
	&DU221_21,
	&PP213,

	&PP214,
	&PP215,
	&V2,
	&V221,
	&V231,

	&LIFT21,
};
