#ifndef __SGWORK_H
	#define __SGWORK_H

	#include <avr/io.h>
	extern uint8_t LED_Out_Str[];
	extern uint8_t TestMSK,TestMSKResult;
	//uint8_t i_mt;
	//extern uint8_t MSK[8];

	#define NUM_OF_FLOOR    21
	#define time_fire 5


	extern uint16_t scafe_fl;//флаги scafe_fl
	extern uint16_t fire_fl;
	extern uint16_t alarm_fl;
	extern uint8_t fire_floor;
    extern uint8_t fire_floor1;
    extern uint8_t fire_floor2;
    extern uint8_t fire_floor3;
	#define FIRE_ZONE		0x0001
	#define FIRE_ZONE_PK	0x0002
	#define FIRE_ZONE_3		0x0004
	#define FIRE_ZONE_4		0x0008
	#define FIRE_SB			0x0010
	#define SCAFE_STOP_PDZ	0x0080
	#define SCAFE_T_MT_OP	0x0040
	#define SCAFE_TEST_MT	0x0080
	#define SCAFE_FIRE		0x0100
	#define SCAFE_FIRE_NET	0x0200

	#define RED				0x0400
	#define GREEN			0x0800
	#define YELLOW			0x1000
	#define FREEZ			0x2000
	#define FIELD			0x4000
	#define MNEMO_WRK		0x8000
	//TechFlag
	extern uint8_t TechFlag;
	#define TEST_MT			0x01
	#define TEST_MSK		0x02

	extern uint16_t net_fl;//флаги наличия шкафов в сети
	extern uint16_t fire_sps;//флаги пожаров от СПС
	extern uint16_t fire_sb;//флаги пожаров от ПК
	extern uint16_t fire_net;//флаги пожаров из сети
	extern uint16_t fire_vzk;//флаги пожаров ОЗК
	extern uint16_t stop_fl;//флаги стопов шкафов
	#define Sh1		0x0001// ЩПЗ2П1
	#define Sh2		0x0002// ЩПЗ2П2
	#define Sh3		0x0004// ЩПЗ2П3
	#define Sh4		0x0008// ЩПЗ2П4
	#define Sh5		0x0010// ЩПЗ2П5
	#define Sh6		0x0020// ЩПЗ2П6
	#define Sh7		0x0040// ЩПЗ2П7
	#define Sh8		0x0080// ЩПЗ2П8
	#define Sh9		0x0100// ЩПЗ2П9
	#define ShA		0x0200// ЩПЗ2П(АБ)
	#define ShB		0x0400// ЩПЗ2П(В)







	///////////////////////////////////////////////////////////////////
	//типа статус и команды слейвов
	extern uint8_t status;//флаги status
	#define SFIRE_SPS		0x0001//
	#define SFIRE_KEY		0x0002//
	#define SFIRE_VZK		0x0004//
	#define SFIRE_NET		0x0008//
	#define STOP_PDZ		0x0010//
	//#define FIRE			0x0020//

	extern uint8_t cmd;//флаги cmd
	#define FIRE_ZONE	0x0001//
	#define FIRE_VZK	0x0002//
	//#define FIRE		0x0004//
	#define STOP_NET	0x0008//

    enum {
        NET_WORK_SHPZ02,
        NET_WORK_SHPZ3,
        NET_WORK_SHPZ6,
        NET_WORK_SHPZ9,
        NET_WORK_SHPZ11,

        NET_WORK_SHPZ14,
        NET_WORK_SHPZ16,
        NET_WORK_SHPZ18,
        NET_WORK_SHPZ20,
        NET_WORK_SHPZ21,
    };
#endif
