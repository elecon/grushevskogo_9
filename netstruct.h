/*
$Author$
$Date$
$Tag$
$IdShort$
$Id$
$IdInfo$
*/

#ifndef __NET_STRUCT_H
	#define __NET_STRUCT_H

    #define COUNTER_NET_STATUS      5
//-----------------------------------------------
	typedef struct
	{
		uint8_t size;
		uint8_t adr;
		uint8_t cmd;
	}HEAD_NET_STRUCT;//3байта

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_stat[16];//
		uint8_t VZK_FL1[4];
		uint8_t VZK_FL2[4];
		uint16_t status;
	}NET_OUTPUT_STRUCT1;

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_cmd[16];//
		uint16_t flag;
	}NET_INPUT_STRUCT1;

    //from slave
    #define FIRE_FL_1               0x01
    #define FIRE_FL_2               0x02
    #define FIRE_FL_3               0x04
    #define FIRE_FL_4               0x08


    //for slave--------------------------------------

    #define FIRE_FL_PK_RAZR1        0x0001
    #define FIRE_FL_PK_RAZR2        0x0002
    #define FIRE_FL_PK_RAZR3        0x0004
    #define FIRE_FL_PK_RAZR4        0x0008

    #define FIRE_FL_SPS1            0x0010
    #define FIRE_FL_SPS2            0x0020
    #define FIRE_FL_SPS3            0x0040
    #define FIRE_FL_SPS4            0x0080


    #define FIRE_FL_ALL             0x1000

    #define FIRE_FL_STOP_PDZ        0x8000


    //fire on master
    #define FIRE_FL_M_PK1            0x0001
    #define FIRE_FL_M_PK2            0x0002
    #define FIRE_FL_M_PK3            0x0004
    #define FIRE_FL_M_SPS1           0x0008
    #define FIRE_FL_M_SPS2           0x0010
    #define FIRE_FL_M_SPS3           0x0020
    #define FIRE_FL_M_ALL            0x0040
    #define FIRE_FL_M_STOP_PDZ       0x8000

     //fire on slave
    #define FIRE_FL_S_PK1            0x0001
    #define FIRE_FL_S_PK2            0x0002
    #define FIRE_FL_S_PK3            0x0004
    #define FIRE_FL_S_PK4            0x0008
    #define FIRE_FL_S_SPS1           0x0010
    #define FIRE_FL_S_SPS2           0x0020
    #define FIRE_FL_S_SPS3           0x0040
    #define FIRE_FL_S_SPS4           0x0080

    #define FIRE_FL_S_PK1_RAZ        0x0100
    #define FIRE_FL_S_PK2_RAZ        0x0200
    #define FIRE_FL_S_PK3_RAZ        0x0400
    #define FIRE_FL_S_PK4_RAZ        0x0800

    #define FIRE_FL_S_ALL            0x1000

    #define FIRE_FL_S_STOP_PDZ       0x8000

#endif
