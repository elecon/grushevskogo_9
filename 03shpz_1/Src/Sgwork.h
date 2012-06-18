#ifndef __SGWORK_H
	#define __SGWORK_H

	#include <avr/io.h>
	extern uint8_t LED_Out_Str[];
	extern uint8_t TestMSK,TestMSKResult;
	//uint8_t i_mt;
	//extern uint8_t MSK[8];
	extern uint16_t scafe_fl;//����� scafe_fl
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

    extern uint16_t fire_fl;
//    #define FIRE_FL_PK1          0x0001
//    #define FIRE_FL_PK2          0x0002
//    #define FIRE_FL_PK_RAZR1     0x0004
//    #define FIRE_FL_PK_RAZR2     0x0008
//    #define FIRE_FL_ALL          0x0010
//    #define FIRE_FL_SPS1         0x0020
//    #define FIRE_FL_SPS2         0x0040
//    #define FIRE_FL_STOP_PDZ     0x0080

	extern uint16_t net_fl;//����� ������� ������ � ����
	extern uint16_t fire_sps;//����� ������� �� ���
	extern uint16_t fire_sb;//����� ������� �� ��
	extern uint16_t fire_net;//����� ������� �� ����
	extern uint16_t fire_vzk;//����� ������� ���
	extern uint16_t stop_fl;//����� ������ ������



//    //from slave
//    #define FIRE_FL_1           0x01
//    #define FIRE_FL_2           0x02
//    #define FIRE_FL_3           0x04
//    #define FIRE_FL_4           0x08

    //from slave
    #define FIRE_FL_1           0x01
    #define FIRE_FL_2           0x02
    #define FIRE_FL_3           0x04
    #define FIRE_FL_4           0x08


	///////////////////////////////////////////////////////////////////
	//���� ������ � ������� �������
	extern uint8_t status;//����� status
	#define SFIRE_SPS		0x0001//
	#define SFIRE_KEY		0x0002//
	#define SFIRE_VZK		0x0004//
	#define SFIRE_NET		0x0008//
	#define STOP_PDZ		0x0010//
	//#define FIRE			0x0020//

	extern uint8_t cmd;//����� cmd
	#define FIRE_ZONE	0x0001//
	#define FIRE_VZK	0x0002//
	//#define FIRE		0x0004//
	#define STOP_NET	0x0008//


#endif
