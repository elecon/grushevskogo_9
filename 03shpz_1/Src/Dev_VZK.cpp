#include "Dev_VZK.h"


#ifdef TAMPLE
    template <uint8_t LED_NOMER>
	void VZK<LED_NOMER>::auto_open()
	//void VZK::auto_open()
#else
    void VZK::auto_open()
#endif
	{
//		if(!(enh_info&(KOG_OPER|KOG_DIST)))
//			if(!(enh_info&(KOG_PRESS_ERROR|KOG_MP_ERROR|KOG_KTR_ERROR|KOG_OS_ERROR)))
				if(stad!=VZK_ST_OPEN) cmd = VZK_C_OPEN;

	}

#ifdef TAMPLE
	template <uint8_t LED_NOMER>
	void VZK<LED_NOMER>::auto_close()
#else
    void VZK::auto_close()
#endif
	{
		if(!(enh_info&(VZK_OPER|VZK_DIST)))
			if(stad!=VZK_ST_CLOSE) cmd = VZK_C_CLOSE;

	}

#ifdef TAMPLE
	template <uint8_t LED_NOMER>
	void VZK<LED_NOMER>::check_press()
#else
    void VZK::check_press()
#endif
	{
		switch(stad)
		{
			case VZK_ST_OPEN:
				if(*k_press) t_wait_press_counter=t_wait_press;
			break;
			case VZK_ST_CLOSE:
				if(!*k_press) t_wait_press_counter=t_wait_press;
			break;
		}
		if(!sec_tik) if(t_wait_press_counter) t_wait_press_counter--;
		if(!t_wait_press_counter) enh_info|=VZK_PRESS_ERROR;
	}

#ifdef TAMPLE
    template <uint8_t LED_NOMER>
	void VZK<LED_NOMER>::check_mp()
#else
    void VZK::check_mp()
#endif
	{
		switch(stad)
		{
			case VZK_ST_OPEN:
				if(*k_mp) t_wait_mp_counter=t_wait_mp;
			break;
			case VZK_ST_CLOSE://включен- авария
//				if(*k_mp)
				t_wait_mp_counter=t_wait_mp;
			break;
		}
		if(!sec_tik) if(t_wait_mp_counter) t_wait_mp_counter--;
		if(!t_wait_mp_counter) enh_info|=VZK_MP_ERROR;
	}

#ifdef TAMPLE
	template <uint8_t LED_NOMER>
	void VZK<LED_NOMER>::check_ktr()
#else
    void VZK::check_ktr()
#endif
	{
		if(*k_ktr) enh_info|=VZK_KTR_ERROR;
//		else enh_info&=~KOG_KTR_ERROR;
	}

#ifdef TAMPLE
	template <uint8_t LED_NOMER>
	void VZK<LED_NOMER>::check_os()
#else
    void VZK::check_os()
#endif
	{
		if(!(*os)) enh_info|=VZK_OS_ERROR;
		else enh_info&=~VZK_OS_ERROR;
	}

    extern uint8_t OUT_FIELD[16];
    extern uint8_t LED_FIELD[NUM_OF_MNEMO*80];

//#ifdef TAMPLE
//    template <uint8_t LED_NOMER>
//	void VZK<LED_NOMER>::drv()
//#else
//    void VZK::drv()
//#endif
//	{
//		if(!sec_tik) inc_t_stad();
//		//if(enh_info&(VZK_PRESS_ERROR|VZK_MP_ERROR|VZK_KTR_ERROR|VZK_OS_ERROR))
//		//	cmd=VZK_C_CLOSE;
//		switch(cmd)
//		{
//			case VZK_C_OPEN:
//				if(stad!=VZK_ST_OPEN)
//				{
//					stad=VZK_ST_OPEN;
//					clear_t_stad();
//				}
//			break;
//			case VZK_C_CLOSE:
//				if(stad!=VZK_ST_CLOSE)
//				{
//					stad=VZK_ST_CLOSE;
//					clear_t_stad();
//				}
//			break;
//		}
//
//		switch(stad)
//		{
//			case VZK_ST_OPEN:
//				*out=0xff;
//				//OUT_FIELD[LED_FIELD]=0xff;
//			break;
//			case VZK_ST_CLOSE:
//				*out=0x00;
//				//OUT_FIELD[LED_FIELD]=0x00;
//			break;
//		}
//
//		if(enh_info&VZK_CHECK_PRESS) check_press();
//		if(enh_info&VZK_CHECK_MP) check_mp();
//		if(enh_info&VZK_CHECK_KTR) check_ktr();
//		if(enh_info&VZK_CHECK_OS) check_os();
//	}
#ifdef TAMPLE
//    template <uint8_t LED_NOMER>
//	VZK<LED_NOMER>::VZK()
//	{
//		clear_t_stad();
//		clear_t_sub_st();
//		cmd = VZK_C_CLOSE;
//		//enh_info|=VZK_CHECK_OS;
//		t_wait_press=10;
//		t_wait_mp=5;
//		t_wait_press_counter=t_wait_press;
//		t_wait_mp_counter=t_wait_mp;
//	}
#else
    VZK::VZK()
	{
		clear_t_stad();
		clear_t_sub_st();
		cmd = VZK_C_CLOSE;
		//enh_info|=VZK_CHECK_OS;
		t_wait_press=10;
		t_wait_mp=5;
		t_wait_press_counter=t_wait_press;
		t_wait_mp_counter=t_wait_mp;
	}
