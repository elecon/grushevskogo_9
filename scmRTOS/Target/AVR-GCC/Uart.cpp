#include "Uart.h"
#include <avr/io.h>
uint8_t rx_local_buffer0[MAX_LENGTH_RX_BUFFER0];
uint8_t tx_local_buffer0[MAX_LENGTH_TX_BUFFER0];

uint8_t rx_local_buffer1[MAX_LENGTH_RX_BUFFER1];
uint8_t tx_local_buffer1[MAX_LENGTH_TX_BUFFER1];

uint8_t uart_status0;
uint8_t uart_status1;

uint8_t hex_to_ASCII (uint8_t hex_to_ASCII_temp)
{    
    hex_to_ASCII_temp&=0x0F;
    if(hex_to_ASCII_temp>9)
	{
		hex_to_ASCII_temp+=7; //определение ASCII кода hex числа 9=39 A=41
	}
    return hex_to_ASCII_temp+=0x30;
}
                          //rx_data             USART_data
uint8_t ASCII_to_hex (uint8_t ASCII_to_hex_temp1, uint8_t ASCII_to_hex_temp2)
{    
    ASCII_to_hex_temp1-=0x30;
    if(ASCII_to_hex_temp1>9)
	{
		ASCII_to_hex_temp1-=7;
	}	
    ASCII_to_hex_temp2-=0x30;
    if(ASCII_to_hex_temp2>9)
	{
		ASCII_to_hex_temp2-=7;
	}
    return ((ASCII_to_hex_temp1<<4)&0xF0)+(ASCII_to_hex_temp2&0x0F);
}


void set_uart0_to_transmitt()
{
	PORTC&=~(1<<PC0);
//	PORTC|=(1<<PC0);
}
void set_uart0_to_receive()
{
	PORTC|=(1<<PC0);
//	PORTC&=~(1<<PC0);
}
void set_uart1_to_transmitt()
{
	PORTC|=(1<<PC3);
	PORTC&=~(1<<PC2);
}
void set_uart1_to_receive()
{
	PORTC|=(1<<PC2);
	PORTC&=~(1<<PC3);
}

//фунции инициализации, передачи, приема уарта0
uint8_t uart_switcher0;
uint8_t uart_checksum0;
uint8_t uart_flags0;
uint8_t uart_counter0;

#define split	1
#define string	2
void uart_init0(void)
{
	uart_switcher0=0;
	uart_checksum0=0;
	uart_flags0=0;
	uart_counter0=0;
}
void Transmitt_buffer_uart0()
{
	uint8_t temp;
	switch(uart_switcher0)
	{
		case 0: //transmitt adr
		{
			temp=tx_local_buffer0[1];
			if(uart_flags0&split)
			{
				temp=hex_to_ASCII(temp);
				uart_flags0&=~split;
				uart_checksum0+=temp;
				uart_switcher0=1;
				UDR0 = temp;
			}
			else
			{
				temp=hex_to_ASCII(temp>>4);
				uart_flags0|=split;
				uart_checksum0=temp;
				UDR0 = temp;
			}
			break;
		}
		case 1: //transmitt cmd
		{
			temp=tx_local_buffer0[2];
			if(temp<0x60)
			{
				uart_flags0|=string;
			}
			uart_checksum0+=temp;
			uart_counter0=3;
			uart_switcher0=2;
			if(uart_counter0==tx_local_buffer0[0])
				{
					uart_switcher0=3;
				}
			UDR0 = temp;
			break;
		}
		case 2: //transmitt to end of buffer
		{
			temp=tx_local_buffer0[uart_counter0];
			if(uart_flags0&string)
			{
				uart_checksum0+=temp;
				uart_counter0++;
				if(uart_counter0==tx_local_buffer0[0])
				{
					uart_switcher0=3;
				}
				UDR0 = temp;
			}
			else//not string
			{
				if(uart_flags0&split)
				{
					temp=hex_to_ASCII(temp);
					uart_flags0&=~split;
					uart_checksum0+=tx_local_buffer0[uart_counter0];
					uart_counter0++;
					if(uart_counter0==tx_local_buffer0[0])
					{
						uart_switcher0=3;
					}
					UDR0 = temp;
				}
				else
				{
					temp=hex_to_ASCII(temp>>4);
					uart_flags0|=split;
					UDR0 = temp;
				}
			}
			break;
		}
		case 3:// transmitt 'k'
		{
			uart_switcher0=4;
			UDR0 = 'k';
			break;
		}
		case 4:
		{
			if(uart_flags0&split)
			{
				temp=hex_to_ASCII(uart_checksum0);
				uart_flags0&=~split;
				uart_switcher0=5;
				UDR0 = temp;
			}
			else
			{
				temp=hex_to_ASCII(uart_checksum0>>4);
				uart_flags0|=split;
				UDR0 = temp;
			}
			break;
		}
		case 5:// transmitt 0x0d
		{
			uart_switcher0=6;
			UDR0 = 0x0d;
			break;
		}
		case 6:
		{
			uart_switcher0=0;
			set_uart0_to_receive();
			UCSR0B&=~((1<<TXEN0)|(1<<TXCIE0));
#if UART0_MASTER
			UCSR0B=(1<<RXEN0)|(1<<RXCIE0);			
#else
			uart_status0|=UART_TX_OK;
#endif
			break;
		}
	}//tr_uart_switcher
}

