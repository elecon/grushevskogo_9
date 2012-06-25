/*
$Author$
$Date$
$Tag$
$IdShort$
$Id$
$IdInfo$
*/
#ifndef __NLS_H
	#define __NLS_H

    #include "Nls_C.h"
    #include "Nls_02.h"
    #include "Nls_3.h"
    #include "Nls_6.h"
    #include "Nls_9.h"
    #include "Nls_11.h"
    #include "Nls_14.h"
    #include "Nls_16.h"
    #include "Nls_18.h"

	#if (__AVR_ATmega128__)
		#define NUM_OF_MNEMO 12
	#endif
	#if (__AVR_ATmega1281__||__AVR_ATmega1280__)
		#define NUM_OF_MNEMO 18
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

	#define mReady		        LED_FIELD[25]

	#define mSHPZ02		        LED_FIELD[61+80*15]
	#define mSHPZ3		        LED_FIELD[16+80*14]
	#define mSHPZ6		        LED_FIELD[ 8+80*12]
	#define mSHPZ9		        LED_FIELD[24+80*10]
	#define mSHPZ11		        LED_FIELD[16+80*8]

	#define mSHPZ14		        LED_FIELD[24+80*6]
	#define mSHPZ16		        LED_FIELD[24+80*4]
	#define mSHPZ18		        LED_FIELD[24+80*2]
	#define mSHPZ20		        LED_FIELD[64+80*0]
	#define mSHPZ21		        LED_FIELD[27+80*1]

	#define mNULL_LAMP          LED_FIELD[0+80*0]

	#define mFIRE_PK0_C         LED_FIELD[18+80*16]
	#define mFIRE_PK1_C         LED_FIELD[26+80*16]
	#define mFIRE_PK2_C         LED_FIELD[ 2+80*14]
	#define mFIRE_PK3_C         LED_FIELD[18+80*14]
	#define mFIRE_PK4_C         LED_FIELD[26+80*14]

	#define mFIRE_PK5_C         LED_FIELD[ 2+80*12]
	#define mFIRE_PK6_C         LED_FIELD[10+80*12]
	#define mFIRE_PK7_C         LED_FIELD[26+80*12]
	#define mFIRE_PK8_C         LED_FIELD[10+80*10]
	#define mFIRE_PK9_C         LED_FIELD[26+80*10]

	#define mFIRE_PK10_C        LED_FIELD[ 2+80*8]
	#define mFIRE_PK11_C        LED_FIELD[18+80*8]
	#define mFIRE_PK12_C        LED_FIELD[34+80*8]
	#define mFIRE_PK13_C        LED_FIELD[10+80*6]
	#define mFIRE_PK14_C        LED_FIELD[26+80*6]

	#define mFIRE_PK15_C        LED_FIELD[ 2+80*4]
	#define mFIRE_PK16_C        LED_FIELD[26+80*4]
	#define mFIRE_PK17_C        LED_FIELD[34+80*4]
	#define mFIRE_PK18_C        LED_FIELD[26+80*2]
	#define mFIRE_PK19_C        LED_FIELD[34+80*2]

	#define mFIRE_SPS0_C        LED_FIELD[17+80*16]
	#define mFIRE_SPS1_C        LED_FIELD[25+80*16]
	#define mFIRE_SPS2_C        LED_FIELD[ 1+80*14]
	#define mFIRE_SPS3_C        LED_FIELD[17+80*14]
	#define mFIRE_SPS4_C        LED_FIELD[25+80*14]

	#define mFIRE_SPS5_C        LED_FIELD[ 1+80*12]
	#define mFIRE_SPS6_C        LED_FIELD[ 9+80*12]
	#define mFIRE_SPS7_C        LED_FIELD[25+80*12]
	#define mFIRE_SPS8_C        LED_FIELD[ 9+80*10]
	#define mFIRE_SPS9_C        LED_FIELD[25+80*10]

	#define mFIRE_SPS10_C       LED_FIELD[ 1+80*8]
	#define mFIRE_SPS11_C       LED_FIELD[17+80*8]
	#define mFIRE_SPS12_C       LED_FIELD[33+80*8]
	#define mFIRE_SPS13_C       LED_FIELD[ 9+80*6]
	#define mFIRE_SPS14_C       LED_FIELD[25+80*6]

	#define mFIRE_SPS15_C       LED_FIELD[ 1+80*4]
	#define mFIRE_SPS16_C       LED_FIELD[25+80*4]
	#define mFIRE_SPS17_C       LED_FIELD[33+80*4]
	#define mFIRE_SPS18_C       LED_FIELD[25+80*2]
	#define mFIRE_SPS19_C       LED_FIELD[33+80*2]

    //
    #define kFIRE_FLOOR_0		MSK_FIELD[25+1*32]
    #define kFIRE_FLOOR_1		MSK_FIELD[26+1*32]
    #define kFIRE_FLOOR_2		MSK_FIELD[27+1*32]
    #define kFIRE_FLOOR_3		MSK_FIELD[28+1*32]
    #define kFIRE_FLOOR_4		MSK_FIELD[29+1*32]
    #define kFIRE_FLOOR_5		MSK_FIELD[30+1*32]
    #define kFIRE_FLOOR_6		MSK_FIELD[31+1*32]
    #define kFIRE_FLOOR_7		MSK_FIELD[16+1*32]

    #define kFIRE_FLOOR_8		MSK_FIELD[18+1*32]
    #define kFIRE_FLOOR_9		MSK_FIELD[19+1*32]
    #define kFIRE_FLOOR_10		MSK_FIELD[20+1*32]
    #define kFIRE_FLOOR_11		MSK_FIELD[21+1*32]
    #define kFIRE_FLOOR_12		MSK_FIELD[22+1*32]
    #define kFIRE_FLOOR_13		MSK_FIELD[23+1*32]
    #define kFIRE_FLOOR_14		MSK_FIELD[ 8+1*32]
    #define kFIRE_FLOOR_15		MSK_FIELD[10+1*32]

    #define kFIRE_FLOOR_16		MSK_FIELD[11+1*32]
    #define kFIRE_FLOOR_17		MSK_FIELD[12+1*32]
    #define kFIRE_FLOOR_18		MSK_FIELD[13+1*32]
    #define kFIRE_FLOOR_19		MSK_FIELD[14+1*32]

    #define kFIRE_FLOOR_0_0		MSK_FIELD[ 0+1*32]
    #define kFIRE_FLOOR_1_0		MSK_FIELD[ 1+1*32]
    #define kFIRE_FLOOR_2_0		MSK_FIELD[ 2+1*32]
    #define kFIRE_FLOOR_3_0		MSK_FIELD[ 3+1*32]

    #define kFIRE_ZONE_1		MSK_FIELD[24+1*32]
    #define kFIRE_ZONE_2		MSK_FIELD[17+1*32]
    #define kFIRE_ZONE_3		MSK_FIELD[ 9+1*32]
    #define kFIRE_ZONE_4		MSK_FIELD[15+1*32]

    //#define kFIRE_FLOOR_20		MSK_FIELD[0+1*32]


    #define kSTOP_PDZ   		MSK_FIELD[7+1*32]
#endif
