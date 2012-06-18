#include "Segm_485.h"

uint16_t SegmStrs[Q_STRS_SEGM][Q_SEGM_ONE_STRS];
uint8_t cur_segm;

void ClearSegmStrs(uint8_t _str)
{
	uint8_t i;
	for(i=0;i<Q_SEGM_ONE_STRS;++i)
	SegmStrs[_str][i] = _SGM_SPACE;
}

void SetSegmSimb(uint16_t _simb, uint8_t _str, uint8_t _pos)
{
	if(_pos >= Q_SEGM_ONE_STRS) return;
	if(_str >= Q_STRS_SEGM) return;
	SegmStrs[_str][_pos] = _simb;
}

void SetSegmStr(uint16_t* _str, uint8_t _num_str, uint8_t _pos)
{
	uint8_t i;
	//pgm_read_word((uint16_t*)&_str)
	if(_num_str >= Q_STRS_SEGM) return;

	for(i=0;i<Q_SEGM_ONE_STRS;++i)
	{
		if(pgm_read_word((uint16_t*)&_str[i])==_SGM_EOS) break;
		if((_pos+i) >= Q_SEGM_ONE_STRS) break;
		SegmStrs[_num_str][_pos+i] = pgm_read_word((uint16_t*)&_str[i]);
	}
}

const uint16_t PROGMEM elecon_segm[] = {_SGM_SPACE, _SGM_E, _SGM_LL, _SGM_E, _SGM_K, _SGM_O, _SGM_H, _SGM_SPACE, _SGM_EOS};
const uint16_t PROGMEM test1_segm[] = {_SGM_SPACE, _SGM_SPACE, _SGM_A, _SGM_C, _SGM_PP,_SGM_T,_SGM_SPACE,_SGM_SPACE, _SGM_EOS};
void InitSegm()
{
	cur_segm = 0;
	SetSegmStr((uint16_t*)test1_segm, 0,0);
//	SetSegmSimb(pgm_read_word((uint16_t*)&elecon_segm[5]), 0, 0);
	SetSegmStr((uint16_t*)elecon_segm, 1,0);
//ClearSegmStrs(0);
//ClearSegmStrs(1);
}
 