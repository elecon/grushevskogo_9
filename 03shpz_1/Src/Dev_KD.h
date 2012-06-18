#ifndef __DEVKD_H
	#define __DEVKD_H

	#include "DEVS.H"

	enum {KD_C_CLOSE,KD_C_OPEN};
	enum {KD_ST_CLOSE,KD_ST_OPEN};

	//флаги enh_info

	#define KD_CHECK_PRESS		0x8000 //проверка перепада давления
	#define KD_CHECK_MP			0x4000 //проверка состояния магнитного пускателя
	#define KD_CHECK_KTR		0x2000 //проверка состояния теплового реле
	#define KD_CHECK_OS			0x1000 //проверка обратной связи
	#define KD_OPER				0x0200 //устройство управляется оператором
	#define KD_DIST				0x0100 //устройство управляется дистанционно
	#define KD_PRESS_ERROR		0x0080 //ошибка перепада давления
	#define KD_MP_ERROR			0x0040 //ошибка магнитного пускателя
	#define KD_KTR_ERROR		0x0020 //ошибка теплового реле
	#define KD_OS_ERROR			0x0010 //ошибка обратной связи


	class KD: public TechObj
	{
		public:
			uint8_t *out;//выбор выхода
			uint8_t *k_press;
			uint8_t *os;//указатель на байт обратной связи
			uint8_t *k_mp;
			uint8_t *k_ktr;
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
			KD();
			KD(	const prog_char* _name,
					uint8_t* _mn_os,
					uint16_t enh_info,
					uint8_t* _out,
					uint8_t* _press,
					uint8_t* _os,
					uint8_t* _mp,
					uint8_t* _ktr);
	};

#endif
