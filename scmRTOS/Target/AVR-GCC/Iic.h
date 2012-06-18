#ifndef __IIC_H
	#define __IIC_H
	
	#include <avr/io.h>
	
	#define SDA 0 //portD
	#define SCL 1 //portD
	extern void Init_iic();
	extern void Start_iic();
	extern void Stop_iic();
	extern uint8_t Tr_iic_byte(uint8_t);
	extern uint8_t Rd_iic_byte(uint8_t);

	extern void WriteSetIIC(uint16_t _value, uint16_t _adr);
	extern uint16_t ReadSetIIC(uint16_t _adr);

#endif
