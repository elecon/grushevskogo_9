#include "Dev_kog_net.h"

//______________________________________________________________________________
	void KOG_NET::drv()
	{
        stan = *net_stan;
        if (stan&KOG_OP) stad&=~(1<<KOG_ST_OPEN);
        if (stan&KOG_CLOSE) stad&=~(1<<KOG_ST_CLOSE);
        if (!(stan&(KOG_OPER|KOG_DIST))) stad&=~(1<<KOG_ST_AVTO);
        if (stan&KOG_OPER) stad&=~(1<<KOG_ST_OPER);
        *net_stad = stad;
	}

	void KOG_NET::show_mnem()
	{
		if (stan&KOG_OP) *mn_os =green_lamp;
        else *mn_os =null_lamp;

        if (stan&KOG_STAN) *mn_os&=~0x11;
        if (stan&KOG_OS_ERROR) *mn_os&=~0x11;
        if (stan&(KOG_OPER|KOG_DIST)) *mn_os&=~0x11;


	}

	void KOG_NET::show_lcd()
	{
        LCD_abc((char*)name,0);
        if (net_fl&(1<<num)) {
            LCD_abc((char*)error_str,6);
        }
        else {
            if  (stan&KOG_OP) LCD_abc((char*)stad_str[0],6);
            else LCD_abc((char*)stad_str[1],6);
            if (stad&(1<<KOG_C_OPEN)) LCD_abc((char*)stad_str[0],4);
            if (stad&(1<<KOG_C_CLOSE)) LCD_abc((char*)stad_str[1],4);

            if (stan&(KOG_OPER|KOG_DIST)) {
                if (stan&KOG_DIST) LCD_abc((char*)dist_str,   12);//19
                if (stan&KOG_OPER) LCD_abc((char*)oper_str,   12);//19
            }
            else {
                LCD_abc((char*)auto_str,   12);//19
            }

            if (stan&(KOG_OS_ERROR|KOG_STAN)) {
                LCD_abc((char*)error_str,20);
                if (stan&KOG_OS_ERROR) LCD_abc((char*)os_err_str,      34);
                if (stan&KOG_STAN)   LCD_abc((char*)press_err_str,   23);//19
            }

            //LCD_uind(stad,28,2|LEAD_ZERO);
            //LCD_uind(stan,31,2|LEAD_ZERO);

            if (stan&KOG_OPER) {
                if(KEY_8) {
                    if(!(stad&(1<<KOG_ST_OPEN)))
                    {
                        stad|=(1<<KOG_ST_OPEN);
                    }
                }
                if(KEY_NO) {
                    if(!(stad&(1<<KOG_ST_CLOSE)))
                    {
                        stad|=(1<<KOG_ST_CLOSE);
                    }
                }
                if (KEY_1) stad|=(1<<KOG_ST_ERR);
                if (KEY_4) {
                    stad|=(1<<KOG_ST_AVTO);
                }
            }
            else {
                if (!(stan&(KOG_OPER|KOG_DIST))) if (KEY_7) stad|=(1<<KOG_ST_OPER);
                if (stan&(KOG_DIST|KOG_OPER)) if (KEY_4) stad|=(1<<KOG_ST_AVTO);
            }
        }
    }
    KOG_NET::KOG_NET()
    {

    }

	KOG_NET::KOG_NET
	(const prog_char* _name,
        uint8_t* _net_stan,
        uint8_t* _net_stad,
        uint8_t* _mn_os,
        uint8_t _num)
        {
            name=_name;
            net_stad=_net_stad;
            net_stan=_net_stan;
            mn_os=_mn_os;
            num=_num;
        }
