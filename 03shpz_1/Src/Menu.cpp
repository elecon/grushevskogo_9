#include "Menu.h"
#include "Sgwork.h"
//#include "version.h"
//#include "../version2.h"

#define SET_MENU(	_defmenu_name,\
					_defmenu_showfunc,\
					_defmenu_index,\
					_defmenu_back,\
					_defmenu_next) \
						{\
						_defmenu_name.show_func=_defmenu_showfunc;\
						_defmenu_name.index_menu=_defmenu_index;\
						_defmenu_name.back_menu=_defmenu_back;\
						_defmenu_name.next_menu=_defmenu_next;\
						}
uint8_t KEY_cpy[2];
uint8_t KEY_wrk[2];

Menu *menu;

Menu GLOB_MENU_screen,PDZ_MENU_screen,/*ETAZ_MENU_screen,*/DEV_MENU_screen;
Menu SET_MENU_screen,TEST_MENU_screen,MESS_MENU_screen,PDZ_SET_screen,DEV_SET_screen;
Menu SYS_SET_screen,RESTART_SET_screen,TIME_SET_screen;
Menu MSK_TEST_screen,/*BFPP_TEST_screen,*/MNEMO_TEST_screen,NET_TEST_MENU_screen;
Menu MSK_TEST2_screen;
Menu MT_TEST2_MENU_screen;
Menu TEST2_MENU_screen;
Menu INFO_MENU_screen;
Menu NET_TEST2_MENU_screen;

Menu* pMenu_arr[]=
{
	&GLOB_MENU_screen,

	&PDZ_MENU_screen,
	&DEV_MENU_screen,
	&SET_MENU_screen,
	&TEST_MENU_screen,
//	&TEST2_MENU_screen,
	&MESS_MENU_screen,
	&INFO_MENU_screen,

	&PDZ_SET_screen,
	&DEV_SET_screen,
	&SYS_SET_screen,

	&RESTART_SET_screen,

	&TIME_SET_screen,

	&MSK_TEST_screen,
	&NET_TEST_MENU_screen,
	&MNEMO_TEST_screen,

	&MSK_TEST2_screen,
	&MT_TEST2_MENU_screen,
	&NET_TEST2_MENU_screen,

};



uint8_t cur_menu;

extern uint16_t i;
//uint8_t i;

extern uint8_t OUT_FIELD[16];
extern uint8_t MT[2];
extern uint8_t OS_MT[2];

extern const prog_char glob_menu_str[7][16] PROGMEM;
const prog_char glob_menu_str[7][16]=
{
#if s03shpz_1
	"1.SHPZ-3",
#endif
#if SHPZ_6
	"1.SHPZ-6",
#endif
#if SHPZ_9
	"1.SHPZ-9",
#endif
#if SHPZ_14
	"1.SHPZ-14",
#endif
	"2.Устройства",
	"3.Уставки",
	"4.Тест",
	"5.Сообщения",
	"6.Info",
};

extern void pisk_drv();
extern void pause_pisk();

extern const prog_char stop_pdz_str[] PROGMEM;
const prog_char stop_pdz_str[]="Стоп ПДЗ";



extern uint8_t LCD_light;
uint8_t glob_counter;


//extern const prog_char fire_str[] PROGMEM;
const prog_char fire_str[]="ПОЖЕЖА";

//extern const prog_char fire_str1[] PROGMEM;
const prog_char fire_str1[]="ПОЖЕЖА СПС";

