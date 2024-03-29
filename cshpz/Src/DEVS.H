#ifndef __DEVS_H
	#define __DEVS_H

	#include "../../scmRTOS/Common/scmRTOS.h"
	#include "../../scmRTOS/Target/AVR-GCC/Peripheral.h"

	#include "TechObj.h"
	#include "Menu.h"
	#include "Dev_VZK.h"

	#include "CSHPZ.h"
    #include "SHPZ_02.h"
//    #include "SHPZ_3.h"
//    #include "SHPZ_6.h"
//    #include "SHPZ_9.h"
//    #include "SHPZ_11.h"
//    #include "SHPZ_14.h"
//    #include "SHPZ_16.h"
//    #include "SHPZ_18.h"
//    #include "SHPZ_20.h"
//    #include "SHPZ_21.h"

    // OPTIONS defines
    #define OPT_CHECK_PRESS	0x8000 //�������� �������� �����
	#define OPT_CHECK_MP	0x4000 //�������� ����� ���������� �������
	#define OPT_CHECK_KTR	0x2000 //�������� ����� ��������� ����
	#define OPT_CHECK_OS	0x1000 //�������� ����������� ������
	extern uint8_t sec_tik;

    extern const uint16_t Dev_constr_info[];
	extern const uint8_t Dev_constr[][6];
	extern const prog_char dev_name_str[][5] PROGMEM;

	//typedef char[5] devMoeString;

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

//    extern const prog_char strKPD181[] PROGMEM;
////    const prog_char strKPD181[] PROGMEM = "���181";
//    extern const prog_char strKPD182[] PROGMEM;
////    const prog_char strKPD182[]="���182";
//    extern const prog_char strKPD191[] PROGMEM;
////    const prog_char strKPD191[]="���191";
//    extern const prog_char strKPD192[] PROGMEM;
////    const prog_char strKPD192[]="���192";
//    extern const prog_char strPP218[] PROGMEM;
////    const prog_char strPP218[]="��218";
//    extern const prog_char strPP219[] PROGMEM;
////    const prog_char strPP219[]="��219";
//    extern const prog_char strZOV18[] PROGMEM;
////    const prog_char strZOV18[]="���18";
//    extern const prog_char strZOV19[] PROGMEM;
////    const prog_char strZOV19[]="���19";
//    extern const prog_char strDVR[] PROGMEM;
////    const prog_char strDVR[]="���";
//    extern const prog_char strVZK1[] PROGMEM;
//    extern const prog_char strVZK2[] PROGMEM;
//    extern const prog_char strVZK3[] PROGMEM;
//    extern const prog_char strVZK4[] PROGMEM;
//    extern const prog_char strVZK5[] PROGMEM;
//    extern const prog_char strVZK6[] PROGMEM;
//    const prog_char strVZK1[]="���1";
//    const prog_char strVZK2[]="���2";
//    const prog_char strVZK3[]="���3";
//    const prog_char strVZK4[]="���4";
//    const prog_char strVZK5[]="���5";
//    const prog_char strVZK6[]="���6";
#endif
