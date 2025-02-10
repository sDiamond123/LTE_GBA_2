
path=%CD%\devkitadv\bin


gcc -c -O3 -mthumb *.c
gcc -mthumb -o main.elf *.o -lm

if "%errorlevel%"=="1" pause
if "%errorlevel%"=="0" objcopy -O binary main.elf main.gba
del *.o del *.elf &start main.gba