//extern const prog_char fire_str2[] PROGMEM;
const prog_char fire_str2[]="ПОЖЕЖА ПК";
extern uint8_t fire_floor;
extern uint8_t NetPackInfo2[3];
extern uint16_t fire_fl;
void show_glob()
{
	glob_counter=getpm(glob_counter,6);
	pMenu_arr[cur_menu]->next_menu = glob_counter+1;
	LCD_putc('>',0);
	LCD_abc((char*)glob_menu_str[glob_counter],1);
	//LCD_abc((char*)NetPackInfo2 [ 1 ] ,1);
	//LCD_uind16(fire_fl,11,4|LEAD_ZERO);
	//LCD_uind(TechFlag,14,2|LEAD_ZERO);

////////////////////////////////////////////////////////////////!!!доделать!!!///////////
	if (!(fire_fl&( FIRE_FL_PK_RAZR1|
                    FIRE_FL_PK_RAZR2|
                    FIRE_FL_PK_RAZR3|
                    FIRE_FL_SPS1|
                    FIRE_FL_SPS2|
                    FIRE_FL_SPS3|
                    FIRE_FL_ALL))){
		if (!(fire_fl&FIRE_FL_STOP_PDZ)) {
			if(glob_counter>=5) {
				LCD_abc((char*)glob_menu_str[0],21);
			}
			else {
				LCD_abc((char*)glob_menu_str[glob_counter+1],21);
			}
		}
		else {
			LCD_abc((char*)stop_pdz_str,20);
		}
	}
	else {
		if (fire_fl&(FIRE_FL_S_PK1_RAZ|FIRE_FL_S_PK2_RAZ|FIRE_FL_S_PK3_RAZ)) LCD_abc((char*)fire_str2,20);
		else
		if (fire_fl&(FIRE_FL_S_SPS2|FIRE_FL_S_SPS2|FIRE_FL_S_SPS3))        	 LCD_abc((char*)fire_str1,20);
		else LCD_abc((char*)fire_str,20);
//		LCD_abc((char*)fire_str,20); LCD_uind(fire_floor,28,2);
	}
////////////////////////////////////////////////////////////////

	pause_pisk();

//	LCD_uind(LCD_light,13,2|LEAD_ZERO);
//	pisk_drv();
}
//---------------------------------------------------------------------
uint8_t		net_counter;
extern uint8_t 		NetPackInfo[NUM_OF_SCAF];
extern uint8_t uiNetCounter;
extern const prog_char NET_TEST_CAP_str[] PROGMEM;
const prog_char NET_TEST_CAP_str[]="Мережа";
extern const prog_char net_test_str[2][6] PROGMEM;
const prog_char net_test_str[2][6]=
{
	"ЩМ-1",
	"ЩМ-2",
};

extern uint8_t i_mt;
void show_net_test()
{
        LCD_abc((char*)NET_TEST_CAP_str,1);
        LCD_uind(uiNetCounter,12,2|LEAD_ZERO);
//	for (i=0;i<8;i++) {
//		if (MT[0]		&(1<<i)) 	LCD_uind(1,i,1|LEAD_ZERO); 	    else LCD_uind(0,i,1|LEAD_ZERO);
//		if (MT[1]		&(1<<i)) 	LCD_uind(1,8+i,1|LEAD_ZERO); 	else LCD_uind(0,8+i,1|LEAD_ZERO);
//		if (OS_MT[0]	&(1<<i)) 	LCD_uind(1,20+i,1|LEAD_ZERO); 	else LCD_uind(0,20+i,1|LEAD_ZERO);
//		if (OS_MT[1]	&(1<<i)) 	LCD_uind(1,28+i,1|LEAD_ZERO); 	else LCD_uind(0,28+i,1|LEAD_ZERO);
//	}
//
//	if (scafe_fl&SCAFE_T_MT_OP) {
//		if (KEY_2)
//			if (i_mt>15) i_mt=0; else i_mt++;
//		if (KEY_5)
//			if (i_mt==0) i_mt=15; else i_mt--;
//	}
//
//
//	if (KEY_4) {
//		scafe_fl|=SCAFE_TEST_MT;
//		scafe_fl&=~SCAFE_T_MT_OP;
//	}
//	if (KEY_7) {
//		scafe_fl&=~SCAFE_TEST_MT;
//		scafe_fl|=SCAFE_T_MT_OP;
//	}
//
//	if (KEY_3) scafe_fl&=~(SCAFE_TEST_MT|SCAFE_T_MT_OP);
}

