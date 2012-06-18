#ifndef __SEGM_485_H
 #define __SEGM_485_H

	#include <avr/io.h>
	#include <avr/pgmspace.h>

#define _SGM_EOS    0xFEFE

#define _SGM_SPACE  0xFFFF

#define _SGM_NUM_0  0xEEC0
#define _SGM_NUM_1  0xFEF9
#define _SGM_NUM_2  0xDDE4
#define _SGM_NUM_3  0xFCF2
#define _SGM_NUM_4  0xDDD9
#define _SGM_NUM_5  0xDDD2
#define _SGM_NUM_6  0xDDC2
#define _SGM_NUM_7  0xEEFE
#define _SGM_NUM_8  0xDDC0
#define _SGM_NUM_9  0xDDD0

#define _SGM_A      0xECF9
#define _SGM_B      0xDCC2
#define _SGM_E      0xDDC6
#define _SGM_H      0xDDC9
#define _SGM_I      0xF77F
#define _SGM_K      0xDACF
#define _SGM_M      0xFE89
#define _SGM_O      0xFFC0
#define _SGM_P      0xDDCC
#define _SGM_A      0xECF9
#define _SGM_C      0xFFC6
#define _SGM_T      0xF77E

#define _SGM_o      0xDDE3

#define _SGM_GG     0xD549
#define _SGM_LL     0xEEF9
#define _SGM_PP     0xFFC8
#define _SGM_FF     0xD55C
#define _SGM_RR     0xCDD8
#define _SGM_YY     0xDDD1
#define _SGM_DD     0xEEF1
#define _SGM_BB     0xDDC2
#define _SGM_ZZ     0xDDF0
#define _SGM_HH     0xDDD9
#define _SGM_II     0xEEC9


#define _SGM_pp     0xDDEB

#define START_SEGM_ADR 0x78

#define Q_SEGM_ONE_ADR 4  //4 символа на адресс
#define Q_STRS_SEGM 2     //две строки
#define Q_SEGM_ONE_STRS 8 //количество букв в строке

#define Q_SEGM Q_SEGM_ONE_STRS*Q_STRS_SEGM/Q_SEGM_ONE_ADR

extern uint16_t SegmStrs[Q_STRS_SEGM][Q_SEGM_ONE_STRS];
extern uint8_t cur_segm;

void InitSegm();
void ClearSegmStrs(uint8_t _str);
void SetSegmSimb(uint16_t _simb, uint8_t _str, uint8_t _pos);
void SetSegmStr(uint16_t* _str, uint8_t _num_str, uint8_t _pos);

#endif
