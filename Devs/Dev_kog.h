#ifndef __DEVKOG_H
	#define __DEVKOG_H

	#include "DEVS.H"
    #include "Nls.h"

    #define T_WAIT_PRESS 5
    #define T_WAIT_MP 2

    #define PAUSE 5
    #define WORK 2

	enum {KOG_C_CLOSE,KOG_C_OPEN};
	enum {  KOG_ST_CLOSE,   //0x01
            KOG_ST_OPEN,    //0x02
            KOG_ST_OPER,    //0x04
            KOG_ST_DIST,    //0x08
            KOG_ST_AVTO,    //0x10

            KOG_ST_ERR      //0x20
    };
    #define KOG_AUTO    	0x01 //
	#define KOG_OPER    	0x02 //
	#define KOG_DIST    	0x04 //
	#define KOG_OP      	0x08 //
	#define KOG_SUXAR   	0x80 //ошибка перепада давления
	#define KOG_CLOSE   	0x40 //ошибка магнитного пускателя
	#define KOG_STAN    	0x20 //ошибка теплового реле
	#define KOG_OS_ERROR	0x10 //ошибка обратной связи

	class KogNum: public TDevObject
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
			KogNum(uint8_t _num);
	};

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