extern uint16_t OS_MT_TEST;
extern uint16_t MT_TEST;
extern uint16_t TestMTResult;
extern const prog_char MT_OK_str[] PROGMEM;
const prog_char MT_OK_str[]="MT ПЕРЕВIРЕНА";
extern const prog_char MT_ERR_str[] PROGMEM;
const prog_char MT_ERR_str[]="MT ERROR";
void show_mt_test2()
{
	TechFlag|=TEST_MT;

	if (TestMTResult==0xffff) LCD_abc((char*)MT_OK_str,0); else LCD_abc((char*)MT_ERR_str,0);
	for(i=0;i<16;i++) {

		if (TestMTResult&(1<<i)) 	LCD_uind(1,20+i,1|LEAD_ZERO); 	else LCD_uind(0,20+i,1|LEAD_ZERO);
	}
}

//----------------------------------------------------------------------
extern const prog_char set_str[4][14] PROGMEM;
const prog_char set_str[4][14]=
{
	"1.ПДЗ",
	"2.Устройств",
	"3.Система",
	"Уставки:"
};

uint8_t set_counter;
void show_set()
{
	set_counter=getpm(set_counter,3);
	pMenu_arr[cur_menu]->next_menu = set_counter+EMenuPdzSet;
	LCD_abc((char*)set_str[3],0);
	LCD_putc('>',20);//16
	LCD_abc((char*)set_str[set_counter],21);//17

}
//---------------------------------------------------	Як то кажуть версі програмного забезпечення
extern const prog_char strVersion[] PROGMEM;
const prog_char strVersion[]="v";

extern const prog_char szVersionIdentify[] PROGMEM;
const prog_char szVersionIdentify[]=IDENTIFY;

extern const prog_char szVersionTemplate[] PROGMEM;
const prog_char szVersionTemplate[]=TEMPLATE;
uint8_t szVersionIdentify_counter;
//char LCD_str_szVersionIdentify[16];
//char* ptszVersionIdentify;
#define TIME_WAIT_VERSION 2
void show_info()
{
        LCD_abc((char*)strVersion,0);
        LCD_abc((char*)szVersionTemplate,1);
        LCD_uind(szVersionIdentify_counter,14,2|LEAD_ZERO);

        if (!sec_tik) szVersionIdentify_counter++;
        //if (ProcesFlag&0x01) szVersionIdentify_counter++;

        if (szVersionIdentify_counter<((sizeof(szVersionIdentify))-16+TIME_WAIT_VERSION*2)) {
        if ((szVersionIdentify_counter)<TIME_WAIT_VERSION) {
            LCD_abc(((char*)(&szVersionIdentify[0])),20);
        }
        else {
            if ((szVersionIdentify_counter)<(sizeof(szVersionIdentify)-16)+TIME_WAIT_VERSION){
                LCD_abc(((char*)(&szVersionIdentify[szVersionIdentify_counter-TIME_WAIT_VERSION])),20);
            }
            else {
                LCD_abc(((char*)(&szVersionIdentify[(sizeof(szVersionIdentify))-16])),20);
            }
        }
        }
        else szVersionIdentify_counter=0;
}
//----------------------------------------------------
void show_pdz_set();
void show_pdz();
//void show_etaz();
void show_test();
void show_test2();
void show_devs();
void show_dev_set();
void show_sys_set();
void show_message();
void show_time_set();
void show_restart_set();
//void show_bfpp_test();
void show_msk_test();
void show_mnemo_test();
void show_msk_test2();
void show_mt_test2();
void show_info();
void show_net_test2();

