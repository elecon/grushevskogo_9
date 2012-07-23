#include "Main.h"

//#define F_CPU 11059200UL
//тик системы 1.48(148) ms

//DefineProcess(TAnMeas, 50);
DefineProcess(TPeripheral, 150);//200
DefineProcess(TUART0, 150);//200
DefineProcess(TUART1, 150);//200
DefineProcess(TTechnolog, 150);//200


//TAnMeas AnMeas(pr0);
TUART0 UART0(pr1);
TUART1 UART1(pr0);
TPeripheral Peripheral(pr2);
TTechnolog Technolog(pr3);


//#if !UART0_MASTER
OS::TEventFlag efUART0;
//#endif

//#if !UART1_MASTER
OS::TEventFlag efUART1;
//#endif

//OS::TMutex Mutex1;

#define strMem

uint8_t tech_fl;
uint8_t uiUartErrCounter;
uint8_t ProcesFlag;
// Основной массив хранения 2-х строк экрана ЖКИ пульта
char LCD_str[40];//=  "                                        ";
//-----------------------------------------------------------------------------
extern uint8_t message_arch_byte[];
extern uint8_t message_arch_byte_cpy[];

#include "Etaz.h"

//MNEMO_OUTPUT_STRUCT mnemo[NUM_OF_MNEMO];


/*
NET_OUTPUT_STRUCT1 data_for_slave1;
NET_INPUT_STRUCT1 data_from_slave1;
*/
NET_OUTPUT_STRUCT1 data_from_slave02;
NET_INPUT_STRUCT1 data_for_slave02;

NET_OUTPUT_STRUCT1 data_from_slave3;
NET_INPUT_STRUCT1 data_for_slave3;

NET_OUTPUT_STRUCT1 data_from_slave6;
NET_INPUT_STRUCT1 data_for_slave6;

NET_OUTPUT_STRUCT1 data_from_slave9;
NET_INPUT_STRUCT1 data_for_slave9;

NET_OUTPUT_STRUCT1 data_from_slave11;
NET_INPUT_STRUCT1 data_for_slave11;

NET_OUTPUT_STRUCT1 data_from_slave14;
NET_INPUT_STRUCT1 data_for_slave14;

NET_OUTPUT_STRUCT1 data_from_slave16;
NET_INPUT_STRUCT1 data_for_slave16;

NET_OUTPUT_STRUCT1 data_from_slave18;
NET_INPUT_STRUCT1 data_for_slave18;

NET_OUTPUT_STRUCT1 data_from_slave20;
NET_INPUT_STRUCT1 data_for_slave20;

NET_OUTPUT_STRUCT1 data_from_slave21;
NET_INPUT_STRUCT1 data_for_slave21;

NET_OUTPUT_STRUCT2 data_for_slave2;
NET_INPUT_STRUCT2 data_from_slave2;
//NET_OUTPUT_STRUCT3 data_for_slave3;
//NET_INPUT_STRUCT3 data_from_slave3;

NET_BFPP_OUTPUT_STRUCT bfpp_out;
NET_BFPP_INPUT_STRUCT bfpp_in;

LCD_OUTPUT_STRUCT lcd_data;
LCD_INPUT_STRUCT key_data;

uint8_t NetPackInfo[NUM_OF_SCAF];

void start_init(void) __attribute__ ((naked)) __attribute__ ((section (".init5")));

