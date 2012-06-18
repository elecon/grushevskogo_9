#include "TechObj.h"

void TechObj::inc_t_stad()
{
	if(t_stad<60000) t_stad++;
}
uint16_t TechObj::read_t_stad()
{
	return t_stad;
}
void TechObj::clear_t_stad()
{
	t_stad=0;
}
void TechObj::inc_t_sub_st()
{
	if(t_sub_st<60000) t_sub_st++;
}
uint16_t TechObj::read_t_sub_st()
{
	return t_sub_st;
}
void TechObj::clear_t_sub_st()
{
	t_sub_st=0;
}
void TechObj::to_stad(uint8_t _stad, uint8_t _sub_st)
{
	if(stad != _stad)
	{
		t_stad=0;
		t_sub_st=0;
		stad = _stad;
		sub_st = 0;
	}

	if(sub_st != _sub_st)
    {
		t_sub_st=0;
		sub_st = _sub_st;
    }
}
/*
TechObj::TechObj()
{
	t_stad=0;
	t_sub_st=0;
	stad=0;
	sub_st=0;
	cmd=0;
	status=0;
	enh_info=0;
	name=0;
}
*/