void Menu_init()
{
//				NAME				SHOW_FUNC			INDEX		BACK		NEXT
	SET_MENU(GLOB_MENU_screen,		show_glob,			EMenuGlob, 		0,	EMenuGlob)		//0		0
	SET_MENU(PDZ_MENU_screen,		show_pdz,	    	EMenuPDZ,		0,	EMenuNetTest2)	//1		1

	SET_MENU(DEV_MENU_screen,		show_devs,			EMenuDevs, 		0,	EMenuDevSet)	//2		2
	SET_MENU(SET_MENU_screen,		show_set,			EMenuSet, 		0,	EMenuPdzSet)	//3		3

	SET_MENU(TEST_MENU_screen,		show_test,			EMenuTest, 		0,	EMenuMSKTest)	//4		4
//	SET_MENU(TEST2_MENU_screen,		show_test2,			EMenuTest2, 	0,	EMenuMSKTest2)	//		5

	SET_MENU(MESS_MENU_screen,		show_message,		EMenuMassage, 	0,	EMenuMassage)
	SET_MENU(INFO_MENU_screen,		show_info,			EMenuVersion, 	0,	EMenuVersion)	//5		6

	SET_MENU(PDZ_SET_screen,		show_pdz_set,		EMenuPdzSet, 	0,	EMenuPdzSet)	//6		7
	SET_MENU(DEV_SET_screen,		show_dev_set,		EMenuDevSet, 	0,	EMenuDevSet)	//7		8

	SET_MENU(SYS_SET_screen,		show_sys_set,		EMenuSysSet, 	0,	EMenuResSet)	//8		9
	SET_MENU(RESTART_SET_screen,	show_restart_set,	EMenuResSet, 	0,	EMenuTimeSet)	//9		10

	SET_MENU(TIME_SET_screen,		show_time_set,		EMenuTimeSet,	0,	EMenuTimeSet)	//10	11
	SET_MENU(MSK_TEST_screen,		show_msk_test,		EMenuMSKTest,	0,	EMenuMSKTest)	//11	12

	SET_MENU(NET_TEST_MENU_screen,	show_net_test,		EMenuNetTest,	0,	EMenuNetTest)	//13	13
	SET_MENU(MNEMO_TEST_screen,		show_mnemo_test,	EMenuMnemoTest,	0,	EMenuMnemoTest)	//12	14

	SET_MENU(MSK_TEST2_screen,		show_msk_test2,		EMenuMSKTest2,	0,	EMenuMSKTest2)	//		15
	SET_MENU(MT_TEST2_MENU_screen,	show_mt_test2,		EMenuMTTest2,	0,	EMenuMTTest2)	//		16
	SET_MENU(NET_TEST2_MENU_screen,	show_net_test2,		EMenuNetTest2,	0,	EMenuNetTest2)


	cur_menu=0;
	menu = pMenu_arr[cur_menu];
	KEY_cpy[0]=KEY[0];
	KEY_wrk[0]=KEY[0];
	KEY_cpy[1]=KEY[1];
	KEY_wrk[1]=KEY[1];

}

extern LCD_INPUT_STRUCT key_data;
uint8_t LCD_light;
void Menu_drv()
{
	//uint8_t i;

	KEY[0]=key_data.key[0];
	KEY[1]=key_data.key[1];

	if((KEY_cpy[0]!=KEY[0])||(KEY_cpy[1]!=KEY[1]))
	{
		KEY_cpy[0]=KEY[0];
		KEY_cpy[1]=KEY[1];
		KEY_wrk[0]=KEY_cpy[0];
		KEY_wrk[1]=KEY_cpy[1];
		pisk_drv();
		if((KEY_cpy[0]>0)||(KEY_cpy[1]>0))
			tech_fl|=SOUND_KEY;
		LCD_light=60;
	}

	if(!sec_tik) if(LCD_light) LCD_light--;

	for(i=0;i<40;i++) LCD_str[i]=' ';//очистка экрана 32

	if(!(tech_fl&DIG_INPUT))
	{
		if(KEY_OK)
		{
			if(pMenu_arr[cur_menu]->next_menu!=pMenu_arr[cur_menu]->index_menu)
			{
				i=pMenu_arr[cur_menu]->index_menu;
				cur_menu=pMenu_arr[cur_menu]->next_menu;
				pMenu_arr[cur_menu]->back_menu=i;
				menu=pMenu_arr[cur_menu];
			}
		}
		if(KEY_3)
		{
			cur_menu=pMenu_arr[cur_menu]->back_menu;
			menu=pMenu_arr[cur_menu];
		}
	}
	if(tech_fl&DIG_INPUT) show_dig();
	else (*menu).show_func();

	KEY_wrk[0]=0x00;
	KEY_wrk[1]=0x00;

}

//================== Функции отображения на ЖКИ ================
//extern const uint8_t LCD_digits[] PROGMEM;
const uint8_t LCD_digits[] =
{
	'0','1','2','3','4','5','6','7',
	'8','9','A','B','C','D','E','F',
};

