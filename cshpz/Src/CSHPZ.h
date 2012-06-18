#ifndef __NET_SHPZ_C_H
	#define __NET_SHPZ_C_H

    #include <avr/pgmspace.h>

//    #define FLOOR_NUM_CENTER       2

    #include "Sgwork.h"
    #include "Nls.h"
    #include "DEVS.H"

//    extern const prog_char strKPD[] PROGMEM;
    extern const prog_char strKPD01[] PROGMEM;
    extern const prog_char strKPD02[] PROGMEM;
    extern const prog_char strKPD11[] PROGMEM;
    extern const prog_char strKPD12[] PROGMEM;
    extern const prog_char strPP001[] PROGMEM;
    extern const prog_char strPP01[] PROGMEM;
    extern const prog_char strZOV0[] PROGMEM;
    extern const prog_char strVZK0[] PROGMEM;
    extern const prog_char strPP1[] PROGMEM;
    extern const prog_char strZOV1[] PROGMEM;
    extern const prog_char strVZK1[] PROGMEM;

    extern TDevObject* pDevs_arr_Center[];
#endif
