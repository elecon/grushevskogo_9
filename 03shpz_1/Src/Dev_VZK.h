#ifndef __DEVVZK_H
	#define __DEVVZK_H

//    #define TAMPLE

	#include "DEVS.H"
    #include "Nls.h"

	enum {VZK_C_CLOSE,VZK_C_OPEN};
	enum {VZK_ST_CLOSE,VZK_ST_OPEN};

    extern uint8_t LED_FIELD[NUM_OF_MNEMO*80];


	//флаги enh_info
	#define VZK_CHECK_PRESS	0x8000 //проверка перепада давления
	#define VZK_CHECK_MP	0x4000 //проверка состояния магнитного пускателя
	#define VZK_CHECK_KTR	0x2000 //проверка состояния теплового реле
	#define VZK_CHECK_OS	0x1000 //проверка обратной связи
	#define VZK_OPER		0x0200 //устройство управляется оператором
	#define VZK_DIST		0x0100 //устройство управляется дистанционно
	#define VZK_PRESS_ERROR	0x0080 //ошибка перепада давления
	#define VZK_MP_ERROR	0x0040 //ошибка магнитного пускателя
	#define VZK_KTR_ERROR	0x0020 //ошибка теплового реле
	#define VZK_OS_ERROR	0x0010 //ошибка обратной связи

#ifdef TAMPLE
	template <uint8_t LED_NOMER>
	class VZK: public TechObj
#else
//    template <uint8_t LED_NOMER>
	class VZK: public TechObj
#endif
	{
		public:
			uint8_t* k_press;
			uint8_t *out;
			//const uint8_t mn_oss;
			uint8_t *os;//указатель на байт обратной связи
			uint8_t *k_mp;
			uint8_t *k_ktr;
			uint16_t t_wait_press;
			uint16_t t_wait_press_counter;
			uint16_t t_wait_mp;
			uint16_t t_wait_mp_counter;
			//static const uint8_t LED_NOMER2=LED_NOMER;

			//void drv();
//-----------------------------------------------------------------------------------------------
            void drv()
            {
                if(!sec_tik) inc_t_stad();
                //if(enh_info&(VZK_PRESS_ERROR|VZK_MP_ERROR|VZK_KTR_ERROR|VZK_OS_ERROR))
                //	cmd=VZK_C_CLOSE;
                switch(cmd)
                {
                    case VZK_C_OPEN:
                        if(stad!=VZK_ST_OPEN)
                        {
                            stad=VZK_ST_OPEN;
                            clear_t_stad();
                        }
                    break;
                    case VZK_C_CLOSE:
                        if(stad!=VZK_ST_CLOSE)
                        {
                            stad=VZK_ST_CLOSE;
                            clear_t_stad();
                        }
                    break;
                }

                switch(stad)
                {
                    case VZK_ST_OPEN:
                        *out=0xff;
                        //OUT_FIELD[LED_NOMER]=0xff;
                    break;
                    case VZK_ST_CLOSE:
                        *out=0x00;
                        //OUT_FIELD[LED_NOMER]=0x00;
                    break;
                }

                if(enh_info&VZK_CHECK_PRESS) check_press();
                if(enh_info&VZK_CHECK_MP) check_mp();
                if(enh_info&VZK_CHECK_KTR) check_ktr();
                if(enh_info&VZK_CHECK_OS) check_os();
            }

            //void ()
//-----------------------------------------------------------------------------------------------
			void show_mnem();
			void show_lcd();
			void check_press();
			void check_mp();
			void check_ktr();
			void check_os();
			void auto_open();
			void auto_close();
			//void drv();
			//void show_mnem();
			//void show_lcd();

        private:
			uint16_t t_stad;
			uint16_t t_sub_st;
		public:
			uint8_t stad;
			uint8_t sub_st;

#ifdef TAMPLE
			//template <uint8_t LED_NOMER>
			VZK();

			//template <uint8_t LED_NOMER>
			VZK(	const prog_char* _name,
					uint8_t* _mn_os,
					uint16_t _enh_info,
					const prog_uint8_t _out,
					uint8_t* _press,
					uint8_t* _os,
					uint8_t* _mp,
					uint8_t* _ktr);
#else
			//template <uint8_t LED_NOMER>
			VZK();
//
			//template <uint8_t LED_NOMER>
			VZK(	const prog_char* _name,
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
                        cmd = VZK_C_CLOSE;
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
                    ;
#endif
	};

#endif
