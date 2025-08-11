@echo off
set folder=bin

cd..
mkdir %folder%
tcc -Iinc main.c ram.c cpu.c logging.c interrupt.c -o barec.exe
move barec.exe %folder%
pause
exit
