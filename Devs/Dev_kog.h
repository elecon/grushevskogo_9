#ifndef __DEVKOG_H
	#define __DEVKOG_H

	#include "DEVS.H"
    #include "Nls.h"

	enum {KOG_C_CLOSE,KOG_C_OPEN};
	enum {  KOG_ST_CLOSE,   //0x01
            KOG_ST_OPEN,    //0x02
            KOG_ST_OPER,    //0x04
            KOG_ST_DIST,    //0x08

            KOG_ST_AVTO,    //0x10
            KOG_ST_ERR      //0x20
    };

    extern uint8_t LED_FIELD[NUM_OF_MNEMO*80];

    #define T_WAIT_PRESS 5
    #define T_WAIT_MP 2

    #define PAUSE 5
    #define WORK 2
	//флаги enh_info
	//Стан пристрою
	#define KOGT_AUTO    	0x01 //
	#define KOGT_OPER    	0x02 //
	#define KOGT_DIST    	0x04 //
	#define KOGT_OP      	0x08 //
	#define KOGT_SUXAR   	0x80 //ошибка перепада давления
	#define KOGT_CLOSE   	0x40 //ошибка магнитного пускателя
	#define KOGT_STAN    	0x20 //ошибка теплового реле
	#define KOGT_OS_ERROR	0x10 //ошибка обратной связи

	template <uint16_t LED_NOMER, uint8_t MSK_BIT,uint8_t OUT_BIT,uint16_t OPTIONS,const char *STRING>
	class KOGT: public TDevObject
	{
        public:
            uint8_t t_repit_counter;
            uint8_t t_kog_wait;

//-----------------------------------------------------------------------------------------------
            void auto_open()
            {
                stan |= KOGT_OP;
                stan &=~ KOGT_CLOSE;
            }

            void auto_close()
            {
                stan &=~ KOGT_OP;
                stan |= KOGT_CLOSE;
            }

            void check_press()
            {
                if (stan&KOGT_OP) {
                    if (MSK_FIELD[MSK_BIT]) t_kog_wait=T_WAIT_PRESS;
                }
                if (stan&KOGT_CLOSE) {
                    if (!(MSK_FIELD[MSK_BIT])) t_kog_wait=T_WAIT_PRESS;
                }
                if(!sec_tik) if(t_kog_wait) t_kog_wait--;
                if(!(t_kog_wait)) stan|=KOGT_STAN;

            }

            void check_mp()
            {
                if (stan&KOGT_OP) {
                    if (!(MSK_FIELD[MSK_BIT])) t_kog_wait=T_WAIT_PRESS;
                }
                if (stan&KOGT_CLOSE) {
                    if ((MSK_FIELD[MSK_BIT])) t_kog_wait=T_WAIT_PRESS;
                }
                if(!sec_tik) if(t_kog_wait) t_kog_wait--;
                if(!(t_kog_wait)) stan|=KOGT_STAN;
            }

            void check_os()
            {
                if(!(OS_FIELD[OUT_BIT])) stan|=KOGT_OS_ERROR;
                else stan&=~KOGT_OS_ERROR;
            }

            void drv()
            {

                if (stan&(KOGT_OPER|KOGT_DIST)) {
                    if (stad&(1<<KOGT_ST_OPEN)) {
                        stad&=~((1<<KOGT_ST_OPEN));
                        stan |= KOGT_OP;
                        stan &=~ KOGT_CLOSE;
                        //OUT_FIELD[OUT_BIT]=0xff;
                    }
                    if (stad&(1<<KOGT_ST_CLOSE)) {
                        stad&=~(1<<KOGT_ST_CLOSE);
                        stan &=~ KOGT_OP;
                        stan |= KOGT_CLOSE;
                        //OUT_FIELD[OUT_BIT]=0x00;
                    }

                    if (stad&(1<<KOGT_ST_AVTO)) {
                        stad&=~(1<<KOGT_ST_AVTO);
                        stan&=~(KOGT_OPER|KOGT_DIST);
                    }

                    if (stad&(1<<KOGT_ST_ERR)) {
                        stad&=~(1<<KOGT_ST_ERR);
                        stan&=~KOGT_STAN;
                    }
                }
                else {
                    if (stad&(1<<KOGT_ST_OPER)) {
                        stad&=~(1<<KOGT_ST_OPER);
                        stan|=KOGT_OPER;
                    }
                    else {
                        if (stad&(1<<KOGT_ST_DIST)) {
                            stad&=~(1<<KOGT_ST_DIST);
                            stan|=KOGT_DIST;
                        }
                    }
                }
                if (stan&KOGT_CLOSE) OUT_FIELD[OUT_BIT]=0x00;
                else if (stan&KOGT_OP) OUT_FIELD[OUT_BIT]=0xff;

                if(OPTIONS&OPT_CHECK_PRESS) check_press();
                if(OPTIONS&OPT_CHECK_MP) check_mp();
//                if(OPTIONS&VZK_CHECK_KTR) check_ktr();
                if(OPTIONS&OPT_CHECK_OS) check_os();
            }

            void show_mnem()
            {
//                if (stan&KOGT_CLOSE)
//                    LED_FIELD[LED_NOMER]=red_b_lamp;
//                else {

                //}

                if (stan&KOGT_OP) LED_FIELD[LED_NOMER]=green_lamp;
                else LED_FIELD[LED_NOMER]=null_lamp;

                if (stan&KOGT_STAN) LED_FIELD[LED_NOMER]&=~0x11;
                if (stan&KOGT_OS_ERROR) LED_FIELD[LED_NOMER]&=~0x11;
                if (stan&(KOGT_OPER|KOGT_DIST)) LED_FIELD[LED_NOMER]&=~0x11;

            }

            void show_lcd()
            {
                LCD_abc((char*)STRING,0);

                //LCD_uind(t_klap_counter,9,2|LEAD_ZERO);

                if  (stan&KOGT_OP) LCD_abc((char*)stad_str[0],6);
                else LCD_abc((char*)stad_str[1],6);
                if (stad&(1<<KOGT_C_OPEN)) LCD_abc((char*)stad_str[0],4);
                if (stad&(1<<KOGT_C_CLOSE)) LCD_abc((char*)stad_str[1],4);

                if (stan&(KOGT_OPER|KOGT_DIST)) {
                    if (stan&KOGT_DIST) LCD_abc((char*)dist_str,   12);//19
                    if (stan&KOGT_OPER) LCD_abc((char*)oper_str,   12);//19
                }
                else {
                    LCD_abc((char*)auto_str,   12);//19
                }

                if (stan&(KOGT_OS_ERROR|KOGT_STAN)) {
                    LCD_abc((char*)error_str,20);
                    if (stan&KOGT_OS_ERROR)     LCD_abc((char*)os_err_str,      34);
                    if (stan&KOGT_STAN)   LCD_abc((char*)press_err_str,   23);//19
                }
//                if (stan&(MOE_OS_ERROR|MOE_STAN)) {
//                    LCD_abc((char*)error_str,20);
////                    if(stan&MOE_PRESS_ERROR)    LCD_abc((char*)press_err_str,   23);//19
////                    if(stan&MOE_MP_ERROR)       LCD_abc((char*)mp_err_str,      27);//23
////                    if(stan&MOE_KTR_ERROR)      LCD_abc((char*)ktr_err_str,     30);//26
//                    if(stan&MOE_OS_ERROR)       LCD_abc((char*)os_err_str,      34);
//                    if(stan&MOE_STAN)           LCD_abc((char*)stan_err_str,    28);
//                }

                LCD_uind(stad,28,2|LEAD_ZERO);
                LCD_uind(stan,31,2|LEAD_ZERO);
                LCD_uind(t_kog_wait,33,2|LEAD_ZERO);

//                if(stan&KOGT_SUXAR) LCD_abc((char*)vidk_str,    23);
//                else LCD_abc((char*)zakr_str,    23);

                //if (stan&MOE_SUXAR)

                if (stan&KOGT_OPER) {
                    if(KEY_8) {
                        if(!(stad&(1<<KOGT_ST_OPEN)))
                        {
                            stad|=(1<<KOGT_ST_OPEN);
                            //t_klap_counter=WORK+PAUSE+2;

                        }
                    }
                    if(KEY_NO) {
                        if(!(stad&(1<<KOGT_ST_CLOSE)))
                        {
                            stad|=(1<<KOGT_ST_CLOSE);
                            //t_klap_counter=0;
                        }
                    }
                    if (KEY_1) stad|=(1<<KOGT_ST_ERR);
                    if (KEY_4) {
                        stad|=(1<<KOGT_ST_AVTO);
                    }
                }
                else {
                    if (!(stan&(KOGT_OPER|KOGT_DIST))) if (KEY_7) stad|=(1<<KOGT_ST_OPER);
                    if (stan&(KOGT_DIST|KOGT_OPER)) if (KEY_4) stad|=(1<<KOGT_ST_AVTO);
                }
            }

            KOGT() {
                t_kog_wait=50;
                stan |= KOGT_CLOSE;
            }

//-----------------------------------------------------------------------------------------------
	};
    template <  uint16_t LED_NOMER,
                const char *STRING,
                NET_OUTPUT_STRUCT1 *D_IN,
                NET_INPUT_STRUCT1 *D_OUT,
                uint8_t NET_BITE,
                uint8_t NET_FLAG>
	class KOGT_NET : public TDevObject
	{
	  public:
            //uint8_t mmmm;

            void drv ()
            {
                stan = D_IN->devs_net_stat[NET_BITE];

                if (stan&KOGT_OP) stad&=~(1<<KOGT_ST_OPEN);
                if (stan&KOGT_CLOSE) stad&=~(1<<KOGT_ST_CLOSE);
//                if (stan&KOGT_COUNTER) {
//                    stad&=~(1<<KOGT_ST_OPEN);
//                }
//                else {
//                    if ((D_OUT->devs_net_cmd[0])&(1<<KOGT_ST_OPEN)) stad|=(1<<KOGT_ST_OPEN);
//                }
                if (!(stan&(KOGT_OPER|KOGT_DIST))) stad&=~(1<<KOGT_ST_AVTO);
                if (stan&KOGT_OPER) stad&=~(1<<KOGT_ST_OPER);
//                if (!(stan&KOGT_COUNTER)) stad&=~(1<<KOGT_ST_CLOSE);


                D_OUT->devs_net_cmd[NET_BITE] = stad;
            }


            void show_mnem()
            {
                 if (net_fl&(1<<NET_FLAG)) {
                    LED_FIELD[LED_NOMER]=null_lamp;
                }
                else {
                    if (stan&KOGT_OP) LED_FIELD[LED_NOMER]=green_lamp;
                    else LED_FIELD[LED_NOMER]=null_lamp;

                    if (stan&KOGT_STAN) LED_FIELD[LED_NOMER]&=~0x11;
                    if (stan&KOGT_OS_ERROR) LED_FIELD[LED_NOMER]&=~0x11;
                    if (stan&(KOGT_OPER|KOGT_DIST)) LED_FIELD[LED_NOMER]&=~0x11;
                }
            }

            void show_lcd()
            {
                LCD_abc((char*)STRING,0);
                if (net_fl&(1<<NET_FLAG)) {
                    LCD_abc((char*)error_str,6);
                }
                else {

                    //LCD_uind(t_klap_counter,9,2|LEAD_ZERO);

                    if  (stan&KOGT_OP) LCD_abc((char*)stad_str[0],6);
                    else LCD_abc((char*)stad_str[1],6);
                    if (stad&(1<<KOGT_C_OPEN)) LCD_abc((char*)stad_str[0],4);
                    if (stad&(1<<KOGT_C_CLOSE)) LCD_abc((char*)stad_str[1],4);

                    if (stan&(KOGT_OPER|KOGT_DIST)) {
                        if (stan&KOGT_DIST) LCD_abc((char*)dist_str,   12);//19
                        if (stan&KOGT_OPER) LCD_abc((char*)oper_str,   12);//19
                    }
                    else {
                        LCD_abc((char*)auto_str,   12);//19
                    }

                    if (stan&(KOGT_OS_ERROR|KOGT_STAN)) {
                        LCD_abc((char*)error_str,20);
                        if (stan&KOGT_OS_ERROR) LCD_abc((char*)os_err_str,      34);
                        if (stan&KOGT_STAN)   LCD_abc((char*)press_err_str,   23);//19
                    }
    //                if (stan&(MOE_OS_ERROR|MOE_STAN)) {
    //                    LCD_abc((char*)error_str,20);
    ////                    if(stan&MOE_PRESS_ERROR)    LCD_abc((char*)press_err_str,   23);//19
    ////                    if(stan&MOE_MP_ERROR)       LCD_abc((char*)mp_err_str,      27);//23
    ////                    if(stan&MOE_KTR_ERROR)      LCD_abc((char*)ktr_err_str,     30);//26
    //                    if(stan&MOE_OS_ERROR)       LCD_abc((char*)os_err_str,      34);
    //                    if(stan&MOE_STAN)           LCD_abc((char*)stan_err_str,    28);
    //                }

                    LCD_uind(stad,28,2|LEAD_ZERO);
                    LCD_uind(stan,31,2|LEAD_ZERO);

                    //if(stan&KOGT_SUXAR) LCD_abc((char*)vidk_str,    23);
                    //else LCD_abc((char*)zakr_str,    23);

                    //if (stan&MOE_SUXAR)

                    if (stan&KOGT_OPER) {
                        if(KEY_8) {
                            if(!(stad&(1<<KOGT_ST_OPEN)))
                            {
                                stad|=(1<<KOGT_ST_OPEN);
                                //t_klap_counter=WORK+PAUSE+2;

                            }
                        }
                        if(KEY_NO) {
                            if(!(stad&(1<<KOGT_ST_CLOSE)))
                            {
                                stad|=(1<<KOGT_ST_CLOSE);
                                //t_klap_counter=0;
                            }
                        }
                        if (KEY_1) stad|=(1<<KOGT_ST_ERR);
                        if (KEY_4) {
                            stad|=(1<<KOGT_ST_AVTO);
                        }
                    }
                    else {
                        if (!(stan&(KOGT_OPER|KOGT_DIST))) if (KEY_7) stad|=(1<<KOGT_ST_OPER);
                        if (stan&(KOGT_DIST|KOGT_OPER)) if (KEY_4) stad|=(1<<KOGT_ST_AVTO);
                    }
                }
            }

	};

#endif
