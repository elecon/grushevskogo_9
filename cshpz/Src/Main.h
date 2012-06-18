#ifndef __MAIN_H
	#define __MAIN_H

	#include <avr/io.h>
	//#include <avr/pgmspace.h>

	#include "../../scmRTOS/Common/scmRTOS.h"
	#include "../../scmRTOS/Target/AVR-GCC/Uart.h"

	#include <string.h>
	#include "../../netstruct.h"

	//tech_fl
	extern uint8_t tech_fl;
	#define DIG_INPUT	0x01
	#define DIG_MINUS	0x02
	#define DEFAULT_SET	0x04
	#define IIC_BUSY	0x08
	#define NO_IIC		0x10
	#define SOUND		0x20
	#define SOUND_KEY	0x40

	#define NUM_OF_SCAF 10
	#define ZSUV 1


	extern uint16_t AN_VALUE[8];
	extern uint8_t sec_tik;
	extern uint8_t ProcesFlag;
	extern void Menu_init();
	extern void Menu_drv();
	extern void Meas_init();
	extern void Meas_drv();
	extern void Work_init();
	extern void Work_drv();
	extern void all_ind();
	extern void Dev_init();
	extern void Dev_drv();
	extern void LCD_init();
	extern void drv_LCD(char*);
	extern void drv_Led();
	extern void Init_iic();
	extern void Pdz_init();
	extern void Pdz_drv();
	extern void Etaz_init();
	extern void Etaz_drv();
	extern void check_iic_status();
	extern void Message_init();
	extern void Message_drv();
	extern void low_init();
	extern uint8_t KEY[];

//	typedef struct
//	{
//		uint8_t size;
//		uint8_t adr;
//		uint8_t cmd;
//	}HEAD_NET_STRUCT;//3байта
//////////////////////////////////////////////////////////////////////////////////
//STRUCTN: N=NUM_OF_SCAF!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//-----------------------------------------------
/*
	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_stat[13];//
		uint8_t status;
//		uint8_t lamps[13];
		uint8_t foo;
	}NET_INPUT_STRUCT1;

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_cmd[13];//
//		uint8_t cmd;
		uint8_t flag;
	}NET_OUTPUT_STRUCT1;
*/
//-----------------------------------------------
    typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t out_led;
		uint8_t foo1;
		uint8_t foo2;
		uint8_t foo3;
	}NET_BFPP_OUTPUT_STRUCT;

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t msk1;
		uint8_t msk2;
		uint8_t status;
		uint8_t dip;
		uint8_t status1;
	}NET_BFPP_INPUT_STRUCT;
////-----------------------------------------------
//	typedef struct
//	{
//		HEAD_NET_STRUCT head;
//		uint8_t devs_net_stat[16];//
//		uint8_t VZK_FL1[4];
//		uint8_t VZK_FL2[4];
//		uint16_t status;
//	}NET_OUTPUT_STRUCT1;
//
//	typedef struct
//	{
//		HEAD_NET_STRUCT head;
//		uint8_t devs_net_cmd[16];//
//		uint8_t flag;
//	}NET_INPUT_STRUCT1;


	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_stat[9];//
		uint8_t status;
	}NET_OUTPUT_STRUCT2;

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_cmd[3];//
		uint8_t flag;
	}NET_INPUT_STRUCT2;

//-------------------------------------------------------------------
/*
	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_stat[13];//
		uint8_t status;
	}NET_INPUT_STRUCT2;

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_cmd[13];//
		uint8_t flag;
	}NET_OUTPUT_STRUCT2;
//----------------------------------------------------

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_stat[9];//
		uint8_t status;
	}NET_INPUT_STRUCT3;

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t devs_net_cmd[9];//
		uint8_t flag;
	}NET_OUTPUT_STRUCT3;
*/
////////////////////////////////////////////////////////////////////////////
	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t out_lcd[44];//36
	}LCD_OUTPUT_STRUCT;

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t key[2];
	}LCD_INPUT_STRUCT;

	typedef struct
	{
		HEAD_NET_STRUCT head;
		uint8_t rg_led[81];
	}MNEMO_OUTPUT_STRUCT;


#endif