uint8_t rx_uart_old_value0;
//return_value
/*
	0 - ожидание ! или #
	1 - идет процесс приема пакета
	2 - ошибка приема
	3 - прием закончен нормально
*/
uint8_t return_value0;
uint8_t Receive_buffer_uart0(uint8_t adr)
{
	uint8_t temp,UDR_temp;
	UDR_temp=UDR0;
	switch(uart_switcher0)
	{
		case 0:// receive # or !
		{
#if UART0_MASTER
			if(UDR_temp=='!')
			{
				uart_switcher0=1;
				return_value0=1;
			}
			
#else
			if(UDR_temp=='#')
			{
				uart_switcher0=1;
				return_value0=1;
			}
#endif
			else
			return_value0=0;
			break;
		}
		case 1: //receive adr
		{
			if(uart_flags0&split)
			{
				temp=ASCII_to_hex(rx_uart_old_value0,UDR_temp);
				if(temp==adr)
				{
					uart_flags0&=~split;
					uart_checksum0+=UDR_temp;
					*(rx_local_buffer0+1)=temp;
					uart_switcher0=2;
				}
				else
				{
					return_value0=2;
				}
			}
			else
			{
				rx_uart_old_value0=UDR_temp;
				uart_flags0|=split;
				uart_checksum0=UDR_temp;
			}
			break;
		}
		case 2: //receive cmd
		{
			if(UDR_temp<0x60)
			{
				uart_flags0|=string;
			}
			else
			{
				uart_flags0&=~string;
			}
			uart_checksum0+=UDR_temp;
			*(rx_local_buffer0+2)=UDR_temp;
			uart_counter0=2;//num+adr+cmd
			uart_switcher0=3;
			break;
		}
		case 3: //receive to 0x0d
		{
			if(uart_flags0&string)
			{
				if(UDR_temp==0x0d)
				{
					uart_checksum0-=*(rx_local_buffer0+uart_counter0);// отмотка CRC2
					uart_checksum0-=*(rx_local_buffer0+uart_counter0-1);// отмотка CRC1
					uart_checksum0-=*(rx_local_buffer0+uart_counter0-2);// отмотка k
					temp=*(rx_local_buffer0+uart_counter0-2);
					if(!((temp=='k')||(temp=='K'))) //no k or K before checksum
					{
						return_value0=2;
					}
					else
					{
						if(uart_checksum0==ASCII_to_hex(*(rx_local_buffer0+uart_counter0-1),
							*(rx_local_buffer0+uart_counter0)))
						{
							*rx_local_buffer0=uart_counter0-3;
							return_value0=3; //end of receiving
						}
						else
						{
							return_value0=2;
						}
					}
				}			
				else
				{
					uart_checksum0+=UDR_temp;
					uart_counter0++;
					*(rx_local_buffer0+uart_counter0)=UDR_temp;
				}
			}
			else//not string
			{
				if((UDR_temp=='k')||(UDR_temp=='K'))
				{
					uart_switcher0=4;
				}
				if(uart_flags0&split)
				{
					temp=ASCII_to_hex(rx_uart_old_value0,UDR_temp);
					uart_flags0&=~split;
					uart_checksum0+=temp;
					uart_counter0++;							
					*(rx_local_buffer0+uart_counter0)=temp;
				}
				else
				{
					rx_uart_old_value0=UDR_temp;
					uart_flags0|=split;
				}
			}
			break;
		}
		case 4:// receive CRC1
		{
			rx_uart_old_value0=UDR_temp;
			uart_switcher0=5;
			break;
		}
		case 5:// receive CRC2
		{
			if(uart_checksum0==ASCII_to_hex(rx_uart_old_value0,UDR_temp))
			{
				uart_switcher0=6;
			}
			else
			{
				return_value0=2;
			}
			break;
		}
		case 6:
		{
			if(UDR_temp==0x0d)
			{
				*(rx_local_buffer0) = uart_counter0+1;
				return_value0=3; // end of receiving
			}
			else
			{
				return_value0=2;
			}
			break;
		}
	}//rx_uart_switcher
	return return_value0;
}
uint8_t uart_switcher1;
uint8_t uart_checksum1;
uint8_t uart_flags1;
uint8_t uart_counter1;

