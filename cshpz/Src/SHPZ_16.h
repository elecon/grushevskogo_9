#ifndef __NET_SHPZ_16_H
	#define __NET_SHPZ_16_H

    #include <avr/pgmspace.h>

    #define FLOOR_NUM_16       2

    #include "Sgwork.h"
    #include "Nls.h"
    #include "DEVS.H"

    extern const prog_char strKPD161[] PROGMEM;
//    const prog_char strKPD181[] PROGMEM = "���181";
    extern const prog_char strKPD162[] PROGMEM;
//    const prog_char strKPD182[]="���182";
    extern const prog_char strKPD171[] PROGMEM;
//    const prog_char strKPD191[]="���191";
    extern const prog_char strKPD172[] PROGMEM;
//    const prog_char strKPD192[]="���192";
    extern const prog_char strPP216[] PROGMEM;
//    const prog_char strPP218[]="��218";
    extern const prog_char strPP217[] PROGMEM;
//    const prog_char strPP219[]="��219";
    extern const prog_char strZOV16[] PROGMEM;
//    const prog_char strZOV18[]="���18";
    extern const prog_char strZOV17[] PROGMEM;
//    const prog_char strZOV19[]="���19";
    extern const prog_char strDVR16[] PROGMEM;
//    const prog_char strDVR[]="���";
    extern const prog_char strVZK161[] PROGMEM;
    extern const prog_char strVZK162[] PROGMEM;
    extern const prog_char strVZK163[] PROGMEM;
    extern const prog_char strVZK171[] PROGMEM;
    extern const prog_char strVZK172[] PROGMEM;
    extern const prog_char strVZK173[] PROGMEM;

    extern TDevObject* pDevs_arr_16[];


#endif
