#ifndef __DEVKOG_H
	#define __DEVKOG_H

	#include "DEVS.H"
    #include "Nls.h"

	enum {KOG_C_CLOSE,KOG_C_OPEN};
	enum {KOG_ST_CLOSE,KOG_ST_OPEN};

	//����� enh_info
	#define KOG_CHECK_PRESS	0x8000 //�������� �������� ��������
	#define KOG_CHECK_MP	0x4000 //�������� ��������� ���������� ���������
	#define KOG_CHECK_KTR	0x2000 //�������� ��������� ��������� ����
	#define KOG_CHECK_OS	0x1000 //�������� �������� �����
	#define KOG_OPER		0x0200 //���������� ����������� ����������
	#define KOG_DIST		0x0100 //���������� ����������� ������������
	#define KOG_PRESS_ERROR	0x0080 //������ �������� ��������
	#define KOG_MP_ERROR	0x0040 //������ ���������� ���������
	#define KOG_KTR_ERROR	0x0020 //������ ��������� ����
	#define KOG_OS_ERROR	0x0010 //������ �������� �����

	class KOG: public TDevObject
	{
		public:
			uint8_t *out;//����� ������
			uint8_t *k_press;
			uint8_t *os;//��������� �� ���� �������� �����
			uint8_t *k_mp;
			uint8_t *k_ktr;
			uint16_t t_wait_press;
			uint16_t t_wait_press_counter;
			uint16_t t_wait_mp;
			uint16_t t_wait_mp_counter;
			void drv();
			void show_mnem();
			void show_lcd();
			void check_press();
			void check_mp();
			void check_ktr();
			void check_os();
			void auto_open();
			void auto_close();
			KOG();
			KOG(	const prog_char* _name,
					uint8_t* _mn_os,
					uint16_t enh_info,
					uint8_t* _out,
					uint8_t* _press,
					uint8_t* _os,
					uint8_t* _mp,
					uint8_t* _ktr);
	};

#endif
