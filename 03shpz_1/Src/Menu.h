#ifndef __MENU_H
	#define __MENU_H

	#include "Main.h"

	#define LEAD_ZERO 0x40 //ставить впереди 0
	#define LEFT_ALIGN 0x80

	#define CLEAR_LENGTH(b) ((b)&0x3f)//младшие 6 битов на длину

	enum {
	EMenuGlob,

	EMenuPDZ,
	EMenuDevs,
	EMenuSet,
	EMenuTest,
	EMenuMassage,
	EMenuVersion,

	EMenuPdzSet,
	EMenuDevSet,
	EMenuSysSet,

	EMenuResSet,

	EMenuTimeSet,

	EMenuMSKTest,
	EMenuNetTest,
	EMenuMnemoTest,

	EMenuMSKTest2,
	EMenuMTTest2,
	EMenuNetTest2,
	};

	#define KEY_1 ((KEY_wrk[0]&(1<<0)))
	#define KEY_2 ((KEY_wrk[0]&(1<<1)))
	#define KEY_3 ((KEY_wrk[0]&(1<<2)))
	#define KEY_OK ((KEY_wrk[0]&(1<<3)))
	#define KEY_4 ((KEY_wrk[0]&(1<<4)))
	#define KEY_5 ((KEY_wrk[0]&(1<<5)))
	#define KEY_6 ((KEY_wrk[0]&(1<<6)))
	#define KEY_0 ((KEY_wrk[0]&(1<<7)))
	#define KEY_7 ((KEY_wrk[1]&(1<<0)))
	#define KEY_8 ((KEY_wrk[1]&(1<<1)))
	#define KEY_9 ((KEY_wrk[1]&(1<<2)))
	#define KEY_NO ((KEY_wrk[1]&(1<<3)))
	#define KEY_F1 ((KEY_wrk[1]&(1<<4)))
	#define KEY_F2 ((KEY_wrk[1]&(1<<5)))
	#define KEY_F3 ((KEY_wrk[1]&(1<<6)))
	#define KEY_F4 ((KEY_wrk[1]&(1<<7)))


	extern byte GetTickCount();
    extern byte GetTick100ms();
    extern byte GetTick1s();
	extern void Menu_drv();
	extern void Menu_init();
	extern char LCD_str[];

	class Menu
	{
		public:
			uint8_t next_menu;
			uint8_t back_menu;
			uint8_t index_menu;
			void (*show_func)(void);
	};

	void LCD_uind(uint16_t _num, uint8_t _ind, uint8_t _cntr);
	void LCD_uind16(uint16_t _num, uint8_t _ind, uint8_t _cntr);
	void LCD_ind(int16_t _num, uint8_t _ind, uint8_t _cntr);
	void LCD_abc(char *_str, uint8_t _pos);
	void LCD_putc(uint8_t _sym, uint8_t _pos);
	void LCD_float(int16_t _num, uint8_t _base, uint8_t _pos);
	void show_dig(void);
	void getpm_dig(int16_t *val, uint8_t dot, int16_t min_val, int16_t max_val);
	uint8_t getpm(uint8_t val,uint8_t max);

	extern uint8_t KEY_cpy[2];
	extern uint8_t KEY_wrk[2];

	extern uint8_t Tr_iic_byte(uint8_t _byte);
	extern uint8_t Rd_iic_byte(uint8_t _mode);
	extern void Start_iic();
	extern void Stop_iic();


	extern const prog_char glob_menu_str[7][16] PROGMEM;
	extern const prog_char stop_pdz_str[] PROGMEM;
	extern const prog_char fire_str[] PROGMEM;
	extern const prog_char fire_str1[] PROGMEM;
	extern const prog_char fire_str2[] PROGMEM;
	extern const prog_char net_test_str[2][6] PROGMEM;
	extern const prog_char set_str[4][14] PROGMEM;
	extern const prog_char show_dig_str[2][5] PROGMEM;
#endif
