#include "Dev_kog.h"
	void KOG::auto_open()
	{
        stan |= KOG_OP;
        stan &=~ KOG_CLOSE;
	}
	void KOG::auto_close()
	{
		stan &=~ KOG_OP;
        stan |= KOG_CLOSE;
	}
	void KOG::check_press()
	{
		if (stan&KOG_OP) {
            if (*k_press) t_kog_wait=T_WAIT_PRESS;
        }
        if (stan&KOG_CLOSE) {
            if (!(*k_press)) t_kog_wait=T_WAIT_PRESS;
        }
        if(!sec_tik) if(t_kog_wait) t_kog_wait--;
        if(!(t_kog_wait)) stan|=KOG_STAN;
	}

	void KOG::check_mp()
	{
		if (stan&KOG_OP) {
            if (!(*k_mp)) t_kog_wait=T_WAIT_PRESS;
        }
        if (stan&KOG_CLOSE) {
            if ((*k_mp)) t_kog_wait=T_WAIT_PRESS;
        }
        if(!sec_tik) if(t_kog_wait) t_kog_wait--;
        if(!(t_kog_wait)) stan|=KOG_STAN;
	}

	void KOG::check_os()
	{
		if(!(*os)) stan|=KOG_OS_ERROR;
        else stan&=~KOG_OS_ERROR;
	}

	void KOG::drv()
	{
		if (stan&(KOG_OPER|KOG_DIST)) {
        if (stad&(1<<KOG_ST_OPEN)) {
            stad&=~((1<<KOG_ST_OPEN));
            stan |= KOG_OP;
            stan &=~ KOG_CLOSE;
            //OUT_FIELD[OUT_BIT]=0xff;
        }
        if (stad&(1<<KOG_ST_CLOSE)) {
            stad&=~(1<<KOG_ST_CLOSE);
            stan &=~ KOG_OP;
            stan |= KOG_CLOSE;
            //OUT_FIELD[OUT_BIT]=0x00;
        }

        if (stad&(1<<KOG_ST_AVTO)) {
            stad&=~(1<<KOG_ST_AVTO);
            stan&=~(KOG_OPER|KOG_DIST);
        }

        if (stad&(1<<KOG_ST_ERR)) {
            stad&=~(1<<KOG_ST_ERR);
            stan&=~KOG_STAN;
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
    if (stan&KOG_CLOSE) *out=0x00;
    else if (stan&KOG_OP) *out=0xff;

    if(enh_info&OPT_CHECK_PRESS) check_press();
    if(enh_info&OPT_CHECK_MP) check_mp();
    if(enh_info&OPT_CHECK_OS) check_os();
	}

	KOG::KOG()
	{
		cmd = KOG_C_CLOSE;
		t_wait_press=10;
		t_wait_mp=5;
		t_wait_press_counter=t_wait_press;
		t_wait_mp_counter=t_wait_mp;

		t_kog_wait=50;
        stan |= KOG_CLOSE;
	}

	void KOG::show_mnem()
	{
        if (stan&KOG_OP) *mn_os=green_lamp;
        else *mn_os=null_lamp;

        if (stan&KOG_STAN) *mn_os&=~0x11;
        if (stan&KOG_OS_ERROR) *mn_os&=~0x11;
        if (stan&(KOG_OPER|KOG_DIST)) *mn_os&=~0x11;

		//*mn_os = lamp;
	}

	void KOG::show_lcd()
	{
        LCD_abc((char*)name,0);

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
            if (stan&KOG_STAN)   LCD_abc((char*)press_err_str,   23);//19
        }
//        LCD_uind(stad,28,2|LEAD_ZERO);
//        LCD_uind(stan,31,2|LEAD_ZERO);
//        LCD_uind(t_kog_wait,33,2|LEAD_ZERO);

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

	KOG::KOG(	const prog_char* _name,
				uint8_t* _mn_os,
				uint16_t _enh_info,
				uint8_t* _out,
				uint8_t* _press,
				uint8_t* _os,
				uint8_t* _mp,
				uint8_t* _ktr)
	{
//		clear_t_stad();
//		clear_t_sub_st();
		cmd = KOG_C_CLOSE;
		t_wait_press=10;
		t_wait_mp=5;
		t_wait_press_counter=t_wait_press;
		t_wait_mp_counter=t_wait_mp;
		name=_name;
		mn_os=_mn_os;
		enh_info=_enh_info;
		out=_out;
		k_press=_press;
		os=_os;
		k_mp=_mp;
		k_ktr=_ktr;
	}
//______________________________________________________________________________
	void KOG_NET::drv()
	{
//        stan = *net_stan;
//        if (stan&KOG_OP) stad&=~(1<<KOG_ST_OPEN);
//        if (stan&KOG_CLOSE) stad&=~(1<<KOG_ST_CLOSE);
//        if (!(stan&(KOG_OPER|KOG_DIST))) stad&=~(1<<KOG_ST_AVTO);
//        if (stan&KOG_OPER) stad&=~(1<<KOG_ST_OPER);
//        *net_stad = stad;
	}

	void KOG_NET::show_mnem()
	{
//		if (stan&KOG_OP) *mn_os =green_lamp;
//        else *mn_os =null_lamp;
//
//        if (stan&KOG_STAN) *mn_os&=~0x11;
//        if (stan&KOG_OS_ERROR) *mn_os&=~0x11;
//        if (stan&(KOG_OPER|KOG_DIST)) *mn_os&=~0x11;


	}

	void KOG_NET::show_lcd()
	{
//        LCD_abc((char*)name,0);
//        if (net_fl&(1<<num)) {
//            LCD_abc((char*)error_str,6);
//        }
//        else {
//            if  (stan&KOG_OP) LCD_abc((char*)stad_str[0],6);
//            else LCD_abc((char*)stad_str[1],6);
//            if (stad&(1<<KOG_C_OPEN)) LCD_abc((char*)stad_str[0],4);
//            if (stad&(1<<KOG_C_CLOSE)) LCD_abc((char*)stad_str[1],4);
//
//            if (stan&(KOG_OPER|KOG_DIST)) {
//                if (stan&KOG_DIST) LCD_abc((char*)dist_str,   12);//19
//                if (stan&KOG_OPER) LCD_abc((char*)oper_str,   12);//19
//            }
//            else {
//                LCD_abc((char*)auto_str,   12);//19
//            }
//
//            if (stan&(KOG_OS_ERROR|KOG_STAN)) {
//                LCD_abc((char*)error_str,20);
//                if (stan&KOG_OS_ERROR) LCD_abc((char*)os_err_str,      34);
//                if (stan&KOG_STAN)   LCD_abc((char*)press_err_str,   23);//19
//            }
//
//            //LCD_uind(stad,28,2|LEAD_ZERO);
//            //LCD_uind(stan,31,2|LEAD_ZERO);
//
//            if (stan&KOG_OPER) {
//                if(KEY_8) {
//                    if(!(stad&(1<<KOG_ST_OPEN)))
//                    {
//                        stad|=(1<<KOG_ST_OPEN);
//                    }
//                }
//                if(KEY_NO) {
//                    if(!(stad&(1<<KOG_ST_CLOSE)))
//                    {
//                        stad|=(1<<KOG_ST_CLOSE);
//                    }
//                }
//                if (KEY_1) stad|=(1<<KOG_ST_ERR);
//                if (KEY_4) {
//                    stad|=(1<<KOG_ST_AVTO);
//                }
//            }
//            else {
//                if (!(stan&(KOG_OPER|KOG_DIST))) if (KEY_7) stad|=(1<<KOG_ST_OPER);
//                if (stan&(KOG_DIST|KOG_OPER)) if (KEY_4) stad|=(1<<KOG_ST_AVTO);
//            }
//        }
    }

	KOG_NET::KOG_NET(
        const prog_char* _name,
        uint8_t* _net_stan,
        uint8_t* _net_stad,
        uint8_t* _mn_os//,
        //uint8_t _num
        )
        {
            name=_name;
            net_stad=_net_stad;
            net_stan=_net_stan;
            mn_os=_mn_os;
            //num=_num;
        }
