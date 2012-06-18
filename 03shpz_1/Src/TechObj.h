#ifndef __TECHOBJ_H
	#define __TECHOBJ_H

	#include <avr/io.h>
	#include <avr/pgmspace.h>

    //template <int LED_NOMER>
	class TechObj
	{
		private:
			uint16_t t_stad;
			uint16_t t_sub_st;
		public:
			uint8_t stad;
			uint8_t sub_st;
			const prog_char *name;
			//uint8_t *out;//выбор выхода
			uint8_t f_m;
			uint8_t s_n;
			uint8_t cmd;
			uint8_t status;
			uint16_t enh_info;
			uint8_t *mn_os;
			virtual void drv();
			virtual void show_mnem();
			virtual void show_lcd();
			void inc_t_stad();
			uint16_t read_t_stad();
			void clear_t_stad();
			void inc_t_sub_st();
			uint16_t read_t_sub_st();
			void clear_t_sub_st();
			void to_stad(uint8_t _stad, uint8_t _sub_st);
			TechObj()
			{
				t_stad=0;
				t_sub_st=0;
				stad=0;
				sub_st=0;
				cmd=0;
				status=0;
				enh_info=0;
//				f_m=0;
				name=0;
				//out=0;
			}
	};

    class TDevObject
    {
        public:
            uint8_t stad;
            uint8_t stan;
            virtual void drv();
            virtual void show_mnem();
            virtual void show_lcd();
    };

	class Set
	{
		public:
			const prog_char *name;
			int16_t value;
			int16_t min_value;
			int16_t max_value;
			uint8_t dot;
	};
	#define SET_SET(_defset_name,_defset_name_lcd,_defset_value,_defset_min_value,\
					_defset_max_value,_defset_dot)\
					{_defset_name.name=_defset_name_lcd;_defset_name.value=_defset_value;\
					 _defset_name.min_value=_defset_min_value;\
					 _defset_name.max_value=_defset_max_value;_defset_name.dot=_defset_dot;}
#endif
