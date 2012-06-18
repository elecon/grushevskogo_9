#include "Dev_KD.h"
	void KD::auto_open()
	{
//		if(!(enh_info&(KOG_OPER|KOG_DIST)))
//			if(!(enh_info&(KOG_PRESS_ERROR|KOG_MP_ERROR|KOG_KTR_ERROR|KOG_OS_ERROR)))
				if(stad!=KD_ST_OPEN) cmd = KD_C_OPEN;
		
	}
	void KD::auto_close()
	{
		if(!(enh_info&(KD_OPER|KD_DIST)))
			if(stad!=KD_ST_CLOSE) cmd = KD_C_CLOSE;
		
	}
	void KD::check_press()
	{
		switch(stad)
		{
			case KD_ST_OPEN:
				if(*k_press) t_wait_press_counter=t_wait_press;
			break;
			case KD_ST_CLOSE:
				if(!*k_press) t_wait_press_counter=t_wait_press;
			break;
		}
		if(!sec_tik) if(t_wait_press_counter) t_wait_press_counter--;
		if(!t_wait_press_counter) enh_info|=KD_PRESS_ERROR;
	}
	
	void KD::check_mp()
	{
		switch(stad)
		{
			case KD_ST_OPEN:
				if(*k_mp) t_wait_mp_counter=t_wait_mp;
			break;
			case KD_ST_CLOSE://включен- авария
//				if(*k_mp)
				t_wait_mp_counter=t_wait_mp;
			break;
		}
		if(!sec_tik) if(t_wait_mp_counter) t_wait_mp_counter--;
		if(!t_wait_mp_counter) enh_info|=KD_MP_ERROR;
	}
	void KD::check_ktr()
	{
		if(*k_ktr) enh_info|=KD_KTR_ERROR;
//		else enh_info&=~KOG_KTR_ERROR;
	}
	void KD::check_os()
	{
		if(*os) enh_info|=KD_OS_ERROR;
//		else enh_info&=~KOG_OS_ERROR;
	}

	void KD::drv()
	{
		if(!sec_tik) inc_t_stad();
		if(enh_info&(KD_PRESS_ERROR|KD_MP_ERROR|KD_KTR_ERROR|KD_OS_ERROR))
			cmd=KD_C_CLOSE;
		switch(cmd)
		{
			case KD_C_OPEN:
				if(stad!=KD_ST_OPEN)
				{
					stad=KD_ST_OPEN;
					clear_t_stad();
				}
			break;
			case KD_C_CLOSE:
				if(stad!=KD_ST_CLOSE)
				{
					stad=KD_ST_CLOSE;
					clear_t_stad();
				}
			break;
		}

		switch(stad)
		{
			case KD_ST_OPEN:
				*out=0xff;
			break;
			case KD_ST_CLOSE:
				*out=0x00;
			break;
		}
		
		if(enh_info&KD_CHECK_PRESS) check_press();
		if(enh_info&KD_CHECK_MP) check_mp();
		if(enh_info&KD_CHECK_KTR) check_ktr();
		if(enh_info&KD_CHECK_OS) check_os();
	}
	
	KD::KD()
	{
		clear_t_stad();
		clear_t_sub_st();
		cmd = KD_C_CLOSE;
		t_wait_press=10;
		t_wait_mp=5;
		t_wait_press_counter=t_wait_press;
		t_wait_mp_counter=t_wait_mp;
	}
	
	void KD::show_mnem()
	{
		uint8_t lamp = 0xff;
		if(stad==KD_ST_OPEN)
		{
			lamp = 0xf0;
		}
		if(stad==KD_ST_CLOSE)
		{
			lamp = 0x0f;
		}
		
		if(enh_info&(KD_DIST|KD_OPER)) lamp&=~0x11;
		if(enh_info&(KD_PRESS_ERROR|KD_MP_ERROR|KD_KTR_ERROR|KD_OS_ERROR)) lamp= 0xf5;

		*mn_os = lamp;
	}

	const prog_char kog_error_str[5][5]=
	{
		"Ош:",
		"давл",
		"МП",
		"КТР",
		"ОС"
	};
	
	void KD::show_lcd()
	{
		if(!(enh_info&KD_DIST))
		{
			//if(KEY_4) enh_info&=~KOG_OPER;
			//if(KEY_7) enh_info|=KOG_OPER;
			//if(enh_info&KOG_OPER)
			//{
				if(KEY_8) {cmd=KD_C_OPEN; enh_info|=KD_OPER;}
				if(KEY_NO) {cmd=KD_C_CLOSE; enh_info&=~KD_OPER;}
			//}
		}
		LCD_abc((char*)name,0);
	
		if(stad==KD_ST_OPEN) LCD_abc((char*)stad_str[0],6);
		if(stad==KD_ST_CLOSE) LCD_abc((char*)stad_str[1],6);
		LCD_uind(read_t_stad(),7,5);

		if(enh_info&KD_DIST) LCD_abc((char*)mode_str[2],12);
		else if(enh_info&KD_OPER) LCD_abc((char*)mode_str[1],12);
		else LCD_abc((char*)mode_str[0],12);

		if(enh_info&(KD_PRESS_ERROR|KD_MP_ERROR|KD_KTR_ERROR|KD_OS_ERROR))
			LCD_abc((char*)kog_error_str[0],20);//16
		if(enh_info&KD_PRESS_ERROR) LCD_abc((char*)kog_error_str[1],23);//19
		if(enh_info&KD_MP_ERROR) LCD_abc((char*)kog_error_str[2],27);//23
		if(enh_info&KD_KTR_ERROR) LCD_abc((char*)kog_error_str[3],30);//26
		if(enh_info&KD_OS_ERROR) LCD_abc((char*)kog_error_str[4],34);//30

		if(KEY_1) enh_info&=~(KD_PRESS_ERROR|KD_MP_ERROR|KD_KTR_ERROR|KD_OS_ERROR);
	}

	KD::KD(	const prog_char* _name,
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
		cmd = KD_C_CLOSE;
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