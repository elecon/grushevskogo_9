#ifndef __DEVMOE_H
	#define __DEVMOE_H

//    #define TAMPLE

	#include "DEVS.H"
    #include "Nls.h"

	enum {MOE_C_CLOSE,MOE_C_OPEN};
	enum {  MOE_ST_CLOSE,   //0x01
            MOE_ST_OPEN,    //0x02
            MOE_ST_OPER,    //0x04
            MOE_ST_DIST,    //0x08
            MOE_ST_AVTO,    //0x10

            MOE_ST_ERR      //0x20
    };

	//extern XZ moe;

    extern uint8_t LED_FIELD[NUM_OF_MNEMO*80];

    #define T_WAIT_PRESS 2
    #define T_WAIT_MP 2

    #define PAUSE 5
    #define WORK 2
	//флаги enh_info
	//Стан пристрою
	#define MOE_AUTO    	0x01 //
	#define MOE_OPER    	0x02 //
	#define MOE_DIST    	0x04 //
	#define MOE_OP      	0x08 //
	#define MOE_SUXAR   	0x80 //ошибка перепада давления
	#define MOE_COUNTER 	0x40 //ошибка магнитного пускателя
	#define MOE_STAN    	0x20 //ошибка теплового реле
	#define MOE_OS_ERROR	0x10 //ошибка обратной связи

	template <uint16_t LED_NOMER, uint8_t MSK_BIT,uint8_t OUT_BIT,uint16_t OPTIONS,const char *STRING>
	class MOE: public TDevObject
	{
        public:

            uint8_t t_repit_counter;
            uint8_t t_klap_counter;

//-----------------------------------------------------------------------------------------------
            void auto_open()
            {
                if(!(stad&(1<<MOE_ST_OPEN))) {
//                    if (stan&MOE_SUXAR) {
//
//                    }
//                    else {
                        stad|=(1<<MOE_ST_OPEN);
//                    }
                }
            }

            void auto_close()
            {
                if(!(stad&(1<<MOE_ST_CLOSE))) stad|=(1<<MOE_ST_CLOSE);
            }

            void check_press()
            {
//                switch(stad)
//                {
//                    case MOE_ST_OPEN:
//                        if(MSK_FIELD[MSK_BIT]) t_wait_press_counter=T_WAIT_PRESS;
//                    break;
//                    case MOE_ST_CLOSE:
//                        if(!MSK_FIELD[MSK_BIT]) t_wait_press_counter=T_WAIT_PRESS;
//                    break;
//                }
//                if(!sec_tik) if(t_wait_press_counter) t_wait_press_counter--;
//                if(!t_wait_press_counter) stan|=MOE_PRESS_ERROR;
                if (!(MSK_FIELD[MSK_BIT])) stan|=MOE_SUXAR; else stan&=~MOE_SUXAR;
            }

            void check_mp()
            {
                //uint8_t t_wait_mp_counter;
//                switch(stad)
//                {
//                    case MOE_ST_OPEN:
//                        if(MSK_FIELD[MSK_BIT])      t_wait_mp_counter=T_WAIT_MP;
//                    break;
//                    case MOE_ST_CLOSE:
//                        if(!MSK_FIELD[MSK_BIT])     t_wait_mp_counter=T_WAIT_MP;
//                    break;
//                }
//                if(!sec_tik) if(t_wait_mp_counter) t_wait_mp_counter--;
//                if(!t_wait_mp_counter) stan|=MOE_MP_ERROR;
            }

            void check_os()
            {
                if(!(OS_FIELD[OUT_BIT])) stan|=MOE_OS_ERROR;
                else stan&=~MOE_OS_ERROR;
            }

            void drv()
            {
                //if

                if (t_klap_counter) {
                    stan|=MOE_COUNTER;
                    if (stan&MOE_SUXAR) {
                        t_klap_counter=0;
                    }
                    if (!(stad&(1<<MOE_ST_OPEN))) {
                        stad&=~(1<<MOE_ST_OPEN);
                        //t_klap_counter=WORK+PAUSE+2;
                    }

                    if (stad&(1<<MOE_ST_CLOSE)) {
                        stad&=~(1<<MOE_ST_CLOSE);
                        t_klap_counter=0;
                    }
                    else {
                        if (t_klap_counter>2) {
                            if (!sec_tik) t_klap_counter--;
                            if (t_klap_counter>PAUSE+2) {
                                //stad|=(1<<MOE_ST_OPEN);
                            }
                            else {
                                //if (stan&MOE_SUXAR) stan|=MOE_STAN;
                                //stad|=(1<<MOE_ST_CLOSE);
                                //t_klap_counter=0;
                            }
                        }
                        else {
                            if (stan&MOE_SUXAR) {
                                //stad|=(1<<MOE_ST_CLOSE);
                                t_klap_counter=0;
                            }
                            else {
                                t_klap_counter=WORK+PAUSE+2;


                            }

                        }
                    }
                }
                else {
                    //stad|=(1<<MOE_ST_CLOSE);
                    stan&=~MOE_COUNTER;
                    if (stad&(1<<MOE_ST_OPEN)) {
                        stad&=~(1<<MOE_ST_OPEN);
                        //t_klap_counter=WORK+PAUSE+2;
                         if (stan&MOE_SUXAR) {
                            t_klap_counter=0;
                        }
                        else {
                            t_klap_counter=WORK+PAUSE+2;
                        }
                    }
                    if (stad&(1<<MOE_ST_CLOSE)) {
                        stad&=~(1<<MOE_ST_CLOSE);
                        t_klap_counter=0;
                    }
                }

                if (t_klap_counter) {
                    if (t_klap_counter>PAUSE+2) {
                        stan |= MOE_OP;
                        OUT_FIELD[OUT_BIT]=0xff;
                    }
                    else {
                        OUT_FIELD[OUT_BIT]=0x00;
                        stan &=~ MOE_OP;
                    }
                }
                else {
                    OUT_FIELD[OUT_BIT]=0x00;
                    stan &=~ MOE_OP;
                }


//                if (stad&(1<<MOE_ST_OPEN)) {
//                    stad&=~(1<<MOE_ST_OPEN);
//                    OUT_FIELD[OUT_BIT]=0xff;
//                    stan |= MOE_OP;
//                }
//                else {
//                    if (stad&(1<<MOE_ST_CLOSE)) {
//                        stad&=~(1<<MOE_ST_CLOSE);
//                        OUT_FIELD[OUT_BIT]=0x00;
//                        stan &=~ MOE_OP;
//                    }
//                }
                if (!(stan&(MOE_OPER|MOE_DIST))) {
                    if (stad&(1<<MOE_ST_OPER)) {
                        stad&=~(1<<MOE_ST_OPER);
                        stan|=MOE_OPER;
                        //stan&=~(MOE_AUTO);
                    }
                    else {
                        if (stad&(1<<MOE_ST_DIST)) {
                            stad&=~(1<<MOE_ST_DIST);
                            stan|=MOE_DIST;
                            //stan&=~(MOE_AUTO);
                        }
                    }
                }
                else {
                    if (stan&(MOE_DIST|MOE_OPER)) {
                        if (stad&(1<<MOE_ST_AVTO))  {
                            stad&=~(1<<MOE_ST_AVTO);
                            //stan|=MOE_AUTO;
                            stan&=~(MOE_DIST|MOE_OPER);
                        }
                    }
                }

                if(OPTIONS&OPT_CHECK_PRESS) check_press();
                //if(OPTIONS&OPT_CHECK_MP) check_mp();
//                if(OPTIONS&VZK_CHECK_KTR) check_ktr();
                if(OPTIONS&OPT_CHECK_OS) check_os();
            }

            void show_mnem()
            {
                if (stan&MOE_COUNTER)
                    LED_FIELD[LED_NOMER]=red_b_lamp;
                else {
                    if (stan&MOE_SUXAR) LED_FIELD[LED_NOMER]=red_lamp; else LED_FIELD[LED_NOMER]=green_lamp;
                }

                if (stan&MOE_OS_ERROR) LED_FIELD[LED_NOMER]&=~0x11;
                if (stan&(MOE_OPER|MOE_DIST)) LED_FIELD[LED_NOMER]&=~0x11;

            }

            void show_lcd()
            {
                LCD_abc((char*)STRING,0);

                LCD_uind(t_klap_counter,9,2|LEAD_ZERO);

                if  (stan&MOE_OP) LCD_abc((char*)stad_str[0],6);
                else LCD_abc((char*)stad_str[1],6);
                if (stad&(1<<MOE_C_OPEN)) LCD_abc((char*)stad_str[0],4);
                if (stad&(1<<MOE_C_CLOSE)) LCD_abc((char*)stad_str[1],4);

                if (stan&(MOE_OPER|MOE_DIST)) {
                    if (stan&MOE_DIST) LCD_abc((char*)dist_str,   12);//19
                    if (stan&MOE_OPER) LCD_abc((char*)oper_str,   12);//19
                }
                else {
                    LCD_abc((char*)auto_str,   12);//19
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

                if(stan&MOE_SUXAR) LCD_abc((char*)vidk_str,    23);
                else LCD_abc((char*)zakr_str,    23);

                //if (stan&MOE_SUXAR)

                if (stan&MOE_OPER) {
                    if(KEY_8) {
                        if(!(stad&(1<<MOE_ST_OPEN)))
                        {
                            stad|=(1<<MOE_ST_OPEN);
                            //t_klap_counter=WORK+PAUSE+2;

                        }
                    }
                    if(KEY_NO) {
                        if(!(stad&(1<<MOE_ST_CLOSE)))
                        {
                            stad|=(1<<MOE_ST_CLOSE);
                            //t_klap_counter=0;
                        }
                    }
                    if (KEY_1) stad|=(1<<MOE_ST_ERR);
                    if (KEY_4) {
                        stad|=(1<<MOE_ST_AVTO);
                    }
                }
                else {
                    if (!(stan&(MOE_OPER|MOE_DIST))) if (KEY_7) stad|=(1<<MOE_ST_OPER);
                    if (stan&(MOE_DIST|MOE_OPER)) if (KEY_4) stad|=(1<<MOE_ST_AVTO);
                }
            }

//-----------------------------------------------------------------------------------------------
	};
    template <  uint16_t LED_NOMER,
                const char *STRING,
                NET_OUTPUT_STRUCT1 *D_IN,
                NET_INPUT_STRUCT1 *D_OUT,
                uint8_t NET_BITE,
                uint8_t NET_FLAG>
	class MOE_NET : public TDevObject
	{
	  public:
            //uint8_t mmmm;

            void drv ()
            {
                stan = D_IN->devs_net_stat[NET_BITE];

                if (stan&(MOE_COUNTER|MOE_SUXAR)) {
                    stad&=~(1<<MOE_ST_OPEN);
                }
                else {
                    if ((D_OUT->devs_net_cmd[NET_BITE])&(1<<MOE_ST_OPEN)) stad|=(1<<MOE_ST_OPEN);
                }
                if (!(stan&(MOE_OPER|MOE_DIST))) stad&=~(1<<MOE_ST_AVTO);
                if (stan&MOE_OPER) stad&=~(1<<MOE_ST_OPER);
                if (!(stan&MOE_COUNTER)) stad&=~(1<<MOE_ST_CLOSE);


                D_OUT->devs_net_cmd[NET_BITE] = stad;
            }


            void show_mnem()
            {
                if (net_fl&(1<<NET_FLAG)) {
                    LED_FIELD[LED_NOMER]=null_lamp;
                }
                else {
                    if (stan&MOE_COUNTER)
                        LED_FIELD[LED_NOMER]=red_b_lamp;
                    else {
                        if (stan&MOE_SUXAR) LED_FIELD[LED_NOMER]=red_lamp; else LED_FIELD[LED_NOMER]=green_lamp;
                    }

                    if (stan&MOE_OS_ERROR) LED_FIELD[LED_NOMER]&=~0x11;
                    if (stan&(MOE_OPER|MOE_DIST)) LED_FIELD[LED_NOMER]&=~0x11;
                }


            }

            void show_lcd()
            {
                LCD_abc((char*)STRING,0);
                if (net_fl&(1<<NET_FLAG)) {
                    LCD_abc((char*)error_str,6);
                }
                else {
                    if  (stan&MOE_OP) LCD_abc((char*)stad_str[0],6);
                    else LCD_abc((char*)stad_str[1],6);

                    if (stan&(MOE_OPER|MOE_DIST)) {
                        if (stan&MOE_DIST) LCD_abc((char*)dist_str,   12);//19
                        if (stan&MOE_OPER) LCD_abc((char*)oper_str,   12);//19
                    }
                    else {
                        LCD_abc((char*)auto_str,   12);//19
                    }

                    if (stan&(MOE_OS_ERROR|MOE_STAN)) {
                        LCD_abc((char*)error_str,20);
    //                    if(stan&MOE_PRESS_ERROR)    LCD_abc((char*)press_err_str,   23);//19
    //                    if(stan&MOE_MP_ERROR)       LCD_abc((char*)mp_err_str,      27);//23
    //                    if(stan&MOE_KTR_ERROR)      LCD_abc((char*)ktr_err_str,     30);//26
                        if(stan&MOE_OS_ERROR)       LCD_abc((char*)os_err_str,      34);
                        if(stan&MOE_STAN)           LCD_abc((char*)stan_err_str,    28);
                    }

                    if(stan&MOE_SUXAR) LCD_abc((char*)vidk_str,    23);
                    else LCD_abc((char*)zakr_str,    23);

                    //if (stan&MOE_SUXAR)

                     if (stan&MOE_OPER) {
                        if(KEY_8) {
                            if(!(stad&(1<<MOE_ST_OPEN)))
                            {
                                stad|=(1<<MOE_ST_OPEN);
                                //t_klap_counter=WORK+PAUSE+2;

                            }
                        }
                        if(KEY_NO) {
                            if(!(stad&(1<<MOE_ST_CLOSE)))
                            {
                                stad|=(1<<MOE_ST_CLOSE);
                                //t_klap_counter=0;
                            }
                        }
                        if (KEY_1) stad|=(1<<MOE_ST_ERR);
                        if (KEY_4) {
                            stad|=(1<<MOE_ST_AVTO);
                        }
                    }
                    else {
                        if (!(stan&(MOE_OPER|MOE_DIST))) if (KEY_7) stad|=(1<<MOE_ST_OPER);
                        if (stan&(MOE_DIST|MOE_OPER)) if (KEY_4) stad|=(1<<MOE_ST_AVTO);
                    }
                }
            }
	};

#endif
