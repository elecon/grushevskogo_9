#ifndef __NLS_H
	#define __NLS_H


	#if (__AVR_ATmega128__)
		#define NUM_OF_MNEMO 1
	#endif
	#if (__AVR_ATmega1281__)
		#define NUM_OF_MNEMO 32
	#endif
	extern uint8_t MSK_FIELD[64],OS_FIELD[16],OUT_FIELD[16],LED_FIELD[NUM_OF_MNEMO*80];

	#define red_lamp 		0xf0
	#define green_lamp 		0x0f
	#define yellow_lamp 	0x00
	#define null_lamp		0xff
	#define red_b_lamp		0xf3
	#define green_b_lamp	0x3f
	#define red_bb_lamp		0xa0
	#define greeen_bb_lamp	0x0a
	//мнемосхема

	#define mReady		        LED_FIELD[33]
	#define mReady2		        LED_FIELD[15]
	#define mReady3		        LED_FIELD[48]
	#define mReady4		        LED_FIELD[64]
//-------------------------------------------------------------------------
//																   пристрої
//-------------------------------------------------------------------------
//	#define mZ_21		        LED_FIELD[78]
#if s03shpz_1
    #define mVZK_1_1	        LED_FIELD[24]
    #define mVZK_1_2	        LED_FIELD[25]
    #define mVZK_1_3	        LED_FIELD[26]
    #define mVZK_1_4	        LED_FIELD[16]
    #define mVZK_1_5	        LED_FIELD[17]

    #define mVZK_1_6	        LED_FIELD[18]
    #define mVZK_1_7	        LED_FIELD[8]
    #define mVZK_1_8	        LED_FIELD[9]
    #define mVZK_1_9	        LED_FIELD[10]
    #define mVZK_1_10	        LED_FIELD[0]

    #define mVZK_1_11	        LED_FIELD[1]
    #define mVZK_1_12	        LED_FIELD[30]
    #define mVZK_1_13	        LED_FIELD[22]
    #define mVZK_1_14	        LED_FIELD[31]
    #define mVZK_1_15	        LED_FIELD[23]

    #define mVZK_1_16	        LED_FIELD[64]
    #define mVZK_1_17	        LED_FIELD[56]
    #define mVZK_1_18	        LED_FIELD[14]
    #define mVZK_1_19	        LED_FIELD[15]
    #define mVZK_1_20	        LED_FIELD[6]

    #define mVZK_1_21	        LED_FIELD[7]
    #define mVZK_1_22	        LED_FIELD[40]
    #define mVZK_1_23	        LED_FIELD[67]
    #define mVZK_1_24	        LED_FIELD[68]
    #define mVZK_1_25	        LED_FIELD[69]

    #define mVZK_1_26	        LED_FIELD[59]
    #define mVZK_1_27	        LED_FIELD[60]
    #define mVZK_1_28	        LED_FIELD[61]
    #define mVZK_1_29	        LED_FIELD[51]
    #define mVZK_1_30	        LED_FIELD[52]

    #define mVZK_1_31	        LED_FIELD[43]
    #define mVZK_1_32	        LED_FIELD[44]
    #define mVZK_1_33	        LED_FIELD[45]
    #define mVZK_1_34	        LED_FIELD[32]
    #define mVZK_1_35	        LED_FIELD[32]