void start_init(void) {
	#if (__AVR_ATmega128__)
		MCUCSR&=~0x1f;
	#endif
	#if (__AVR_ATmega1281__)
		MCUCR&=~0x1f;
	#endif
	#if (__AVR_ATmega128__)  //for MRTP_4
	DDRA = 0x00;
	DDRB = 0x00;
    DDRC = 0x03;
    DDRD = 0x00;
    DDRE = 0x10;
    DDRF = 0x00;
    DDRG = 0x00;
	PORTA = 0xff;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
	PORTF = 0x00;
	PORTG = 0x00;

	DDRD|=(1<<PD7)|(1<<PD6)|(1<<PD5)|(1<<PD4);
	DDRA=0xff;

	PORTD=0xff;
	PORTD&=~((1<<PD4)/*|(1<<PD6)*/);

	DDRC=(1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);
	PORTC|=(1<<PC3);
	DDRE&=~(1<<PE4);//живлення для регістрів ввода/вивода
	#endif

	#if (__AVR_ATmega1280__) //for MK_035
//	void start_init(void) __attribute__ ((naked)) __attribute__ ((section (".init5")));



	MCUCR|=0x80;
	DDRA = 0x00;
	DDRB = 0x80;
    DDRC = 0xff;
    DDRD = 0xf0;
    DDRE = 0xA0;
    DDRF = 0x00;
    DDRG = 0x2c;
	DDRH = 0x00;
	DDRL = 0xff;
	DDRJ = 0xfa;
	DDRK = 0xff;

	PORTA = 0xff;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
	PORTF = 0x00;
	//PORTG = 0x20;
	PORTH = 0x00;
	PORTL = 0x00;
	PORTJ = 0x00;
	PORTK = 0x00;

	//XMCRB = (1<<XMM1);

	PORTG|=_BV(PG4);
	PORTG&=~_BV(PG3);
	PORTG|=_BV(PG5);

	XMCRA |= _BV(SRE);

	uint8_t * xbss_clean;
    extern uint8_t __xbss_start, __xbss_end;
    for ( xbss_clean = &__xbss_start; xbss_clean < &__xbss_end; xbss_clean++) *xbss_clean = 0x00;

#endif

}

