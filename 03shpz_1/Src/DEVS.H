#ifndef __DEVS_H
	#define __DEVS_H

	#include "../../scmRTOS/Common/scmRTOS.h"
	#include "../../scmRTOS/Target/AVR-GCC/Peripheral.h"

	#include "TechObj.h"
	#include "Menu.h"
	//#include "Dev_VZK.h"
    // OPTIONS defines
    #define OPT_CHECK_PRESS	0x8000 //�������� �������� �����
	#define OPT_CHECK_MP	0x4000 //�������� ����� ���������� �������
	#define OPT_CHECK_KTR	0x2000 //�������� ����� ��������� ����
	#define OPT_CHECK_OS	0x1000 //�������� ����������� ������
	extern uint8_t sec_tik;

	//typedef char[5] devMoeString;
	extern const uint16_t Dev_constr_info[];
	extern const uint8_t Dev_constr[][6];
	extern const prog_char dev_name_str[][5] PROGMEM;

	//extern XZ moe;
	extern const prog_char stad_str[4][3] PROGMEM;
//	const prog_char stad_str[4][3]=
//	{
//		"OP",
//		"CL",
//		"ST",
//		"ER"
//	};

    extern const prog_char mode_str[3][5] PROGMEM;
//	const prog_char mode_str[3][5]=
//	{
//		"����",
//		"����",
//		"����"
//	};

    extern const prog_char error_str[] PROGMEM;
//    const prog_char err_str[] = "��";
    extern const prog_char press_err_str[] PROGMEM;
//    const prog_char press_err_str[] = "����";
    extern const prog_char mp_err_str[] PROGMEM;
//	const prog_char mp_err_str[] = "��";
	extern const prog_char ktr_err_str[] PROGMEM;
//	const prog_char ktr_err_str[] = "���";
	extern const prog_char os_err_str[] PROGMEM;
//	const prog_char os_err_str[] = "��";
    extern const prog_char stan_err_str[] PROGMEM;
//    const prog_char stan_err_str[]      = "C���";
    extern const prog_char auto_str[] PROGMEM;
//    const prog_char auto_str[] = "����";
	extern const prog_char dist_str[] PROGMEM;
//	const prog_char dist_str[] = "����";
	extern const prog_char oper_str[] PROGMEM;
//	const prog_char oper_str[] = "����";
    extern const prog_char vidk_str[] PROGMEM;
//    const prog_char vidk_str[]          = "�i��";
	extern const prog_char zakr_str[] PROGMEM;
//	const prog_char zakr_str[]          = "����";

    extern const prog_char strKPD11[] PROGMEM;
    extern const prog_char strKPD12[] PROGMEM;
    extern const prog_char strKPD21[] PROGMEM;
    extern const prog_char strKPD22[] PROGMEM;
    extern const prog_char strKPD31[] PROGMEM;
    extern const prog_char strKPD32[] PROGMEM;
    extern const prog_char strPP1[] PROGMEM;
    extern const prog_char strPP2[] PROGMEM;
    extern const prog_char strPP3[] PROGMEM;
    extern const prog_char strZOV1[] PROGMEM;
    extern const prog_char strZOV2[] PROGMEM;
    extern const prog_char strZOV3[] PROGMEM;

    extern const prog_char strVZK1[] PROGMEM;
    extern const prog_char strVZK2[] PROGMEM;
    extern const prog_char strVZK3[] PROGMEM;

    extern const prog_char noll_str[] PROGMEM;
	extern const prog_char one_str[] PROGMEM;

//    const prog_char strVZK1[]="���1";
//    const prog_char strVZK2[]="���2";
//    const prog_char strVZK3[]="���3";
//    const prog_char strVZK4[]="���4";
//    const prog_char strVZK5[]="���5";
//    const prog_char strVZK6[]="���6";
#endif
