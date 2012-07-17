#include "Dev_kog.h"
	void KogNum::auto_open()
	{
        stan |= KOG_OP;
        stan &=~ KOG_CLOSE;
	}
	void KogNum::auto_close()
	{
		stan &=~ KOG_OP;
        stan |= KOG_CLOSE;
	}
	void KogNum::check_press()
	{
		if (stan&KOG_OP) {
            if (MSK_FIELD[Dev_constr[num][3]]) t_kog_wait=T_WAIT_PRESS;
        }
        if (stan&KOG_CLOSE) {
            if (!(MSK_FIELD[Dev_constr[num][3]])) t_kog_wait=T_WAIT_PRESS;
        }
        if(!sec_tik) if(t_kog_wait) t_kog_wait--;
        if(!(t_kog_wait)) stan|=KOG_STAN;
	}

	void KogNum::check_mp()
	{
		if (stan&KOG_OP) {
            if (!(MSK_FIELD[Dev_constr[num][4]])) t_kog_wait=T_WAIT_PRESS;
        }
        if (stan&KOG_CLOSE) {
            if ((MSK_FIELD[Dev_constr[num][4]])) t_kog_wait=T_WAIT_PRESS;
        }
        if(!sec_tik) if(t_kog_wait) t_kog_wait--;
        if(!(t_kog_wait)) stan|=KOG_STAN;
	}

	void KogNum::check_os()
	{
		if(!(OS_FIELD[Dev_constr[num][1]])) stan|=KOG_OS_ERROR;
        else stan&=~KOG_OS_ERROR;
	}

	void KogNum::drv()
	{
		if (stan&(KOG_OPER|KOG_DIST)) {

            if (stad&(1<<KOG_ST_OPEN)) {
                stad&=~((1<<KOG_ST_OPEN));
                stan |= KOG_OP;
                stan &=~ KOG_CLOSE;
            }
            if (stad&(1<<KOG_ST_CLOSE)) {
                stad&=~(1<<KOG_ST_CLOSE);
                stan &=~ KOG_OP;
                stan |= KOG_CLOSE;
            }

            if (stad&(1<<KOG_ST_AVTO)) {
                stad&=~(1<<KOG_ST_AVTO);
                stan&=~(KOG_OPER|KOG_DIST);
            }

            if (stad&(1<<KOG_ST_ERR)) {
                stad&=~(1<<KOG_ST_ERR);
                stan&=~KOG_STAN;
                t_kog_wait=T_WAIT_PRESS;
            }
        }
        else {
            if (stad&(1<<KOG_ST_OPER)) {
                stad&=~(1<<KOG_ST_OPER);
                stan|=KOG_OPER;
            }
            else {
                if (stad&(1<<KOG_ST_DIST)) {
                    stad&=~(1<<KOG_ST_DIST);
                    stan|=KOG_DIST;
                }
            }
        }
    if (stan&KOG_CLOSE) OUT_FIELD[Dev_constr[num][1]]=0x00;
    else if (stan&KOG_OP) OUT_FIELD[Dev_constr[num][1]]=0xff;

    if(Dev_constr_info[num]&OPT_CHECK_PRESS) check_press();
    if(Dev_constr_info[num]&OPT_CHECK_MP) check_mp();
    if(Dev_constr_info[num]&OPT_CHECK_OS) check_os();
	}

	void KogNum::show_mnem()
	{
        if (stan&KOG_OP) LED_FIELD[Dev_constr[num][0]]=green_lamp;
        else LED_FIELD[Dev_constr[num][0]]=null_lamp;
        if (stan&KOG_STAN) LED_FIELD[Dev_constr[num][0]]&=~0x11;
        if (stan&KOG_OS_ERROR) LED_FIELD[Dev_constr[num][0]]&=~0x11;
        if (stan&(KOG_OPER|KOG_DIST)) LED_FIELD[Dev_constr[num][0]]&=~0x11;
	}

	void KogNum::show_lcd()
	{
        LCD_abc((char*)dev_name_str[num],0);

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
            if (stan&KOG_OS_ERROR)     LCD_abc((char*)os_err_str,      34);
            if (stan&KOG_STAN)   LCD_abc((char*)stan_err_str,   23);//19
        }
#ifdef ddebug
        LCD_uind(stad,28,2|LEAD_ZERO);
        LCD_uind(stan,31,2|LEAD_ZERO);
        if ((MSK_FIELD[Dev_constr[num][4]])) LCD_abc((char*)one_str,11);
        else LCD_abc((char*)noll_str,11);
#endif

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

	KogNum::KogNum(uint8_t _num)
	{
        num=_num;
        t_kog_wait=50;
        stan|= KOG_CLOSE;
	}
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
