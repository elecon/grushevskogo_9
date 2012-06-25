#include "Dev_kog.h"
	void KOG::auto_open()
	{
//		if(!(enh_info&(KOG_OPER|KOG_DIST)))
//			if(!(enh_info&(KOG_PRESS_ERROR|KOG_MP_ERROR|KOG_KTR_ERROR|KOG_OS_ERROR)))
				if(stad!=KOG_ST_OPEN) cmd = KOG_C_OPEN;

	}
	void KOG::auto_close()
	{
		if(!(enh_info&(KOG_OPER|KOG_DIST)))
			if(stad!=KOG_ST_CLOSE) cmd = KOG_C_CLOSE;

	}
	void KOG::check_press()
	{
		switch(stad)
		{
			case KOG_ST_OPEN:
				if(*k_press) t_wait_press_counter=t_wait_press;
			break;
			case KOG_ST_CLOSE:
				if(!*k_press) t_wait_press_counter=t_wait_press;
			break;
		}
		if(!sec_tik) if(t_wait_press_counter) t_wait_press_counter--;
		if(!t_wait_press_counter) enh_info|=KOG_PRESS_ERROR;
	}

	void KOG::check_mp()
	{
		switch(stad)
		{
			case KOG_ST_OPEN:
				if(*k_mp) t_wait_mp_counter=t_wait_mp;
			break;
			case KOG_ST_CLOSE://включен- авария
//				if(*k_mp)
				t_wait_mp_counter=t_wait_mp;
			break;
		}
		if(!sec_tik) if(t_wait_mp_counter) t_wait_mp_counter--;
		if(!t_wait_mp_counter) enh_info|=KOG_MP_ERROR;
	}
	void KOG::check_ktr()
	{
		if(*k_ktr) enh_info|=KOG_KTR_ERROR;
//		else enh_info&=~KOG_KTR_ERROR;
	}
	void KOG::check_os()
	{
		if(*os) enh_info|=KOG_OS_ERROR;
		else enh_info&=~KOG_OS_ERROR;
	}

	void KOG::drv()
	{
		if(!sec_tik) inc_t_stad();
//		if(enh_info&(KOG_PRESS_ERROR|KOG_MP_ERROR|KOG_KTR_ERROR|KOG_OS_ERROR))
//			cmd=KOG_C_CLOSE;
		switch(cmd)
		{
			case KOG_C_OPEN:
				if(stad!=KOG_ST_OPEN)
				{
					stad=KOG_ST_OPEN;
					clear_t_stad();
				}
			break;
			case KOG_C_CLOSE:
				if(stad!=KOG_ST_CLOSE)
				{
					stad=KOG_ST_CLOSE;
					clear_t_stad();
				}
			break;
		}

		switch(stad)
		{
			case KOG_ST_OPEN:
				*out=0xff;
			break;
			case KOG_ST_CLOSE:
				*out=0x00;
			break;
		}

		if(enh_info&KOG_CHECK_PRESS) check_press();
		if(enh_info&KOG_CHECK_MP) check_mp();
		if(enh_info&KOG_CHECK_KTR) check_ktr();
		if(enh_info&KOG_CHECK_OS) check_os();
	}

	KOG::KOG()
	{
		clear_t_stad();
		clear_t_sub_st();
		cmd = KOG_C_CLOSE;
		t_wait_press=10;
		t_wait_mp=5;
		t_wait_press_counter=t_wait_press;
		t_wait_mp_counter=t_wait_mp;
	}

	void KOG::show_mnem()
	{
		uint8_t lamp = 0xff;
		if(stad==KOG_ST_OPEN)
		{
			lamp = 0x0f;
		}
		if(stad==KOG_ST_CLOSE)
		{
			lamp = 0xff;
		}

		if(enh_info&(KOG_DIST|KOG_OPER)) lamp&=~0x11;
		if(enh_info&(KOG_PRESS_ERROR|KOG_MP_ERROR|KOG_KTR_ERROR|KOG_OS_ERROR)) lamp= 0xf5;

		*mn_os = lamp;
	}

    extern const prog_char kog_error_str[5][5] PROGMEM;
	const prog_char kog_error_str[5][5]=
	{
		"Ош:",
		"давл",
		"МП",
		"КТР",
		"ОС"
	};

	void KOG::show_lcd()
	{
		if(!(enh_info&KOG_DIST))
		{
            if(KEY_8) {cmd=KOG_C_OPEN; enh_info|=KOG_OPER;}
            if(KEY_NO) {cmd=KOG_C_CLOSE; enh_info&=~KOG_OPER;}
		}
		LCD_abc((char*)name,0);

		if(stad==KOG_ST_OPEN) LCD_abc((char*)stad_str[0],6);
		if(stad==KOG_ST_CLOSE) LCD_abc((char*)stad_str[1],6);
		//LCD_uind(read_t_stad(),7,5);

//		if(enh_info&KOG_DIST) LCD_abc((char*)dist_str,12);
//		else if(enh_info&KOG_OPER) LCD_abc((char*)oper_str,12);
//		else LCD_abc((char*)auto_str,12);
//
//		if(enh_info&(KOG_PRESS_ERROR|KOG_MP_ERROR|KOG_KTR_ERROR|KOG_OS_ERROR))
//			LCD_abc((char*)error_str,20);//16
//		if(enh_info&KOG_PRESS_ERROR) LCD_abc((char*)press_err_str,23);//19
//		if(enh_info&KOG_MP_ERROR) LCD_abc((char*)mp_err_str,27);//23
//		if(enh_info&KOG_KTR_ERROR) LCD_abc((char*)ktr_err_str,30);//26
//		if(enh_info&KOG_OS_ERROR) LCD_abc((char*)os_err_str,34);//30
//
//		if(KEY_1) enh_info&=~(KOG_PRESS_ERROR|KOG_MP_ERROR|KOG_KTR_ERROR|KOG_OS_ERROR);
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
		clear_t_stad();
		clear_t_sub_st();
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