int main()
{
	uint8_t i,j;
	#if (__AVR_ATmega128__)
		message_arch_byte[0]=MCUCSR;
	#endif
	#if (__AVR_ATmega1281__||__AVR_ATmega1280__)
		message_arch_byte[0]=MCUCR;
	#endif

	message_arch_byte_cpy[0]=0xff;

	#if (__AVR_ATmega128__||__AVR_ATmega1281__)
		MCUCSR&=~0x1f;
		DDRA = 0xff;
        DDRB = 0x00;
        DDRC = 0x03;
        DDRD = 0x00;
        DDRE = 0x10;
        DDRF = 0x00;
        DDRG = 0x00;
        PORTA = 0xff;
        PORTB = 0x00;
        PORTC = 0x00;
        PORTD = 0x00;
        PORTE = 0x00;
        PORTF = 0x00;
        PORTG = 0x00;

        DDRD|=(1<<PD7)|(1<<PD6)|(1<<PD5)|(1<<PD4);
        //DDRA=0xff;

        PORTD=0xff;
        PORTD&=~((1<<PD4));//|(1<<PD6));

        DDRC=(1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);
        PORTC|=(1<<PC3);
	#endif
	#if (__AVR_ATmega1280__)
		MCUCR&=~0x80;
		DDRA = 0x00;
        DDRB = 0x80;
        DDRC = 0xff;
        DDRD = 0xf0;
        DDRE = 0xA0;
        DDRF = 0x00;
        DDRG = 0x2c;
        DDRH = 0x00;
        DDRL = 0xff;
        DDRJ = 0xfa;
        DDRK = 0xff;

        PORTA = 0xff;
        PORTB = 0x00;
        PORTC = 0x00;
        PORTD = 0x00;
        PORTE = 0x00;
        PORTF = 0x00;
        //PORTG = 0x20;
        PORTH = 0x00;
        PORTL = 0x00;
        PORTJ = 0x00;
        PORTK = 0x00;

        //XMCRB = (1<<XMM1);

        PORTG|=_BV(PG4);
        PORTG&=~_BV(PG3);
        PORTG|=_BV(PG5);

        XMCRA |= _BV(SRE);
//        uint8_t * xbss_clean;
//        //extern uint8_t __xbss_start, __xbss_end;
//        for ( xbss_clean = &__xbss_start; xbss_clean < &__xbss_end; xbss_clean++) *xbss_clean = 0x00;

	#endif


	//PORTC&=~_BV(PC1);

	//DDRE|=(1<<PE4);//живлення для регістрів ввода/вивода
	//PORTE&=~(1<<PE4);

	RAMPZ=0;


	KEY[0]=0x00;
	KEY[1]=0x00;



	lcd_data.head.size=sizeof(LCD_OUTPUT_STRUCT);
	lcd_data.head.adr=0x20;
	lcd_data.head.cmd='S';

	key_data.head.size=sizeof(LCD_INPUT_STRUCT);
	key_data.head.adr=0x20;
	key_data.head.cmd='d';

//////////////////////////////////////////////////////////////////////////////////////////////////////
//slaveN: N=NUM_OF_SCAF!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*
	data_for_slave1.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_for_slave1.head.adr=0x50;
	data_for_slave1.head.cmd='d';

	data_from_slave1.head.size=sizeof(NET_INPUT_STRUCT1);
	data_from_slave1.head.adr=0x50;
	data_from_slave1.head.cmd='d';
*/

    data_for_slave02.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave02.head.adr=0x57;
	data_for_slave02.head.cmd='d';

	data_from_slave02.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave02.head.adr=0x57;
	data_from_slave02.head.cmd='d';

	data_for_slave3.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave3.head.adr=0x57;
	data_for_slave3.head.cmd='d';

	data_from_slave3.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave3.head.adr=0x57;
	data_from_slave3.head.cmd='d';

	data_for_slave6.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave6.head.adr=0x58;
	data_for_slave6.head.cmd='d';

	data_from_slave6.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave6.head.adr=0x58;
	data_from_slave6.head.cmd='d';

	data_for_slave9.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave9.head.adr=0x59;
	data_for_slave9.head.cmd='d';

	data_from_slave9.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave9.head.adr=0x59;
	data_from_slave9.head.cmd='d';

    data_for_slave11.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave11.head.adr=0x56;
	data_for_slave11.head.cmd='d';

	data_from_slave11.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave11.head.adr=0x56;
	data_from_slave11.head.cmd='d';

	data_for_slave14.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave14.head.adr=0x5A;
	data_for_slave14.head.cmd='d';

	data_from_slave14.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave14.head.adr=0x5A;
	data_from_slave14.head.cmd='d';

	data_for_slave16.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave16.head.adr=0x50;
	data_for_slave16.head.cmd='d';

	data_from_slave16.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave16.head.adr=0x50;
	data_from_slave16.head.cmd='d';

	data_for_slave18.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave18.head.adr=0x51;
	data_for_slave18.head.cmd='d';

	data_from_slave18.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave18.head.adr=0x51;
	data_from_slave18.head.cmd='d';

	data_for_slave20.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave20.head.adr=0x52;
	data_for_slave20.head.cmd='d';

	data_from_slave20.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave20.head.adr=0x52;
	data_from_slave20.head.cmd='d';

    data_for_slave21.head.size=sizeof(NET_INPUT_STRUCT1);
	data_for_slave21.head.adr=0x53;
	data_for_slave21.head.cmd='d';

	data_from_slave21.head.size=sizeof(NET_OUTPUT_STRUCT1);
	data_from_slave21.head.adr=0x53;
	data_from_slave21.head.cmd='d';








	data_for_slave2.head.size=sizeof(NET_INPUT_STRUCT2);
	data_for_slave2.head.adr=0x51;
	data_for_slave2.head.cmd='d';

	data_from_slave2.head.size=sizeof(NET_OUTPUT_STRUCT2);
	data_from_slave2.head.adr=0x51;
	data_from_slave2.head.cmd='d';

	bfpp_in.head.size=sizeof(NET_BFPP_INPUT_STRUCT);
	bfpp_in.head.adr=0xb0;
	bfpp_in.head.cmd='d';

	bfpp_out.head.size=sizeof(NET_BFPP_OUTPUT_STRUCT);
	bfpp_out.head.adr=0xb0;
	bfpp_out.head.cmd='d';


/*
	data_for_slave3.head.size=sizeof(NET_OUTPUT_STRUCT3);
	data_for_slave3.head.adr=0x52;
	data_for_slave3.head.cmd='d';

	data_from_slave3.head.size=sizeof(NET_INPUT_STRUCT3);
	data_from_slave3.head.adr=0x52;
	data_from_slave3.head.cmd='d';
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////



	for(i=0;i<NUM_OF_MNEMO;i++)
	{
//		mnemo[i].head.size=sizeof(MNEMO_OUTPUT_STRUCT);
//		mnemo[i].head.adr=0x30+i;
//		mnemo[i].head.cmd='d';
	}
/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!колво строчек=колву мнемосхем!!!!!!!!!!!!!!!!!////////////////
	for(j=0;j<NUM_OF_MNEMO;j++) {
		for(i=0;i<80;i++) {
			//mnemo[j].rg_led[i+1]=0xff;
			LED_FIELD[i+80*j]=0xff;
		}
		//mnemo[j].rg_led[j]=0x00;
	}

	for (i=0;i<NUM_OF_SCAF;i++) {
        NetPackInfo[i]=0xff;
	}



	low_init();
	Init_iic();

	check_iic_status();
	Work_init();
	Dev_init();
//	Etaz_init();
	Menu_init();
	Pdz_init();
	Message_init();
    OS::Run();
}


//-----------------------------------------------------------------------------

#define AOUT	2	//portA OPEN/CLOSE output switcher
#define ADR0	4	//portA
#define ADR1	8	//portA
#define ADR2	16	//portA
/*
#if 0
uint8_t analog_address;
uint16_t AN_VALUE[8];
uint16_t PWM[8];
enum {STABILIZE_PWM,ADC_MEASURE};
uint8_t analog_mode;

void TAnMeas::Exec()
{
	TCCR1A = 0x23;
	TCCR1B = 0x01;
	PWM[0] = 0x20;
	OCR1B = PWM[0];
	PORTA&=~(ADR0|ADR1|ADR2);
	ADMUX = 0;
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS0);
	ADCSRA|=1<<ADSC;// start conversion
	while(ADCSRA&(1<<ADSC));// poll conversion
	AN_VALUE[0] = ADCW;
	analog_mode=STABILIZE_PWM;
    for(;;)
    {
		//OCR1B = PWM;
		//ADCSRA|=(1<<ADSC);// start conversion
		//while(ADCSRA&(1<<ADSC));// poll conversion
		//AN_VALUE = ADCW;
		switch(analog_mode)
		{
			case ADC_MEASURE:
				{
					PORTA|=AOUT;//enable analog output
					analog_mode = STABILIZE_PWM;
					break;
				}
			case STABILIZE_PWM:
				{
					ADCSRA|=(1<<ADSC);// start conversion
					while(ADCSRA&(1<<ADSC));// poll conversion
					AN_VALUE[analog_address] = ADCW;
					PORTA&=~AOUT;//disable analog output
					analog_address++;
					if(analog_address>7)
					{
				analog_address=0;
					}
					//decode analog adress
					if(analog_address&1) PORTA|=ADR0;
					else PORTA&=~ADR0;
					if(analog_address&2) PORTA|=ADR1;
					else PORTA&=~ADR1;
					if(analog_address&4) PORTA|=ADR2;
					else PORTA&=~ADR2;
					OCR1B = PWM[analog_address];
					analog_mode = ADC_MEASURE;
					break;
				}
		}
		Sleep(5);// 11 mc
    }
}
#endif
*/
//-----------------------------------------------------------------------------
#include <avr/delay.h>
//uint8_t NetPackInfo[NUM_OF_SCAF];//
uint8_t cur_net_pack;
uint8_t cur_address0;
uint8_t cur_address1;
uint8_t uiNetCounter;

void TUART0::Exec()
{
	UCSR0A=0x00;
	UCSR0B=(1<<RXCIE0)|(1<<RXEN0);
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
	UBRR0H=0;
	#if (__AVR_ATmega128__||__AVR_ATmega1281__)
		UBRR0L=11;
	#endif
	#if (__AVR_ATmega1280__)
		UBRR0L=15;
	#endif

	cur_net_pack=0;
	set_uart0_to_receive();

	for(;;)
    {
		//PORTC|=_BV(PC1);
//		#if !UART0_MASTER
		efUART0.Wait(40);
//		#endif

		if(uart_status0&UART_RX_OK)
		{
            uiNetCounter=0;
            NetPackInfo[cur_net_pack]=0;
			#if (__AVR_ATmega128__||__AVR_ATmega1281__)
                PORTC&=~_BV(PC1);			//Блималка при гарному пакеті
			#endif
			#if (__AVR_ATmega1280__)
                PORTK&=~_BV(PK4); //for MK_035
            #endif

			uart_status0&=~UART_RX_OK;
			switch(cur_net_pack)
			{

				case 0:
					memcpy((uint8_t*)&(data_from_slave02.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				case 1:
					memcpy((uint8_t*)&(data_from_slave3.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				case 2:
					memcpy((uint8_t*)&(data_from_slave6.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				case 3:
					memcpy((uint8_t*)&(data_from_slave9.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				case 4:
					memcpy((uint8_t*)&(data_from_slave11.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				case 5:
					memcpy((uint8_t*)&(data_from_slave14.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				case 6:
					memcpy((uint8_t*)&(data_from_slave16.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				case 7:
					memcpy((uint8_t*)&(data_from_slave18.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				case 8:
					memcpy((uint8_t*)&(data_from_slave20.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				case 9:
					memcpy((uint8_t*)&(data_from_slave21.devs_net_stat[0]),
					(uint8_t*)&rx_local_buffer0[3],
						sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
				break;
				default:
				break;
			}
//----------------------------------------------------------------------------
//			memcpy(	(uint8_t*)&(data_from_slave1.devs_net_stat[0]),
//					(uint8_t*)&rx_local_buffer0[3],
//					sizeof(NET_OUTPUT_STRUCT1)-sizeof(HEAD_NET_STRUCT));
//----------------------------------------------------------------------------
		}
		else {
		    #if (__AVR_ATmega128__||__AVR_ATmega1281__)
                PORTC|=_BV(PC1);
            #endif
            #if (__AVR_ATmega1280__)
                PORTK|=_BV(PK4); //for MK_035
            #endif

            if(NetPackInfo[cur_net_pack]<40) NetPackInfo[cur_net_pack]++;//

		}
        //cur_net_pack=7;
		if(cur_net_pack<NUM_OF_SCAF-1) cur_net_pack++; else cur_net_pack=0;

        uart_status0=0;
        uart_init0();
        set_uart0_to_receive();
//---------------------------------------------------------------------------------------
        switch(cur_net_pack)
		{
			case 0:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave02,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave02.head.adr;
			break;
			case 1:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave3,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave3.head.adr;
			break;
			case 2:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave6,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave6.head.adr;
			break;
			case 3:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave9,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave9.head.adr;
			break;
			case 4:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave11,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave11.head.adr;
			break;
			case 5:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave14,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave14.head.adr;
			break;
			case 6:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave16,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave16.head.adr;
			break;
			case 7:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave18,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave18.head.adr;
			break;
			case 8:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave20,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave20.head.adr;
			break;
			case 9:
				memcpy((uint8_t*)&tx_local_buffer0,
				(uint8_t*)&data_for_slave21,
				sizeof(NET_INPUT_STRUCT1));
				cur_address0=data_for_slave21.head.adr;
			break;
			default:
			break;
		}
        //Mutex1.Lock();
//            memcpy((uint8_t*)&tx_local_buffer0,
//            (uint8_t*)&data_for_slave1,
//            sizeof(NET_INPUT_STRUCT1));
//            cur_address0=data_for_slave1.head.adr;
        //Mutex1.Unlock();
//---------------------------------------------------------------------------------------

#if UART0_MASTER
			UCSR0B=(1<<TXEN0)|(1<<TXCIE0);   //разрешение передатчика
			set_uart0_to_transmitt();
			_delay_us(100);
			UDR0='#';
#else
            UCSR0B=(1<<RXEN0)|(1<<RXCIE0);
#endif
		//Sleep(10);//7//10.37ms      //BULO 50
    }
}
extern void set_uart1_transmitt();
extern uint8_t tx_local_buffer1[MAX_LENGTH_TX_BUFFER1];
extern uint8_t rx_local_buffer1[MAX_LENGTH_TX_BUFFER1];
extern uint8_t mnemo_test_counter;
extern uint8_t LCD_light;
uint8_t color,tmp_counter,loop_counter;
uint8_t mnemo_counter;
uint8_t Uart1Counter;
uint8_t NetPackInfo2[10];
uint8_t Shota;

void TUART1::Exec()
{
	UCSR1A=0x00;
	UCSR1B=(1<<RXCIE1)|(1<<RXEN1);
	UCSR1C=(1<<UCSZ11)|(1<<UCSZ10);
	UBRR1H=0;
	#if (__AVR_ATmega128__||__AVR_ATmega1281__)
		UBRR1L=11;
	#endif
	#if (__AVR_ATmega1280__)
		UBRR1L=15;
	#endif
	set_uart1_to_receive();
	Uart1Counter=0;

	for(;;)
    {
		//#if !UART1_MASTER
		if (Uart1Counter==2) {
			efUART1.Wait(40);//200
		}
		else {
			efUART1.Wait(20);//200
		}
		//#endif
		if (Uart1Counter==0) {
			if (uart_status1&UART_TX_OK) Shota|=UART_TX_OK; else Shota&=~UART_TX_OK;
			if (uart_status1&UART_RX_OK) Shota|=UART_RX_OK; else Shota&=~UART_RX_OK;
		}
		//if (uart_status1&UART_TX_OK) {
		//	uart_status1&=~UART_TX_OK;

			if(uart_status1&UART_RX_OK)
			{
				uart_status1&=~UART_RX_OK;
				NetPackInfo2[Uart1Counter+ZSUV]=0x00;//
				switch(Uart1Counter)
				{
					case 0://типа shafa
					{
						memcpy(	(uint8_t*)&(data_for_slave2.devs_net_stat[0]),
								(uint8_t*)&rx_local_buffer1[3],
								sizeof(NET_INPUT_STRUCT2)-sizeof(HEAD_NET_STRUCT));
					//}
					break;
					}

					case 1://типа кнопки
					{
						memcpy(	(uint8_t*)&(key_data.key[0]),
								(uint8_t*)&rx_local_buffer1[3],
								sizeof(LCD_INPUT_STRUCT)-sizeof(HEAD_NET_STRUCT));
                        ProcesFlag|=0x01;

					break;
					}

					case 2:{ //типа мнемосхема

					}
					break;
				}
			}
			else {
				//if (uart_status1&UART_TX_OK) {
				//	uart_status1&=~UART_TX_OK;
					if(NetPackInfo2[Uart1Counter+ZSUV]<12) NetPackInfo2[Uart1Counter+ZSUV]++;
				//}
				//if(NetPackInfo2[Uart1Counter]<12) NetPackInfo2[Uart1Counter]++;
			}
		//}

		//Uart1Counter=0;
		if (Uart1Counter<2)
			Uart1Counter++;
		else Uart1Counter=0;

		//mnemo_counter++;
		if (Uart1Counter==2) mnemo_counter++;
		//if (mnemo_counter>=3) mnemo_counter=0;
		//mnemo_counter=0;
		if (mnemo_counter>=NUM_OF_MNEMO) mnemo_counter=0;

		//if ((NetPackInfo2[0+ZSUV])) PORTC|=_BV(PC1);	else PORTC&=~_BV(PC1);
		switch(Uart1Counter)
		{
			case 0: {
				memcpy(	(uint8_t*)&tx_local_buffer1,
						(uint8_t*)&data_from_slave2,
						sizeof(NET_OUTPUT_STRUCT2));
						cur_address1=0x51;
				//cur_address1=data_from_slave1.head.adr;
			}
			break;

			case 1: {
				if(tech_fl&SOUND)
				{
					lcd_data.out_lcd[0]=0x00;
					lcd_data.out_lcd[1]=0x44;
				}
				else {
					if(!LCD_light)
					{
						if (tech_fl&SOUND_KEY){
							lcd_data.out_lcd[0]='1';
							lcd_data.out_lcd[1]='4';
							tech_fl&=~SOUND_KEY;
						}
						else {
							lcd_data.out_lcd[0]='0';
							lcd_data.out_lcd[1]='0';
						}
					}
					else
					{
						if (tech_fl&SOUND_KEY){
							lcd_data.out_lcd[0]='1';//31
							lcd_data.out_lcd[1]='D';//44
							tech_fl&=~SOUND_KEY;
						}
						else {
							lcd_data.out_lcd[0]='0';
							lcd_data.out_lcd[1]='8';
						}

					}
				}
				memcpy((uint8_t*)&lcd_data.out_lcd[2],(uint8_t*)&LCD_str[0],20);//16 //bulo 20
				lcd_data.out_lcd[22]='\\';//18     //bulo  22
				lcd_data.out_lcd[23]='n';//19		//bulo  23
				memcpy((uint8_t*)&lcd_data.out_lcd[24],(uint8_t*)&LCD_str[20],20);//20 16 16 	//bulo 24 20 20
				memcpy((uint8_t*)&tx_local_buffer1,(uint8_t*)&lcd_data,sizeof(LCD_OUTPUT_STRUCT));
				cur_address1=0x20;
			}
			break;

			case 2: {  //(-1|-5)
				if(mnemo_counter<(NUM_OF_MNEMO)) {
					if(scafe_fl&MNEMO_WRK)
					{
						color=0xff;
						if(scafe_fl&RED) color=0xf0;
						else if(scafe_fl&YELLOW) color=0x00;
						else if(scafe_fl&GREEN) color=0x0f;

						if(scafe_fl&FIELD)
						{
							for(tmp_counter=0;tmp_counter<80;tmp_counter++)
							{
								if(mnemo_test_counter==(mnemo_counter))
								{
									LED_FIELD[80*(mnemo_counter)+tmp_counter]=color;
								}
								else
								{
									LED_FIELD[80*(mnemo_counter)+tmp_counter]=0xff;
								}
							}
						}
						else
						{
							if(mnemo_test_counter==(mnemo_counter))
								if(!(scafe_fl&FREEZ)) loop_counter++;
							if(loop_counter>79) loop_counter=0;
							for(tmp_counter=0;tmp_counter<80;tmp_counter++)
							{
								if(tmp_counter==loop_counter)
									LED_FIELD[80*(mnemo_counter)+tmp_counter]=color;
								else
									LED_FIELD[80*(mnemo_counter)+tmp_counter]=0xff;
							}
						}
						tx_local_buffer1[0]=84;
						tx_local_buffer1[1]=0x30+mnemo_counter;
						tx_local_buffer1[2]='d';
						tx_local_buffer1[3]=0x00;
						memcpy((uint8_t*)&tx_local_buffer1[4],(uint8_t*)&LED_FIELD[80*(mnemo_counter)],80);
						//memcpy((uint8_t*)&tx_local_buffer1,(uint8_t*)&LED_FIELD[80*(mnemo_counter)],80);
					}
					else
					{
						//memcpy((uint8_t*)&mnemo[mnemo_counter].rg_led[1],
						//(uint8_t*)&LED_FIELD[80*(mnemo_counter)],80);
						tx_local_buffer1[0]=84;
						#ifdef DDEBUG
                            if (mnemo_counter<12) {
                                tx_local_buffer1[1]=0x30+(mnemo_counter+6);
                            }
                            else {
                                tx_local_buffer1[1]=0x30+(mnemo_counter-12);
                            }
                        #else
                            tx_local_buffer1[1]=0x30+mnemo_counter;
						#endif
						tx_local_buffer1[2]='d';
						tx_local_buffer1[3]=0x00;
						memcpy((uint8_t*)&tx_local_buffer1[4],(uint8_t*)&LED_FIELD[80*(mnemo_counter)],80);
					}
//					#ifdef DDEBUG
//                    if (mnemo_counter<12) {
//                        cur_address1=0x30+(mnemo_counter+6);
//                    }
//                    else {
//                        cur_address1=0x30+(mnemo_counter-12);
//                    }
//
//					#else
//					 if (mnemo_counter<12) {
//                        cur_address1=0x30+(mnemo_counter+6);
//                    }
//                    else {
//                        cur_address1=0x30+(mnemo_counter-12);
//                    }
//					//cur_address1=0x30+(mnemo_counter);
//					#endif
//					//mnemo_counter++;
				}
			}
			break;
		}
		uart_status1=0;
		uart_init1();
		set_uart1_to_receive();
#if UART1_MASTER
			UCSR1B=(1<<TXEN1)|(1<<TXCIE1);   //разрешение передатчика
			set_uart1_to_transmitt();
			_delay_us(100);
			UDR1='#';
#else
			UCSR1B=(1<<RXEN1)|(1<<RXCIE1);
#endif
//		Sleep(10);//70//10.37ms////bulo 25 26_11_08
    }
}
//-----------------------------------------------------------------------------
extern void low_drv();
extern uint8_t cur_msk_selector;
extern uint8_t MT[2];
void TPeripheral::Exec()
{
	cur_msk_selector=0;
	for(;;)
    {
		low_drv();
		Sleep(10);//10.37ms
    }
}

//-----------------------------------------------------------------------------
void inconv();void outconv();
uint8_t sec_tik;
uint8_t lcd_drv_counter;
uint8_t WaitWhenIronIsReady;
void TTechnolog::Exec()
{

	check_iic_status();
	Work_init();
	Dev_init();
//	Reg_init();
	Menu_init();
//	Meas_init();
//	Cond_init();
	Message_init();

	WaitWhenIronIsReady=5;
	for(;;)
    {
		if(tech_fl&NO_IIC) tech_fl|=IIC_BUSY;
		else tech_fl&=~IIC_BUSY;
		if(/*(!(OS::GetTickCount()))&&*/(!(OS::GetTick200ms())) && (!(OS::GetTick1s()))) sec_tik=0;
		else sec_tik=0xff;
		outconv();
		if(!WaitWhenIronIsReady)
		{
			Pdz_drv();
//			Etaz_drv();
			Work_drv();
			Dev_drv();
			Message_drv();
		}
		else if(!sec_tik) WaitWhenIronIsReady--;
		all_ind();

//		if(lcd_drv_counter) lcd_drv_counter--;
//		else lcd_drv_counter=5;
//		if(!lcd_drv_counter)
        //low_drv();
        //Mutex1.Lock();
            Menu_drv();
        //Mutex1.Unlock();
        ProcesFlag&=~0x01;
		inconv();
		Sleep(27);//9
    }
}
//-----------------------------------------------------------------------------
//UART0 зовнішній
//UART1 внутрішній
uint8_t zaderjka_uarta;
//void perevid() {
//	if (cur_address0==0x51) {
//		uart_init1();
//		set_uart1_to_receive();
//		UCSR1B=(1<<RXEN1)|(1<<RXCIE1);
//	}
//}

OS_INTERRUPT void Uart0Rx_ISR()
{
	OS_ISR_ENTER();
	_CLI();
	uint8_t ret_val;

	ret_val=Receive_buffer_uart0(cur_address0);
	switch(ret_val)
	{
		case 2:
		{
			UCSR0B=0;
			//#if !UART0_MASTER
			efUART0.Signal();
			//#endif
			break;
		}
		case 3:
		{
			uart_status0|=UART_RX_OK;
			uart_init0();
			//efUART0.Signal();
			break;
		}
	}
	OS_ISR_EXIT();
}
OS_INTERRUPT void Uart0Tx_ISR()
{
	OS_ISR_ENTER();
	_CLI();

	Transmitt_buffer_uart0();
	//if (UCSR0A&((1<<DOR0)|(1<<FE0)|(1<<UPE0))) uiUartErrCounter++;
	#if !UART0_MASTER
	if(uart_status0&UART_TX_OK)
	{
		efUART0.Signal();
	}
	#endif
	OS_ISR_EXIT();
}
//-----------------------------------------------------------------------------
//UART0 зовнішній
//UART1 внутрішній
OS_INTERRUPT void Uart1Rx_ISR()
{
	OS_ISR_ENTER();
	_CLI();
	uint8_t ret_val;

	ret_val=Receive_buffer_uart1(cur_address1);
	switch(ret_val)
	{
		case 2:
		{
			UCSR1B=0;
//			#if !UART1_MASTER
				efUART1.Signal();
//			#endif
			break;
		}
		case 3:
		{

			uart_status1|=UART_RX_OK;
			uart_init1();
			#if UART1_MASTER
			//	efUART1.Signal();
			#endif

			#if !UART1_MASTER
				UCSR1B=(1<<TXEN1)|(1<<TXCIE1);   //разрешение передатчика
				set_uart1_to_transmitt();
				UDR1='!';
			#endif
			break;
		}
	}
	OS_ISR_EXIT();
}

//void set_uart1_receive();
OS_INTERRUPT void Uart1Tx_ISR()
{
	OS_ISR_ENTER();
	_CLI();
	Transmitt_buffer_uart1();

	#if !UART1_MASTER
	if(uart_status1&UART_TX_OK)
	{
		efUART1.Signal();
	}
	#endif
	OS_ISR_EXIT();
}

extern uint8_t MSK[8],OS_MT[2],MT[2];
uint8_t MSK_FIELD[64],OS_FIELD[36],OUT_FIELD[36],LED_FIELD[NUM_OF_MNEMO*80];
//uint8_t Test_MSK,TestMSKResult;
void outconv()
{
//	uint8_t i,j;
//	for(i=0;i<4;i++)
//	{
//		for(j=0;j<8;j++)
//		{
//			MSK_FIELD[0][i*8+j+1]=MSK[7-i]&(1<<j);
//			MSK_FIELD[1][i*8+j+1]=MSK[3-i]&(1<<j);
//		}
//	}
    uint8_t i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			//if(MSK[i]&(1<<j)) MSK_FIELD[i*8+j]=0xff;
			//else MSK_FIELD[i*8+j]=0x00;
			MSK_FIELD[i*8+j]=MSK[i]&(1<<j);
		}
	}

	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			OS_FIELD[i*8+j]=OS_MT[i]&(1<<j);
		}
	}
}
void inconv()
{
	uint8_t i,j;
	for(i=0;i<2;i++)
	{
		for(j=0;j<8;j++)
		{
			if(OUT_FIELD[i*8+j]) MT[i]|=(1<<j);
			else MT[i]&=~(1<<j);
		}
	}
}