#define MAX_WORD_DIGS 5
#if 0
uint8_t LCD_uind(uint16_t _num, uint8_t _base, uint8_t _ind, uint8_t _cntr)
{
	uint16_t pos = _ind, max;
	uint8_t num_dig=1, i, length;

	length = _cntr&0x3F;
//----------------------------------------------
//count number of digits in _num
	max = _base;
	while((_num>=max) && (num_dig<MAX_WORD_DIGS))
	{
		++num_dig;
		max*=_base;
	}

	if(!(_cntr&LEFT_ALIGN))
	{
		pos+=length-1;
		if(length<num_dig)
			length = num_dig;
	}
	else
	{
		max/=_base;
		if(length>num_dig)
			length = num_dig;
	}
//----------------------------------------------
//draw _num on screen

	for(i=0; i<length; ++i)
	{
		if(!(_cntr&LEFT_ALIGN))
		{
		//little pillow
			if(pos<40)//32
			{
				LCD_str[pos] = LCD_digits[_num%_base];
				_num/=_base;
				--pos;
			}
			else
			{
				return num_dig;
			}
			if((!_num) && (!(_cntr&LEAD_ZERO)))
			{
				return num_dig;
			}
		}
		else
		{
			if(pos<40)//32
			{
				if((max>0) && _num)
				{
					LCD_str[pos] = LCD_digits[_num/max];
					_num-=(_num/max)*max;
					max/=_base;
				}
				else
				{
					if(!(_cntr&LEAD_ZERO))
					{
						LCD_str[pos] = ' ';
					}
					else
					{
						LCD_str[pos] = LCD_digits[0];
					}
				}
				++pos;
			}
			else
			{
				return num_dig;
			}
		}
	}
	return num_dig;
}
#else
void LCD_uind(uint16_t _num, uint8_t _ind, uint8_t _cntr)
{
	uint16_t _pos = _ind, max,temp,num_temp;
	uint8_t num_dig=1, i, length;
	uint8_t uind_str[MAX_WORD_DIGS];

	length = _cntr&0x3F;
//----------------------------------------------
//count number of digits in _num
	num_temp=_num;
	for(i=1;i<6;i++)
	{
		uind_str[i-1]=LCD_digits[num_temp%10];
		if(num_temp<10) break;
		num_temp/=10;
		num_dig++;
	}

	if(length+_pos-1>39) return;//31
	if(num_dig>length) num_dig=length;

	for(i=0;i<num_dig;i++)
	{
		if(!(_cntr&LEFT_ALIGN))
		{
			LCD_str[_pos+length-i-1]=uind_str[i];
		}
		else
		{
			LCD_str[_pos+i]=uind_str[num_dig-i-1];
		}
	}
	if(_cntr&LEAD_ZERO)
	{
		if(!(_cntr&LEFT_ALIGN))
		{
			if(num_dig<length)
			{
				for(i=0;i<length-num_dig;i++)
				{
					LCD_str[_pos+i]='0';
				}
			}
		}
	}
	return;
}
#endif
void LCD_uind16(uint16_t _num, uint8_t _ind, uint8_t _cntr)
{
	uint16_t _pos = _ind, max,temp,num_temp;
	uint8_t num_dig=1, i, length;
	uint8_t uind_str[4];

	length = _cntr&0x3F;
//----------------------------------------------
//count number of digits in _num
	num_temp=_num;
	for(i=1;i<5;i++)
	{
		uind_str[i-1]=LCD_digits[num_temp%16];
		if(num_temp<16) break;
		num_temp/=16;
		num_dig++;
	}

	if(length+_pos-1>39) return;//31
	if(num_dig>length) num_dig=length;

	for(i=0;i<num_dig;i++)
	{
		if(!(_cntr&LEFT_ALIGN))
		{
			LCD_str[_pos+length-i-1]=uind_str[i];
		}
		else
		{
			LCD_str[_pos+i]=uind_str[num_dig-i-1];
		}
	}
	if(_cntr&LEAD_ZERO)
	{
		if(!(_cntr&LEFT_ALIGN))
		{
			if(num_dig<length)
			{
				for(i=0;i<length-num_dig;i++)
				{
					LCD_str[_pos+i]='0';
				}
			}
		}
	}
	return;
}