void uart_init1(void)
{
	uart_switcher1=0;
	uart_checksum1=0;
	uart_flags1=0;
	uart_counter1=0;
}
void Transmitt_buffer_uart1()
{
	uint8_t temp;
	switch(uart_switcher1)
	{
		case 0: //transmitt adr
		{
			temp=tx_local_buffer1[1];
			if(uart_flags1&split)
			{
				temp=hex_to_ASCII(temp);
				uart_flags1&=~split;
				uart_checksum1+=temp;
				uart_switcher1=1;
				UDR1 = temp;
			}
			else
			{
				temp=hex_to_ASCII(temp>>4);
				uart_flags1|=split;
				uart_checksum1=temp;
				UDR1 = temp;
			}
			break;
		}
		case 1: //transmitt cmd
		{
			temp=tx_local_buffer1[2];
			if(temp<0x60)
			{
				uart_flags1|=string;
			}
			uart_checksum1+=temp;
			uart_counter1=3;
			uart_switcher1=2;
			if(uart_counter1==tx_local_buffer1[0])
				{
					uart_switcher1=3;
				}
			UDR1 = temp;
			break;
		}
		case 2: //transmitt to end of buffer
		{
			temp=tx_local_buffer1[uart_counter1];
			if(uart_flags1&string)
			{
				uart_checksum1+=temp;
				uart_counter1++;
				if(uart_counter1==tx_local_buffer1[0])
				{
					uart_switcher1=3;
				}
				UDR1 = temp;
			}
			else//not string
			{
				if(uart_flags1&split)
				{
					temp=hex_to_ASCII(temp);
					uart_flags1&=~split;
					uart_checksum1+=tx_local_buffer1[uart_counter1];
					uart_counter1++;
					if(uart_counter1==tx_local_buffer1[0])
					{
						uart_switcher1=3;
					}
					UDR1 = temp;
				}
				else
				{
					temp=hex_to_ASCII(temp>>4);
					uart_flags1|=split;
					UDR1 = temp;
				}
			}
			break;
		}
		case 3:// transmitt 'k'
		{
			uart_switcher1=4;
			UDR1 = 'k';
			break;
		}
		case 4:
		{
			if(uart_flags1&split)
			{
				temp=hex_to_ASCII(uart_checksum1);
				uart_flags1&=~split;
				uart_switcher1=5;
				UDR1 = temp;
			}
			else
			{
				temp=hex_to_ASCII(uart_checksum1>>4);
				uart_flags1|=split;
				UDR1 = temp;
			}
			break;
		}
		case 5:// transmitt 0x0d
		{
			uart_switcher1=6;
			UDR1 = 0x0d;
			break;
		}
		case 6:
		{
			uart_switcher1=0;
			set_uart1_to_receive();
			UCSR1B&=~((1<<TXEN1)|(1<<TXCIE1));
#if UART1_MASTER
			UCSR1B=(1<<RXEN1)|(1<<RXCIE1);
#else
			uart_status1|=UART_TX_OK;
#endif
			break;
		}
	}//tr_uart_switcher
}

uint8_t rx_uart_old_value1;
//return_value
/*
	0 - ожидание ! или #
	1 - идет процесс приема пакета
	2 - ошибка приема
	3 - прием закончен нормально
*/

