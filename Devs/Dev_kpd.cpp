#include "Dev_kpd.h"

//______________________________________________________________________________
	void KogKpd::auto_open()
	{
        stan |= KPD_OP;
        stan &=~ KPD_CLOSE;
	}
	void KogKpd::auto_close()
	{
		stan &=~ KPD_OP;
        stan |= KPD_CLOSE;
	}
	void KogKpd::check_press()
	{
		if (stan&KPD_OP) {
            if (MSK_FIELD[Dev_constr[num][3]]) t_kog_wait=T_WAIT_PRESS;
        }
        if (stan&KPD_CLOSE) {
            if (!(MSK_FIELD[Dev_constr[num][3]])) t_kog_wait=T_WAIT_PRESS;
        }
        if(!sec_tik) if(t_kog_wait) t_kog_wait--;
        if(!(t_kog_wait)) stan|=KPD_STAN;
	}

	void KogKpd::check_mp()
	{
		if (stan&KPD_OP) {
            if (!(MSK_FIELD[Dev_constr[num][4]])) t_kog_wait=T_WAIT_PRESS;
        }
        if (stan&KPD_CLOSE) {
            if ((MSK_FIELD[Dev_constr[num][4]])) t_kog_wait=T_WAIT_PRESS;
        }
        if(!sec_tik) if(t_kog_wait) t_kog_wait--;
        if(!(t_kog_wait)) stan|=KPD_STAN;
	}

	void KogKpd::check_os()
	{
		if(!(OS_FIELD[Dev_constr[num][1]])) stan|=KPD_OS_ERROR;
        else stan&=~KPD_OS_ERROR;
	}

	void KogKpd::drv()
	{
		if (stan&(KPD_OPER|KPD_DIST)) {
        if (stad&(1<<KPD_ST_OPEN)) {
            stad&=~((1<<KPD_ST_OPEN));
            stan |= KPD_OP;
            stan &=~ KPD_CLOSE;
            //OUT_FIELD[OUT_BIT]=0xff;
        }
        if (stad&(1<<KPD_ST_CLOSE)) {
            stad&=~(1<<KPD_ST_CLOSE);
            stan &=~ KPD_OP;
            stan |= KPD_CLOSE;
            //OUT_FIELD[OUT_BIT]=0x00;
        }

        if (stad&(1<<KPD_ST_AVTO)) {
            stad&=~(1<<KPD_ST_AVTO);
            stan&=~(KPD_OPER|KPD_DIST);
        }

        if (stad&(1<<KPD_ST_ERR)) {
            stad&=~(1<<KPD_ST_ERR);
            stan&=~KPD_STAN;
        }
    }
    else {
        if (stad&(1<<KPD_ST_OPER)) {
            stad&=~(1<<KPD_ST_OPER);
            stan|=KPD_OPER;
        }
        else {
            if (stad&(1<<KPD_ST_DIST)) {
                stad&=~(1<<KPD_ST_DIST);
                stan|=KPD_DIST;
            }
        }
    }
    if (stan&KPD_CLOSE) OUT_FIELD[Dev_constr[num][1]]=0x00;
    else if (stan&KPD_OP) OUT_FIELD[Dev_constr[num][1]]=0xff;

    if(Dev_constr_info[num]&OPT_CHECK_PRESS) check_press();
    if(Dev_constr_info[num]&OPT_CHECK_MP) check_mp();
    if(Dev_constr_info[num]&OPT_CHECK_OS) check_os();
	}

	KogKpd::KogKpd()
	{

		t_wait_press=10;
		t_wait_mp=5;
		t_wait_press_counter=t_wait_press;
		t_wait_mp_counter=t_wait_mp;

		t_kog_wait=50;
        stan |= KPD_CLOSE;
	}

	void KogKpd::show_mnem()
	{
        if (stan&KPD_OP) LED_FIELD[Dev_constr[num][0]]=green_lamp;
        else LED_FIELD[Dev_constr[num][0]]=null_lamp;

        if (stan&KPD_STAN) LED_FIELD[Dev_constr[num][0]]&=~0x11;
        if (stan&KPD_OS_ERROR) LED_FIELD[Dev_constr[num][0]]&=~0x11;
        if (stan&(KPD_OPER|KPD_DIST)) LED_FIELD[Dev_constr[num][0]]&=~0x11;

		//*mn_os = lamp;
	}

	void KogKpd::show_lcd()
	{
        LCD_abc((char*)dev_name_str[num],0);

        if  (stan&KPD_OP) LCD_abc((char*)stad_str[0],6);
        else LCD_abc((char*)stad_str[1],6);
        if (stad&(1<<KPD_C_OPEN)) LCD_abc((char*)stad_str[0],4);
        if (stad&(1<<KPD_C_CLOSE)) LCD_abc((char*)stad_str[1],4);

        if (stan&(KPD_OPER|KPD_DIST)) {
            if (stan&KPD_DIST) LCD_abc((char*)dist_str,   12);//19
            if (stan&KPD_OPER) LCD_abc((char*)oper_str,   12);//19
        }
        else {
            LCD_abc((char*)auto_str,   12);//19
        }

        if (stan&(KPD_OS_ERROR|KPD_STAN)) {
            LCD_abc((char*)error_str,20);
            if (stan&KPD_OS_ERROR)     LCD_abc((char*)os_err_str,      34);
            if (stan&KPD_STAN)   LCD_abc((char*)press_err_str,   23);//19
        }
        LCD_uind(stad,28,2|LEAD_ZERO);
        LCD_uind(stan,31,2|LEAD_ZERO);
//        LCD_uind(t_kog_wait,33,2|LEAD_ZERO);

        if (stan&KPD_OPER) {
            if(KEY_8) {
                if(!(stad&(1<<KPD_ST_OPEN)))
                {
                    stad|=(1<<KPD_ST_OPEN);
                }
            }
            if(KEY_NO) {
                if(!(stad&(1<<KPD_ST_CLOSE)))
                {
                    stad|=(1<<KPD_ST_CLOSE);
                }
            }
            if (KEY_1) stad|=(1<<(KPD_ST_ERR));
            if (KEY_4) {
                stad|=(1<<KPD_ST_AVTO);
            }
        }
        else {
            if (!(stan&(KPD_OPER|KPD_DIST))) if (KEY_7) stad|=(1<<KPD_ST_OPER);
            if (stan&(KPD_DIST|KPD_OPER)) if (KEY_4) stad|=(1<<KPD_ST_AVTO);
        }
	}

	KogKpd::KogKpd(uint8_t _num)
	{
        num=_num;
	}