#endif
#if SHPZ_6
    #define mVZK_1_1	        LED_FIELD[24]
    #define mVZK_1_2	        LED_FIELD[25]
    #define mVZK_1_3	        LED_FIELD[26]
    #define mVZK_1_4	        LED_FIELD[16]
    #define mVZK_1_5	        LED_FIELD[17]

    #define mVZK_1_6	        LED_FIELD[18]
    #define mVZK_1_7	        LED_FIELD[8]
    #define mVZK_1_8	        LED_FIELD[9]
    #define mVZK_1_9	        LED_FIELD[0]
    #define mVZK_1_10	        LED_FIELD[1]

    #define mVZK_1_11	        LED_FIELD[2]
    #define mVZK_1_12	        LED_FIELD[30]
    #define mVZK_1_13	        LED_FIELD[22]
    #define mVZK_1_14	        LED_FIELD[31]
    #define mVZK_1_15	        LED_FIELD[23]

    #define mVZK_1_16	        LED_FIELD[64]
    #define mVZK_1_17	        LED_FIELD[56]
    #define mVZK_1_18	        LED_FIELD[14]
    #define mVZK_1_19	        LED_FIELD[67]
    #define mVZK_1_20	        LED_FIELD[68]

    #define mVZK_1_21	        LED_FIELD[69]
    #define mVZK_1_22	        LED_FIELD[59]
    #define mVZK_1_23	        LED_FIELD[60]
    #define mVZK_1_24	        LED_FIELD[61]
    #define mVZK_1_25	        LED_FIELD[51]

    #define mVZK_1_26	        LED_FIELD[52]


    #define mVZK_1_27	        LED_FIELD[32]
    #define mVZK_1_28	        LED_FIELD[32]
    #define mVZK_1_29	        LED_FIELD[32]
    #define mVZK_1_30	        LED_FIELD[32]

    #define mVZK_1_31	        LED_FIELD[32]
    #define mVZK_1_32	        LED_FIELD[32]
    #define mVZK_1_33	        LED_FIELD[32]
    #define mVZK_1_34	        LED_FIELD[32]
    #define mVZK_1_35	        LED_FIELD[32]
#endif
#if SHPZ_9
    #define mVZK_1_1	        LED_FIELD[24]
    #define mVZK_1_2	        LED_FIELD[25]
    #define mVZK_1_3	        LED_FIELD[26]
    #define mVZK_1_4	        LED_FIELD[16]
    #define mVZK_1_5	        LED_FIELD[17]

    #define mVZK_1_6	        LED_FIELD[18]
    #define mVZK_1_7	        LED_FIELD[8]
    #define mVZK_1_8	        LED_FIELD[9]
    #define mVZK_1_9	        LED_FIELD[0]
    #define mVZK_1_10	        LED_FIELD[1]

    #define mVZK_1_11	        LED_FIELD[2]
    #define mVZK_1_12	        LED_FIELD[30]
    #define mVZK_1_13	        LED_FIELD[22]
    #define mVZK_1_14	        LED_FIELD[31]
    #define mVZK_1_15	        LED_FIELD[23]

    #define mVZK_1_16	        LED_FIELD[14]
    #define mVZK_1_17	        LED_FIELD[64]
    #define mVZK_1_18	        LED_FIELD[56]
    #define mVZK_1_19	        LED_FIELD[15]
    #define mVZK_1_20	        LED_FIELD[48]

    #define mVZK_1_21	        LED_FIELD[49]
    #define mVZK_1_22	        LED_FIELD[6]
    #define mVZK_1_23	        LED_FIELD[7]
    #define mVZK_1_24	        LED_FIELD[67]
    #define mVZK_1_25	        LED_FIELD[68]

    #define mVZK_1_26	        LED_FIELD[69]
    #define mVZK_1_27	        LED_FIELD[59]
    #define mVZK_1_28	        LED_FIELD[60]
    #define mVZK_1_29	        LED_FIELD[51]
    #define mVZK_1_30	        LED_FIELD[52]

    #define mVZK_1_31	        LED_FIELD[32]
    #define mVZK_1_32	        LED_FIELD[32]
    #define mVZK_1_33	        LED_FIELD[32]
    #define mVZK_1_34	        LED_FIELD[32]
    #define mVZK_1_35	        LED_FIELD[32]
