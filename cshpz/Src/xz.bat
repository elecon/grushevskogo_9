echo #define > versionhg.h
echo xz hg id >> versionhg.h




::rem For /F "delims=" %b in ('hg id') Do @echo %b%>>versionhg.h
For /F "tokens=2,3* delims=:" %%d in ('hg summary') Do @echo %%d>>versionhg.h
echo //----------------->>versionhg.h
hg summary >>versionhg.h
::rem echo %b% >>ver.h
::rem For /F "delims=:" %%a in ('hg summary') Do   >>ver.h