//______________________________________________________________________________
	void KpdNet::drv()
	{
        stan = *net_stan;
        if (stan&KPD_OP) stad&=~(1<<KPD_ST_OPEN);
        if (stan&KPD_CLOSE) stad&=~(1<<KPD_ST_CLOSE);
        if (!(stan&(KPD_OPER|KPD_DIST))) stad&=~(1<<KPD_ST_AVTO);
        if (stan&KPD_OPER) stad&=~(1<<KPD_ST_OPER);
        *net_stad = stad;
	}

	void KpdNet::show_mnem()
	{
		if (stan&KPD_OP) *mn_os =green_lamp;
        else *mn_os =null_lamp;

        if (stan&KPD_STAN) *mn_os&=~0x11;
        if (stan&KPD_OS_ERROR) *mn_os&=~0x11;
        if (stan&(KPD_OPER|KPD_DIST)) *mn_os&=~0x11;


	}

	void KpdNet::show_lcd()
	{
        LCD_abc((char*)name,0);
        if (net_fl&(1<<num)) {
            LCD_abc((char*)error_str,6);
        }
        else {
            if  (stan&KPD_OP) LCD_abc((char*)stad_str[0],6);
            else LCD_abc((char*)stad_str[1],6);
            if (stad&(1<<KPD_C_OPEN)) LCD_abc((char*)stad_str[0],4);
            if (stad&(1<<KPD_C_CLOSE)) LCD_abc((char*)stad_str[1],4);

            if (stan&(KPD_OPER|KPD_DIST)) {
                if (stan&KPD_DIST) LCD_abc((char*)dist_str,   12);//19
                if (stan&KPD_OPER) LCD_abc((char*)oper_str,   12);//19
            }
            else {
                LCD_abc((char*)auto_str,   12);//19
            }

            if (stan&(KPD_OS_ERROR|KPD_STAN)) {
                LCD_abc((char*)error_str,20);
                if (stan&KPD_OS_ERROR) LCD_abc((char*)os_err_str,      34);
                if (stan&KPD_STAN)   LCD_abc((char*)stan_err_str,   23);//19
            }

            //LCD_uind(stad,28,2|LEAD_ZERO);
            //LCD_uind(stan,31,2|LEAD_ZERO);

            if (stan&KPD_OPER) {
                if(KEY_8) {
                    if(!(stad&(1<<KPD_ST_OPEN)))
                    {
                        stad|=(1<<KPD_ST_OPEN);
                    }
                }
                if(KEY_NO) {
                    if(!(stad&(1<<KPD_ST_CLOSE)))
                    {
                        stad|=(1<<KPD_ST_CLOSE);
                    }
                }
                if (KEY_1) stad|=(1<<KPD_ST_ERR);
                if (KEY_4) {
                    stad|=(1<<KPD_ST_AVTO);
                }
            }
            else {
                if (!(stan&(KPD_OPER|KPD_DIST))) if (KEY_7) stad|=(1<<KPD_ST_OPER);
                if (stan&(KPD_DIST|KPD_OPER)) if (KEY_4) stad|=(1<<KPD_ST_AVTO);
            }
        }
    }
    KpdNet::KpdNet()
    {

    }

	KpdNet::KpdNet
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