extern uint8_t MT[2];
uint8_t return_value1;
uint8_t FOR_ME_SUMMA,FOR_ME_SUMMA2,FOR_ME_SUMMA3;
extern uint8_t Uart1Counter;
uint8_t Receive_buffer_uart1(uint8_t adr)
{
	uint8_t temp,UDR_temp;
	UDR_temp=UDR1;
	switch(uart_switcher1)
	{
		case 0:// receive # or !
		{
#if UART1_MASTER
			if(UDR_temp=='!')
			{
				uart_switcher1=1;
				return_value1=1;
			}
			
#else
			if(UDR_temp=='#')
			{
				uart_switcher1=1;
				return_value1=1;
			}
#endif
			else
			return_value1=0;
			break;
		}
		case 1: //receive adr
		{
			if(uart_flags1&split)
			{
				temp=ASCII_to_hex(rx_uart_old_value1,UDR_temp);
				if(temp==adr)
				{
					uart_flags1&=~split;
					uart_checksum1+=UDR_temp;
					*(rx_local_buffer1+1)=temp;
					uart_switcher1=2;
				}
				else
				{
					return_value1=2;
				}
			}
			else
			{
				rx_uart_old_value1=UDR_temp;
				uart_flags1|=split;
				uart_checksum1=UDR_temp;
			}
			break;
		}
		case 2: //receive cmd
		{
			if(UDR_temp<0x60)
			{
				uart_flags1|=string;
			}
			else
			{
				uart_flags1&=~string;
			}
			uart_checksum1+=UDR_temp;
			*(rx_local_buffer1+2)=UDR_temp;
			uart_counter1=2;//num+adr+cmd
			uart_switcher1=3;
			break;
		}
		case 3: //receive to 0x0d
		{
			if(uart_flags1&string)
			{
				if(UDR_temp==0x0d)
				{
					uart_checksum1-=*(rx_local_buffer1+uart_counter1);// отмотка CRC2
					uart_checksum1-=*(rx_local_buffer1+uart_counter1-1);// отмотка CRC1
					uart_checksum1-=*(rx_local_buffer1+uart_counter1-2);// отмотка k
					temp=*(rx_local_buffer1+uart_counter1-2);
					if(!((temp=='k')||(temp=='K'))) //no k or K before checksum
					{
						return_value1=2;
					}
					else
					{
						if(uart_checksum1==ASCII_to_hex(*(rx_local_buffer1+uart_counter1-1),
							*(rx_local_buffer1+uart_counter1)))
						{
							*rx_local_buffer1=uart_counter1-3;
							return_value1=3; //end of receiving
						}
						else
						{
							return_value1=2;
						}
					}
				}			
				else
				{
					uart_checksum1+=UDR_temp;
					uart_counter1++;
					*(rx_local_buffer1+uart_counter1)=UDR_temp;
				}
			}
			else//not string
			{
				if((UDR_temp=='k')||(UDR_temp=='K'))
				{
					uart_switcher1=4;
				}
				if(uart_flags1&split)
				{
					temp=ASCII_to_hex(rx_uart_old_value1,UDR_temp);
					uart_flags1&=~split;
					uart_checksum1+=temp;
					uart_counter1++;							
					*(rx_local_buffer1+uart_counter1)=temp;
				}
				else
				{
					rx_uart_old_value1=UDR_temp;
					uart_flags1|=split;
				}
			}
			break;
		}
		case 4:// receive CRC1
		{
			rx_uart_old_value1=UDR_temp;
			uart_switcher1=5;
			break;
		}
		case 5:// receive CRC2
		{
			if (!Uart1Counter) {
				FOR_ME_SUMMA = uart_checksum1;
				//FOR_ME_SUMMA2 = ASCII_to_hex(rx_uart_old_value1,UDR_temp);
			}
			if(uart_checksum1==ASCII_to_hex(rx_uart_old_value1,UDR_temp))
			{
				uart_switcher1=6;
			}
			else
			{
				return_value1=2;
			}
			break;
		}
		case 6:
		{
			if(UDR_temp==0x0d)
			{
				*(rx_local_buffer1) = uart_counter1+1;
				return_value1=3; // end of receiving
			}
			else
			{
				return_value1=2;
			}
			break;
		}
	}//rx_uart_switcher
	return return_value1;
}