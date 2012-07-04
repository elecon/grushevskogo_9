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
    #define OPT_CHECK_PRESS	0x8000 //перевірка перепаду тиску
	#define OPT_CHECK_MP	0x4000 //перевірка стану магнітного пускача
	#define OPT_CHECK_KTR	0x2000 //перевірка стану теплового реле
	#define OPT_CHECK_OS	0x1000 //перевірка зворотнього звязку
	extern uint8_t sec_tik;

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
//		"АВТО",
//		"ОПЕР",
//		"ДИСТ"
//	};

    extern const prog_char error_str[] PROGMEM;
//    const prog_char err_str[] = "ОШ";
    extern const prog_char press_err_str[] PROGMEM;
//    const prog_char press_err_str[] = "тиск";
    extern const prog_char mp_err_str[] PROGMEM;
//	const prog_char mp_err_str[] = "МП";
	extern const prog_char ktr_err_str[] PROGMEM;
//	const prog_char ktr_err_str[] = "КТР";
	extern const prog_char os_err_str[] PROGMEM;
//	const prog_char os_err_str[] = "ОС";
    extern const prog_char stan_err_str[] PROGMEM;
//    const prog_char stan_err_str[]      = "CТАН";
    extern const prog_char auto_str[] PROGMEM;
//    const prog_char auto_str[] = "АВТО";
	extern const prog_char dist_str[] PROGMEM;
//	const prog_char dist_str[] = "ОПЕР";
	extern const prog_char oper_str[] PROGMEM;
//	const prog_char oper_str[] = "ДИСТ";
    extern const prog_char vidk_str[] PROGMEM;
//    const prog_char vidk_str[]          = "Вiдк";
	extern const prog_char zakr_str[] PROGMEM;
//	const prog_char zakr_str[]          = "Закр";

//    extern const prog_char strKPD181[] PROGMEM;
////    const prog_char strKPD181[] PROGMEM = "КПД181";
//    extern const prog_char strKPD182[] PROGMEM;
////    const prog_char strKPD182[]="КПД182";
//    extern const prog_char strKPD191[] PROGMEM;
////    const prog_char strKPD191[]="КПД191";
//    extern const prog_char strKPD192[] PROGMEM;
////    const prog_char strKPD192[]="КПД192";
//    extern const prog_char strPP218[] PROGMEM;
////    const prog_char strPP218[]="ПП218";
//    extern const prog_char strPP219[] PROGMEM;
////    const prog_char strPP219[]="ПП219";
//    extern const prog_char strZOV18[] PROGMEM;
////    const prog_char strZOV18[]="ЗОВ18";
//    extern const prog_char strZOV19[] PROGMEM;
////    const prog_char strZOV19[]="ЗОВ19";
//    extern const prog_char strDVR[] PROGMEM;
////    const prog_char strDVR[]="ДВР";
//    extern const prog_char strVZK1[] PROGMEM;
//    extern const prog_char strVZK2[] PROGMEM;
//    extern const prog_char strVZK3[] PROGMEM;
//    extern const prog_char strVZK4[] PROGMEM;
//    extern const prog_char strVZK5[] PROGMEM;
//    extern const prog_char strVZK6[] PROGMEM;
//    const prog_char strVZK1[]="ВЗК1";
//    const prog_char strVZK2[]="ВЗК2";
//    const prog_char strVZK3[]="ВЗК3";
//    const prog_char strVZK4[]="ВЗК4";
//    const prog_char strVZK5[]="ВЗК5";
//    const prog_char strVZK6[]="ВЗК6";
#endif
