#ifndef __UART_H
	#define __UART_H

#include <avr/io.h>
//#define UART0_MASTER 0
#define UART1_MASTER 1
#define UART_RX_OK 0x01 //uart_status
#define UART_TX_OK 0x02 //uart_status

#define MAX_LENGTH_TX_BUFFER0 100//200
#define MAX_LENGTH_RX_BUFFER0 100//50
#define MAX_LENGTH_TX_BUFFER1 100//200
#define MAX_LENGTH_RX_BUFFER1 100//50

#include "Sgwork.h"
extern uint8_t Receive_buffer_uart0(uint8_t);
extern uint8_t Receive_buffer_uart1(uint8_t);
extern void Transmitt_buffer_uart0();
extern void Transmitt_buffer_uart1();
extern uint8_t rx_local_buffer0[];
extern uint8_t tx_local_buffer0[];
extern uint8_t rx_local_buffer1[];
extern uint8_t tx_local_buffer1[];
extern uint8_t hex_to_ASCII (uint8_t hex_to_ASCII_temp);
extern void uart_init0();
extern void uart_init1();
extern uint8_t uart_status0;
extern uint8_t uart_status1;

extern void set_uart0_to_transmitt();
extern void set_uart0_to_receive();
extern void set_uart1_to_transmitt();
extern void set_uart1_to_receive();
#endif