void LCD_ind(int16_t _num, uint8_t _ind, uint8_t _cntr)
{
	if(!(_ind<40)) return;//32
//-----------------------------------------------
//if negative, set leading MINUS
	if(_num<0)
	{
		LCD_str[_ind++] = '-';
		_num=-_num;
		_cntr = (_cntr&LEAD_ZERO)|((CLEAR_LENGTH(_cntr)-1));
	}
	LCD_uind(_num, _ind, _cntr);
}

// Courier -> LCD
extern const prog_char LCD_simb[256] PROGMEM;
const prog_char LCD_simb[256] =
 {//0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
//
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //0
//
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //1
//' '   '!'   '"'   '#'   '$'   '%'   '&'   '''   '('   ')'   '*'   '+'   ','   '-'   '.'	'/'
  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, //2
//'0'   '1'   '2'   '3'   '4'   '5'   '6'   '7'   '8'   '9'   ':'   ';'   '<'   '='   '>'   '?'
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, //3
//'@'   'A'   'B'   'C'   'D'   'E'   'F'   'G'   'H'   'I'   'J'   'K'   'L'   'M'   'N'   'O'
  0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, //4
//'P'   'Q'   'R'   'S'   'T'   'U'   'V'   'W'   'X'   'Y'   'Z'   '['   '\'   ']'   '^'   '_'
  0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x20, 0x5D, 0x5E, 0x5F, //5
//'`'   'a'   'b'   'c'   'd'   'e'   'f'   'g'   'h'   'i'   'j'   'k'   'l'   'm'   'n'   'o'
  0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, //6
//'p'   'q'   'r'   's'   't'   'u'   'v'   'w'   'x'   'y'   'z'   '{'   '|'   '}'   '~'
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x20, 0xD1, 0x20, 0xE9, 0x20, //7
//
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //B
//
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //C
//							o
  0x20, 0x20, 0x20, 0x20, 0xDF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //D
//'Ё'   'ё' 'укр.Е''укр.е''укр.I''ukr.і'
  0xF0, 0xF1, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, //E
// 'А'   'Б'   'В'    'Г'   'Д'   'Е'   'Ж'    'З'   'И'   'Й'   'К'   'Л'   'M'    'H'   'O'   'П'
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, //8
// 'Р'   'С'   'Т'    'У'   'Ф'   'Х'   'Ц'    'Ч'   'Ш'   'Щ'   'Ъ'    'Ы'   'Ь'   'Э'   'Ю'   'Я'
  0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, //9
// 'a'   'б'   'в'   'г'    'д'   'e'   'ж'    'з'   'и'   'й'   'к'    'л'   'м'   'н'   'о'   'п'
  0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, //A
// 'р'   'с'   'т'   'у'    'ф'   'х'   'ц'   'ч'    'ш'   'щ'   'ъ'    'ы'   'ь'   'э'   'ю'   'я'
  0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, //E
 };

void LCD_abc(prog_char *_str, uint8_t _pos)
{
	uint8_t i = _pos;
	size_t _strlen;
	uint8_t lcd_temp[40];//32
	_strlen=strlen_P(_str);

	if(_strlen>(40-_pos)) _strlen=40-_pos;//32 32

	strncpy_P((char*)(&lcd_temp),_str,_strlen+1);

	while(i<40)//32
	{
		if(lcd_temp[i-_pos]==0x00)
			break;
		LCD_str[i] = pgm_read_byte(&LCD_simb[lcd_temp[i-_pos]]);
		++i;
	}
}
void LCD_putc(uint8_t _sym, uint8_t _pos)
{
	if(_pos<40)	LCD_str[_pos] = _sym;//32
}

