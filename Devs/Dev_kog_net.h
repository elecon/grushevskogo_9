#ifndef __DEVKOG_NET_H
	#define __DEVKOG_NET_H

	#include "DEVS.H"
    #include "Nls.h"

    #define T_WAIT_PRESS 5
    #define T_WAIT_MP 2

    #define PAUSE 5
    #define WORK 2

	enum {KOG_C_CLOSE,KOG_C_OPEN};
	//enum {KOGTT_C_CLOSE,KOGTT_C_OPEN};
	enum {  KOG_ST_CLOSE,   //0x01
            KOG_ST_OPEN,    //0x02
            KOG_ST_OPER,    //0x04
            KOG_ST_DIST,    //0x08
            KOG_ST_AVTO,    //0x10

            KOG_ST_ERR      //0x20
    };

	//флаги enh_info
//	#define KOG_CHECK_PRESS	0x8000 //проверка перепада давлени€
//	#define KOG_CHECK_MP	0x4000 //проверка состо€ни€ магнитного пускател€
//	#define KOG_CHECK_KTR	0x2000 //проверка состо€ни€ теплового реле
//	#define KOG_CHECK_OS	0x1000 //проверка обратной св€зи
//	#define KOG_OPER		0x0200 //устройство управл€етс€ оператором
//	#define KOG_DIST		0x0100 //устройство управл€етс€ дистанционно
//	#define KOG_PRESS_ERROR	0x0080 //ошибка перепада давлени€
//	#define KOG_MP_ERROR	0x0040 //ошибка магнитного пускател€
//	#define KOG_KTR_ERROR	0x0020 //ошибка теплового реле
//	#define KOG_OS_ERROR	0x0010 //ошибка обратной св€зи

    #define KOG_AUTO    	0x01 //
	#define KOG_OPER    	0x02 //
	#define KOG_DIST    	0x04 //
	#define KOG_OP      	0x08 //
	#define KOG_SUXAR   	0x80 //ошибка перепада давлени€
	#define KOG_CLOSE   	0x40 //ошибка магнитного пускател€
	#define KOG_STAN    	0x20 //ошибка теплового реле
	#define KOG_OS_ERROR	0x10 //ошибка обратной св€зи



	class KOG_NET: public TDevObject
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

			KOG_NET();
			KOG_NET (const prog_char* _name,
					uint8_t* _net_stan,
					uint8_t* _net_stad,
					uint8_t* _mn_os,
					uint8_t _num);
	};

#endif
