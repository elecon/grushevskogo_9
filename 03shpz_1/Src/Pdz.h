#ifndef __PDZ_H
	#define __PDZ_H
	#include "TechObj.h"
	#include "Menu.h"

	#include "../../scmRTOS/Target/AVR-GCC/Peripheral.h"
	#include "Nls.h"

	enum {PDZ_C_STOP,PDZ_C_WORK};
	enum {PDZ_ST_STOP,PDZ_ST_WORK};

	extern uint16_t fire_zone;
	#define FZ1		0x0001//����� � ����� ���2�1
	#define FZ2		0x0002//����� � ����� ���2�2
	#define FZ3		0x0004//����� � ����� ���2�3
	#define FZ4		0x0008//����� � ����� ���2�4
	#define FZ5		0x0010//����� � ����� ���2�5
	#define FZ6		0x0020//����� � ����� ���2�6
	#define FZ7		0x0040//����� � ����� ���2�7
	#define FZ8		0x0080//����� � ����� ���2�8
	#define FZ9		0x0100//����� � ����� ���2�9
	#define FZA		0x0200//����� � ����� ���2�(��)
	#define FZB		0x0400//����� � ����� ���2�(�)
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
