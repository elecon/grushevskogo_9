rem ###########################################################################################
rem Set mercurial id to header file
rem ###########################################################################################
rem Writen by Zolotuvskij Sasha zolotoos@ukr.net

echo #ifndef VERSION_H > version.h
echo #define	VERSION_H >> version.h
echo.>>version.h
echo    extern const prog_char szVersion[] PROGMEM; >> version.h
 For /F "delims=" %%b in ('hg id') Do <nul >>version.h set /p =   const prog_char szVersion[]  ="%%b";
echo ";>>version.h
echo.>>version.h
echo    extern const prog_char szVersionTam[] PROGMEM; >> version.h
 For /F "delims=" %%b in ('hg parent --template "{latesttag}+{latesttagdistance}"') Do <nul >>version.h set /p =   const prog_char szVersionTam[]  ="%%b";
echo ";>>version.h
echo.>>version.h
echo.>>version.h
echo #endif >> version.h