#endif

#ifdef TAMPLE
    template <uint8_t LED_NOMER>
	void VZK<LED_NOMER>::show_mnem()
#else
    void VZK::show_mnem()
#endif
	{
		uint8_t lamp = 0xff;
		if(stad==VZK_ST_OPEN)
		{
			lamp = 0xf0;
		}
		if(stad==VZK_ST_CLOSE)
		{
			lamp = 0xff;
		}

		if(enh_info&(VZK_DIST|VZK_OPER)) lamp&=~0x11;
		if(enh_info&(VZK_PRESS_ERROR|VZK_MP_ERROR|VZK_KTR_ERROR|VZK_OS_ERROR)) lamp&=~0xf5;

		//LED_FIELD[mn_os]=lamp;
		//mn_os = lamp;
		//LED_FIELD[LED_NOMER]=0xff;
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

#ifdef TAMPLE
    template <uint8_t LED_NOMER>
	void VZK<LED_NOMER>::show_lcd()
#else
    void VZK::show_lcd()
#endif
	{
		if(!(enh_info&VZK_DIST))
		{
			//if(KEY_4) enh_info&=~KOG_OPER;
			//if(KEY_7) enh_info|=KOG_OPER;
			//if(enh_info&KOG_OPER)
			//{
				if(KEY_8) {cmd=VZK_C_OPEN; enh_info|=VZK_OPER;}
				if(KEY_NO) {cmd=VZK_C_CLOSE; enh_info&=~VZK_OPER;}
			//}
		}
		LCD_abc((char*)name,0);

		if(stad==VZK_ST_OPEN) LCD_abc((char*)stad_str[0],6);
		if(stad==VZK_ST_CLOSE) LCD_abc((char*)stad_str[1],6);
		LCD_uind(read_t_stad(),7,5);

		if(enh_info&VZK_DIST) LCD_abc((char*)mode_str[2],12);
		else if(enh_info&VZK_OPER) LCD_abc((char*)mode_str[1],12);
		else LCD_abc((char*)mode_str[0],12);

		if(enh_info&(VZK_PRESS_ERROR|VZK_MP_ERROR|VZK_KTR_ERROR|VZK_OS_ERROR))
			LCD_abc((char*)kog_error_str[0],20);//16
		if(enh_info&VZK_PRESS_ERROR) LCD_abc((char*)kog_error_str[1],23);//19
		if(enh_info&VZK_MP_ERROR) LCD_abc((char*)kog_error_str[2],27);//23
		if(enh_info&VZK_KTR_ERROR) LCD_abc((char*)kog_error_str[3],30);//26
		if(enh_info&VZK_OS_ERROR) LCD_abc((char*)kog_error_str[4],34);//30

		if(KEY_1) enh_info&=~(VZK_PRESS_ERROR|VZK_MP_ERROR|VZK_KTR_ERROR|VZK_OS_ERROR);
	}

//    template <uint8_t LED_NOMER>
//	VZK<LED_NOMER>::VZK(	const prog_char* _name,
//				uint8_t* _mn_os,
//				uint16_t _enh_info,
//                prog_uint8_t _out,
//				uint8_t* _press,
//				uint8_t* _os,
//				uint8_t* _mp,
//				uint8_t* _ktr)
//	{
//		clear_t_stad();
//		clear_t_sub_st();
//		cmd = VZK_C_CLOSE;
//		t_wait_press=10;
//		t_wait_mp=5;
//		t_wait_press_counter=t_wait_press;
//		t_wait_mp_counter=t_wait_mp;
//		name=_name;
//		mn_os=_mn_os;
//		enh_info=_enh_info;
//		out=_out;
//		k_press=_press;
//		os=_os;
//		k_mp=_mp;
//		k_ktr=_ktr;
//	}
