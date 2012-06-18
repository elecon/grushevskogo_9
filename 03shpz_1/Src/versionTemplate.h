#ifndef VERSION_H
#define	VERSION_H

// Î ןנמדנאללו
extern const prog_char szVersion[] PROGMEM;
const prog_char szVersion[]  = "1.0";

extern const prog_char szBuild[] PROGMEM;
const prog_char szBuild[]  = "v$WCREV$";

extern const prog_char szBuildTime[] PROGMEM;
const prog_char szBuildTime[]  = "$WCDATE= %H:%M:%S$";

extern const prog_char szBuildDate[] PROGMEM;
const prog_char szBuildDate[]  = "$WCDATE= %d/%m/%y$";

extern const prog_char szCopyriht[] PROGMEM;
const prog_char szCopyriht[] = "© ÍÒÒÎÂ EËÅÊÎÍ";

#endif