#endif
#if SHPZ_14
    #define mVZK_1_1	        LED_FIELD[24]
    #define mVZK_1_2	        LED_FIELD[25]
    #define mVZK_1_3	        LED_FIELD[26]
    #define mVZK_1_4	        LED_FIELD[16]
    #define mVZK_1_5	        LED_FIELD[17]

    #define mVZK_1_6	        LED_FIELD[18]
    #define mVZK_1_7	        LED_FIELD[8]
    #define mVZK_1_8	        LED_FIELD[9]
    #define mVZK_1_9	        LED_FIELD[0]
    #define mVZK_1_10	        LED_FIELD[30]

    #define mVZK_1_11	        LED_FIELD[22]
    #define mVZK_1_12	        LED_FIELD[31]
    #define mVZK_1_13	        LED_FIELD[23]
    #define mVZK_1_14	        LED_FIELD[64]
    #define mVZK_1_15	        LED_FIELD[56]

    #define mVZK_1_16	        LED_FIELD[14]
    #define mVZK_1_17	        LED_FIELD[67]
    #define mVZK_1_18	        LED_FIELD[68]
    #define mVZK_1_19	        LED_FIELD[69]
    #define mVZK_1_20	        LED_FIELD[59]

    #define mVZK_1_21	        LED_FIELD[60]
    #define mVZK_1_22	        LED_FIELD[61]
    #define mVZK_1_23	        LED_FIELD[51]
    #define mVZK_1_24	        LED_FIELD[52]
    #define mVZK_1_25	        LED_FIELD[43]

    #define mVZK_1_26	        LED_FIELD[44]
    #define mVZK_1_27	        LED_FIELD[45]
    #define mVZK_1_28	        LED_FIELD[32]
    #define mVZK_1_29	        LED_FIELD[32]
    #define mVZK_1_30	        LED_FIELD[32]

    #define mVZK_1_31	        LED_FIELD[32]
    #define mVZK_1_32	        LED_FIELD[32]
    #define mVZK_1_33	        LED_FIELD[32]
    #define mVZK_1_34	        LED_FIELD[32]
    #define mVZK_1_35	        LED_FIELD[32]
#endif
//-------------------------------------------------------------------------
//														  мережеві пристрої
//-------------------------------------------------------------------------
	#define mGR1		        LED_FIELD[7]
	#define mGR4		        LED_FIELD[77]

    #define mMSK1		        LED_FIELD[0]
    #define mMSK2		        LED_FIELD[1]
    #define mMSK3		        LED_FIELD[2]
    #define mMSK4		        LED_FIELD[3]
    #define mMSK5		        LED_FIELD[4]

    #define mMSK6		        LED_FIELD[5]
    #define mMSK7		        LED_FIELD[6]
    #define mMSK8		        LED_FIELD[7]
    #define mMSK9		        LED_FIELD[40]
    #define mMSK10		        LED_FIELD[41]

    #define mMSK11		        LED_FIELD[42]
    #define mMSK12		        LED_FIELD[43]
    #define mMSK13		        LED_FIELD[44]
    #define mMSK14		        LED_FIELD[45]
    #define mMSK15		        LED_FIELD[46]

    #define mMSK16		        LED_FIELD[47]

     #define mFIRE_KNOP_1      LED_FIELD[20]
     #define mFIRE_KNOP_2      LED_FIELD[58]
     #define mFIRE_KNOP_3      LED_FIELD[63]

     #define mFIRE_FL_KN1      LED_FIELD[37]
     #define mFIRE_FL_KN2      LED_FIELD[74]
     #define mFIRE_FL_KN3      LED_FIELD[79]


