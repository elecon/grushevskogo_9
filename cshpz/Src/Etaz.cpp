#include "Etaz.h"
#include "Menu.h"
#include "Sgwork.h"
#include "Pdz.h"


extern NET_OUTPUT_STRUCT1 data_for_slave1;
extern NET_OUTPUT_STRUCT2 data_for_slave2;

extern uint16_t net_fl;
extern uint16_t fire_sps;
extern uint16_t fire_sb;
extern uint16_t fire_net;
extern uint16_t fire_vzk;
extern uint16_t stop_fl;
extern uint16_t fire_zone;


//const prog_char link_str[] = "в сети";
//const prog_char nolink_str[] = "ош сети";
//const prog_char norma_str[] = "норма";
//const prog_char fire_str[] = "ПОЖАР";
//const prog_char fsps_str[] = "СПС";
//const prog_char fsb_str[] = "ПК";
//const prog_char fnet_str[] = "сеть";
//const prog_char fvzk_str[] = "ОЗК";
//const prog_char stop_str[] = "СТОП ПДЗ";
////const prog_char err_str[] = "авария";
//
////uint8_t cur_etaz_lcd;
//const prog_char etaz_str[]="ЩПЗ 2П";
//void show_etaz()
//{
//	cur_etaz_lcd=getpm(cur_etaz_lcd,NUM_OF_SCAF);//
//	LCD_abc((char*)etaz_str,0);
////	LCD_uind(cur_etaz_lcd+1,6,2);
//	if (cur_etaz_lcd<NUM_OF_SCAF)
//	{
//		if(KEY_F1&&KEY_8)//пожар с клавы при нажатии двух кнопок одновременно
//		{
///*
//		if (cur_etaz_lcd==0) data_for_slave1.cmd|=FIRE_ZONE;//пожар от центра на слейв1
//		if (cur_etaz_lcd==1) data_for_slave2.cmd|=FIRE_ZONE;//пожар от центра на слейв2
//
//*/
//
//
//		}
//
//	if(net_fl&(1<<cur_etaz_lcd))	LCD_abc((char*)nolink_str,9);
//	else{ LCD_abc((char*)link_str,9);
//		if(stop_fl&(1<<cur_etaz_lcd))	LCD_abc((char*)stop_str,20);//16
//		else {
//			LCD_abc((char*)norma_str,20);
//			if(fire_zone&(1<<cur_etaz_lcd)) LCD_abc((char*)fire_str,20);//16
//			if(fire_sps&(1<<cur_etaz_lcd)) LCD_abc((char*)fsps_str,26);//22
//			if(fire_sb&(1<<cur_etaz_lcd)) LCD_abc((char*)fsb_str,30);//26
//			if(fire_net&(1<<cur_etaz_lcd)) LCD_abc((char*)fnet_str,32);//28
//			if(fire_vzk&(1<<cur_etaz_lcd)) LCD_abc((char*)fvzk_str,36);//16
//			}
//		}
//	}
//
//}
//
//
//const prog_char test_str[]="zero";
//void show_bfpp_test()
//{
//	LCD_abc((char*)test_str,0);
//}