#if 0
void LCD_float(int16_t _num, uint16_t _base, uint8_t _pos, uint8_t _cntr)
{
	int16_t length=CLEAR_LENGTH(_cntr), tmp,tmp1;

	if(!length)
		return;

	if(_num<0)
	{
		LCD_str[_pos] = '-';
		_num=-_num;
		////-1 байт на знак
		_cntr = (_cntr&LEAD_ZERO)|(_cntr&LEFT_ALIGN)|(length);
		++_pos;
	}
	//-------------------------------------------------------------
	//целая часть
	//определение делителя _base
	tmp1=1;
	tmp=_base;
	while(tmp)
	{
		tmp1*=10;
		tmp--;
	}

	tmp = LCD_uind(_num/tmp1,10, _pos, length|LEFT_ALIGN|LEAD_ZERO);

	if(length<=tmp)
		return;
	length-=tmp;

	_pos+=tmp;

	if(_base)
	{
		//ставим '.'
		LCD_putc('.', _pos++);
		--length;
		if(!length)
			return;
		_num %= tmp1;
		LCD_uind(_num,10, _pos, _base|LEAD_ZERO);//|LEFT_ALIGN);
	}
  return;
}
#else
void LCD_float(int16_t _num, uint8_t _base, uint8_t _pos)
{
	uint16_t _pos1 = _pos, max,temp;
	int16_t num_temp;
	uint8_t num_dig=1, i;
	uint8_t uind_str[5];

//----------------------------------------------
//count number of digits in _num
	num_temp=_num;
	if(num_temp<0)
	{
		num_temp=-num_temp;
		num_dig++;
	}

	for(i=1;i<6;i++)
	{
		uind_str[i-1]=LCD_digits[num_temp%10];
		if(num_temp<10) break;
		num_temp/=10;
		num_dig++;
	}

	if(num_dig+_pos1-1>39) return;//31
	if(_num<0)
	{
		LCD_putc('-',_pos1);
		_pos1++;
		num_dig--;
	}
	//if(num_dig==1) LCD_str[_pos1++]='0';
	if(_base>=num_dig)
	{
		for(i=0;i<=_base-num_dig;i++)
		{
			LCD_str[_pos1++]='0';
		}
	}
	for(i=1;i<=num_dig;)
	{
		if(_base==num_dig-i+1) LCD_str[_pos1++]='.';
		LCD_str[_pos1++]=uind_str[num_dig-i];
		i++;
	}

}
#endif
uint8_t getpm(uint8_t val,uint8_t max)
{
	if(KEY_5)
	{
		val++;
		if(val>=max) val=0;
	}
	if(KEY_2)
	{
		if(!val) val=max-1;
		else val--;
	}
	return val;
}

int16_t *pm_val;
int16_t pm_minv,pm_maxv,pm2;
uint8_t pm_dot;
void getpm_dig(int16_t *val, uint8_t dot, int16_t min_val, int16_t max_val)
{
	if(KEY_0)//(KEY_2)
	{
		tech_fl|=DIG_INPUT;
		tech_fl&=~DIG_MINUS;
		pm_val=val;
		pm_minv=min_val;
		pm_maxv=max_val;
		pm_dot=dot;
		pm2=0;
	}
}

extern const prog_char show_dig_str[2][5] PROGMEM;
const prog_char show_dig_str[2][5]=
{
	"min:",
	"max:"
};