//-------------------------------------------------------------------------
//															 сухие контакты
//-------------------------------------------------------------------------
	#define KTEST				MSK_FIELD[31+0*32-1]

	#define K_GR4				MSK_FIELD[1+0*32-1]
	#define K_MSK_N				MSK_FIELD[2+0*32-1]
	#define K_OUT3				MSK_FIELD[0][3]
	#define K_OUT4				MSK_FIELD[0][4]
	#define K_OUT5				MSK_FIELD[0][5]

	#define K_OUT6				MSK_FIELD[0][6]
	#define K_OUT7				MSK_FIELD[0][7]
	#define K_OUT8				MSK_FIELD[0][8]
	#define K_OUT9				MSK_FIELD[0][9]
	#define K_OUT10				MSK_FIELD[0][10]

	#define kVZK_1_1			MSK_FIELD[31+1*32]
	#define kVZK_1_2			MSK_FIELD[16+1*32]
	#define kVZK_1_3			MSK_FIELD[17+1*32]
	#define kVZK_1_4			MSK_FIELD[18+1*32]
	#define kVZK_1_5			MSK_FIELD[19+1*32]

	#define kVZK_1_6			MSK_FIELD[20+1*32]
	#define kVZK_1_7			MSK_FIELD[21+1*32]
	#define kVZK_1_8			MSK_FIELD[22+1*32]
	#define kVZK_1_9			MSK_FIELD[23+1*32]
	#define kVZK_1_10			MSK_FIELD[ 8+1*32]

	#define kVZK_1_11			MSK_FIELD[ 9+1*32]
	#define kVZK_1_12			MSK_FIELD[10+1*32]
	#define kVZK_1_13			MSK_FIELD[11+1*32]
	#define kVZK_1_14			MSK_FIELD[12+1*32]
	#define kVZK_1_15			MSK_FIELD[13+1*32]

	#define kVZK_1_16			MSK_FIELD[14+1*32]
	#define kVZK_1_17			MSK_FIELD[15+1*32]
	#define kVZK_1_18			MSK_FIELD[ 0+1*32]
	#define kVZK_1_19			MSK_FIELD[ 1+1*32]
	#define kVZK_1_20			MSK_FIELD[ 2+1*32]

	#define kVZK_1_21			MSK_FIELD[ 3+1*32]
	#define kVZK_1_22			MSK_FIELD[ 4+1*32]
	#define kVZK_1_23			MSK_FIELD[ 5+1*32]
	#define kVZK_1_24			MSK_FIELD[ 6+1*32]
	#define kVZK_1_25			MSK_FIELD[ 7+1*32]

	#define kVZK_1_26			MSK_FIELD[24+0*32]
	#define kVZK_1_27			MSK_FIELD[25+0*32]
	#define kVZK_1_28			MSK_FIELD[26+0*32]
	#define kVZK_1_29			MSK_FIELD[27+0*32]
	#define kVZK_1_30			MSK_FIELD[28+0*32]

	#define kVZK_1_31			MSK_FIELD[29+0*32]
	#define kVZK_1_32			MSK_FIELD[30+0*32]
	#define kVZK_1_33			MSK_FIELD[31+0*32]
	#define kVZK_1_34			MSK_FIELD[16+0*32]
	#define kVZK_1_35			MSK_FIELD[17+0*32]





    #define kKNOP_FLOORE_1__1   MSK_FIELD[1+0*32]
    #define kKNOP_FLOORE_1__2   MSK_FIELD[2+0*32]
    #define kKNOP_FLOORE_2__1   MSK_FIELD[3+0*32]
    #define kKNOP_FLOORE_2__2   MSK_FIELD[4+0*32]
    #define kKNOP_FLOORE_3__1   MSK_FIELD[5+0*32]
    #define kKNOP_FLOORE_3__2   MSK_FIELD[6+0*32]
//-------------------------------------------------------------------------
//															 обратные связи
//-------------------------------------------------------------------------
	#define OS_GR1			    OS_FIELD[0]
	#define OS_GR4			    OS_FIELD[2]


//--------------------------------------------------------------------------
//																	  выдача
//--------------------------------------------------------------------------


	#define OP_GR1			    OUT_FIELD[0]
	#define OP_GR4			    OUT_FIELD[1]

	#define OP_VZK_GR1          OUT_FIELD[6]
	#define OP_VZK_GR2          OUT_FIELD[7]
	#define OP_VZK_GR3          OUT_FIELD[8]
	#define OP_VZK_GR4          OUT_FIELD[4]
	#define OP_VZK_GR5          OUT_FIELD[5]
	#define OP_VZK_GR6          OUT_FIELD[6]

	#define OP_ZUMER		    OUT_FIELD[8]

	#define OP_VENT_KL		    OUT_FIELD[11]

#endif
