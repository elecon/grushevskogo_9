#ifndef __PDZ_H
	#define __PDZ_H
	#include "TechObj.h"
	#include "Menu.h"

	#include "../../scmRTOS/Target/AVR-GCC/Peripheral.h"
	#include "Nls.h"

	enum {PDZ_C_STOP,PDZ_C_WORK};
	enum {PDZ_ST_STOP,PDZ_ST_WORK};

	extern uint16_t fire_zone;
	#define FZ1		0x0001//пожар в шкафу ЩПЗ2П1
	#define FZ2		0x0002//пожар в шкафу ЩПЗ2П2
	#define FZ3		0x0004//пожар в шкафу ЩПЗ2П3
	#define FZ4		0x0008//пожар в шкафу ЩПЗ2П4
	#define FZ5		0x0010//пожар в шкафу ЩПЗ2П5
	#define FZ6		0x0020//пожар в шкафу ЩПЗ2П6
	#define FZ7		0x0040//пожар в шкафу ЩПЗ2П7
	#define FZ8		0x0080//пожар в шкафу ЩПЗ2П8
	#define FZ9		0x0100//пожар в шкафу ЩПЗ2П9
	#define FZA		0x0200//пожар в шкафу ЩПЗ2П(АБ)
	#define FZB		0x0400//пожар в шкафу ЩПЗ2П(В)
	///////////////////////////////////////////////////////////////////
	class Pdz: public TechObj
	{
		public:
			void drv();
			void (*pdrv)();
			void init();
			void show_mnem();
			void show_lcd();
			void (*pshow_lcd)();
			void to_stad(uint8_t _stad, uint8_t _sub_st);
			uint8_t *mn_os;
	};
#endif
