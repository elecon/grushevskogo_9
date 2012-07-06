#ifndef __DEVKPD_H
	#define __DEVKPD_H

	#include "DEVS.H"
    #include "Nls.h"

    #define T_WAIT_PRESS 5
    #define T_WAIT_MP 2

    #define PAUSE 5
    #define WORK 2

	enum {KPD_C_CLOSE,KPD_C_OPEN};
	//enum {KOGTT_C_CLOSE,KOGTT_C_OPEN};
	enum {  KPD_ST_CLOSE,   //0x01
            KPD_ST_OPEN,    //0x02
            KPD_ST_OPER,    //0x04
            KPD_ST_DIST,    //0x08
            KPD_ST_AVTO,    //0x10

            KPD_ST_ERR      //0x20
    };

	//флаги enh_info
//	#define KOG_CHECK_PRESS	0x8000 //проверка перепада давлени€
//	#define KOG_CHECK_MP	0x4000 //проверка состо€ни€ магнитного пускател€
//	#define KOG_CHECK_KTR	0x2000 //проверка состо€ни€ теплового реле
//	#define KOG_CHECK_OS	0x1000 //проверка обратной св€зи
//	#define KPD_OPER		0x0200 //устройство управл€етс€ оператором
//	#define KPD_DIST		0x0100 //устройство управл€етс€ дистанционно
//	#define KOG_PRESS_ERROR	0x0080 //ошибка перепада давлени€
//	#define KOG_MP_ERROR	0x0040 //ошибка магнитного пускател€
//	#define KOG_KTR_ERROR	0x0020 //ошибка теплового реле
//	#define KPD_OS_ERROR	0x0010 //ошибка обратной св€зи

    #define KPD_AUTO    	0x01 //
	#define KPD_OPER    	0x02 //
	#define KPD_DIST    	0x04 //
	#define KPD_OP      	0x08 //
	#define KPD_SUXAR   	0x80 //ошибка перепада давлени€
	#define KPD_CLOSE   	0x40 //ошибка магнитного пускател€
	#define KPD_STAN    	0x20 //ошибка теплового реле
	#define KPD_OS_ERROR	0x10 //ошибка обратной св€зи


	class KogKpd: public TDevObject
	{
		public:
			uint16_t enh_info;
			uint8_t num;


			uint8_t t_repit_counter;
            uint8_t t_kog_wait;

			uint16_t t_wait_press;
			uint16_t t_wait_press_counter;
			uint16_t t_wait_mp;
			uint16_t t_wait_mp_counter;
			void drv();
			void show_mnem();
			void show_lcd();
			void check_press();
			void check_mp();
			void check_ktr();
			void check_os();
			void auto_open();
			void auto_close();
			KogKpd();
			KogKpd(uint8_t _num);
	};

    class KpdNet: public TDevObject
	{
		public:
            uint8_t *net_stan;
            uint8_t *net_stad;
            uint8_t *mn_os;
            uint8_t num;
			const prog_char *name;
			void drv();
			void show_mnem();
			void show_lcd();

			KpdNet();
			KpdNet (const prog_char* _name,
					uint8_t* _net_stan,
					uint8_t* _net_stad,
					uint8_t* _mn_os,
					uint8_t _num);
	};

#endif