void show_dig(void)
{
	if(tech_fl&DIG_MINUS) LCD_putc('-',10);

	LCD_float(pm2, pm_dot, 0);
	LCD_abc((char*)show_dig_str[0],6);
	LCD_float(pm_minv, pm_dot, 10);

	LCD_float(*pm_val, pm_dot, 20);//16
	LCD_abc((char*)show_dig_str[1],26);//22
	LCD_float(pm_maxv, pm_dot, 30);//26

	if(KEY_OK)
	{
		if((pm2<=pm_maxv)&&(pm2>=pm_minv))
			*pm_val=pm2;
		tech_fl&=~DIG_INPUT;
	}
	if(KEY_NO)
	{
		if(pm2) {pm2=0;tech_fl&=~DIG_MINUS;}
		else tech_fl&=~DIG_INPUT;
	}
	if(!(tech_fl&DIG_MINUS))
	{
		if(KEY_1) {if(((pm2*10+1)<=pm_maxv)//&&((pm2*10+1)>=pm_minv)
				&&((pm2*10+1)>0)) pm2=(pm2*10+1);}
		if(KEY_2) {if(((pm2*10+2)<=pm_maxv)//&&((pm2*10+2)>=pm_minv)
				&&((pm2*10+2)>0)) pm2=(pm2*10+2);}
		if(KEY_3) {if(((pm2*10+3)<=pm_maxv)//&&((pm2*10+3)>=pm_minv)
				&&((pm2*10+3)>0)) pm2=(pm2*10+3);}
		if(KEY_4) {if(((pm2*10+4)<=pm_maxv)//&&((pm2*10+4)>=pm_minv)
				&&((pm2*10+4)>0)) pm2=(pm2*10+4);}
		if(KEY_5) {if(((pm2*10+5)<=pm_maxv)//&&((pm2*10+5)>=pm_minv)
				&&((pm2*10+5)>0)) pm2=(pm2*10+5);}
		if(KEY_6) {if(((pm2*10+6)<=pm_maxv)//&&((pm2*10+6)>=pm_minv)
				&&((pm2*10+6)>0)) pm2=(pm2*10+6);}
		if(KEY_7) {if(((pm2*10+7)<=pm_maxv)//&&((pm2*10+7)>=pm_minv)
				&&((pm2*10+7)>0)) pm2=(pm2*10+7);}
		if(KEY_8) {if(((pm2*10+8)<=pm_maxv)//&&((pm2*10+8)>=pm_minv)
				&&((pm2*10+8)>0)) pm2=(pm2*10+8);}
		if(KEY_9) {if(((pm2*10+9)<=pm_maxv)//&&((pm2*10+9)>=pm_minv)
				&&((pm2*10+9)>0)) pm2=(pm2*10+9);}
		if(KEY_0) { if(!pm2)
				{
					if(pm_minv<0)
						tech_fl|=DIG_MINUS;
				}
				if(((pm2*10+0)<=pm_maxv)//&&((pm2*10+0)>=pm_minv)
					&&((pm2*10+0)>0)) pm2=(pm2*10+0);}
	}
	else
	{
		if(KEY_1) {if(((pm2*10-1)>=pm_minv)//&&((pm2*10-1)<=pm_maxv)
				&&((pm2*10-1)<0)) pm2=(pm2*10-1);}
		if(KEY_2) {if(((pm2*10-2)>=pm_minv)//&&((pm2*10-2)<=pm_maxv)
				  &&((pm2*10-2)<0)) pm2=(pm2*10-2);}
		if(KEY_3) {if(((pm2*10-3)>=pm_minv)//&&((pm2*10-3)<=pm_maxv)
				  &&((pm2*10-3)<0)) pm2=(pm2*10-3);}
		if(KEY_4) {if(((pm2*10-4)>=pm_minv)//&&((pm2*10-4)<=pm_maxv)
				  &&((pm2*10-4)<0)) pm2=(pm2*10-4);}
		if(KEY_5) {if(((pm2*10-5)>=pm_minv)//&&((pm2*10-5)<=pm_maxv)
				  &&((pm2*10-5)<0)) pm2=(pm2*10-5);}
		if(KEY_6) {if(((pm2*10-6)>=pm_minv)//&&((pm2*10-6)<=pm_maxv)
				  &&((pm2*10-6)<0)) pm2=(pm2*10-6);}
		if(KEY_7) {if(((pm2*10-7)>=pm_minv)//&&((pm2*10-7)<=pm_maxv)
				  &&((pm2*10-7)<0)) pm2=(pm2*10-7);}
		if(KEY_8) {if(((pm2*10-8)>=pm_minv)//&&((pm2*10-8)<=pm_maxv)
				  &&((pm2*10-8)<0)) pm2=(pm2*10-8);}
		if(KEY_9) {if(((pm2*10-9)>=pm_minv)//&&((pm2*10-9)<=pm_maxv)
				  &&((pm2*10-9)<0)) pm2=(pm2*10-9);}
		if(KEY_0) {if(((pm2*10-0)>=pm_minv)//&&((pm2*10-0)<=pm_maxv)
				  &&((pm2*10-0)<0)) pm2=(pm2*10-0);}
	}
}
