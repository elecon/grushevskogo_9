#ifndef __NLS_C_H
	#define __NLS_C_H


//-------------------------------------------------------------------------
//																   пристрої
//-------------------------------------------------------------------------
//	#define mZ_21		        LED_FIELD[78]

    #define mVZK_0_1	        LED_FIELD[ 7+80*16]
    #define mVZK_0_2	        LED_FIELD[40+80*16]
    #define mVZK_0_3	        LED_FIELD[15+80*16]
    #define mVZK_0_4	        LED_FIELD[48+80*16]
    #define mVZK_0_5	        LED_FIELD[49+80*16]

    #define mVZK_0_6	        LED_FIELD[50+80*16]
    #define mVZK_0_7	        LED_FIELD[51+80*16]
    #define mVZK_0_8	        LED_FIELD[52+80*16]
    #define mVZK_0_9	        LED_FIELD[53+80*16]
    #define mVZK_0_10	        LED_FIELD[54+80*16]

    #define mVZK_C_11	        LED_FIELD[55+80*16]
    #define mVZK_C_12	        LED_FIELD[41+80*16]
    #define mVZK_C_13	        LED_FIELD[42+80*16]
    #define mVZK_C_14	        LED_FIELD[43+80*16]
    #define mVZK_C_15	        LED_FIELD[44+80*16]

    #define mVZK_1_1	        LED_FIELD[31+80*16]
    #define mVZK_1_2	        LED_FIELD[65+80*16]
    #define mVZK_1_3	        LED_FIELD[66+80*16]
    #define mVZK_1_4	        LED_FIELD[67+80*16]
    #define mVZK_1_5	        LED_FIELD[64+80*16]


//-------------------------------------------------------------------------
//															 сухие контакты
//-------------------------------------------------------------------------
    #define kVZK_0_1			MSK_FIELD[28+0*32]
	#define kVZK_0_2			MSK_FIELD[29+0*32]
	#define kVZK_0_3			MSK_FIELD[30+0*32]
	#define kVZK_0_4			MSK_FIELD[31+0*32]
	#define kVZK_0_5			MSK_FIELD[16+0*32]

	#define kVZK_0_6			MSK_FIELD[17+0*32]
	#define kVZK_0_7			MSK_FIELD[18+0*32]
	#define kVZK_0_8			MSK_FIELD[19+0*32]
	#define kVZK_0_9			MSK_FIELD[20+0*32]
	#define kVZK_0_10			MSK_FIELD[21+0*32]

	#define kVZK_0_11			MSK_FIELD[22+0*32]
	#define kVZK_0_12			MSK_FIELD[23+0*32]
	#define kVZK_0_13			MSK_FIELD[8+0*32]
	#define kVZK_0_14			MSK_FIELD[9+0*32]
	#define kVZK_0_15			MSK_FIELD[10+0*32]

    #define kVZK_1_1			MSK_FIELD[11+0*32]
	#define kVZK_1_2			MSK_FIELD[12+0*32]
	#define kVZK_1_3			MSK_FIELD[13+0*32]
	#define kVZK_1_4			MSK_FIELD[14+0*32]
	#define kVZK_1_5			MSK_FIELD[15+0*32]

    #define kKNOP_FLOORE_1__1   MSK_FIELD[4+0*32]
    #define kKNOP_FLOORE_1__2   MSK_FIELD[5+0*32]
    #define kKNOP_FLOORE_2__1   MSK_FIELD[6+0*32]
    #define kKNOP_FLOORE_2__2   MSK_FIELD[7+0*32]

    #define KTEST				MSK_FIELD[6+1*32]
//--------------------------------------------------------------------------
//																	  выдача
//--------------------------------------------------------------------------
	#define OP_VZK0			    OUT_FIELD[4]
	#define OP_VZK1			    OUT_FIELD[5]
	#define OP_ZUMER		    OUT_FIELD[15]
#endif
