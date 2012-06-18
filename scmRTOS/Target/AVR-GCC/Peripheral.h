#ifndef __PERIPHERAL_H
	#define __PERIPHERAL_H
		#define MSK_FLT 3 //фильтр МСК
		//#include "Main.h" 
		extern void drv_Led();
		extern void LCD_init();
		extern void drv_LCD(char*);
		extern uint8_t LED_Out_Str[32];
		extern uint8_t KEY[2];// 1 - кнопка не нажата, 0 - кнопка нажата
		extern uint8_t MT[2];
		extern uint8_t MSK[8];
		extern uint8_t OS_MT[2];
		extern uint8_t TestMSK,TestMSKResult;
		extern uint8_t sec_tik;
		//extern uint8_t tech_fl;
#endif

